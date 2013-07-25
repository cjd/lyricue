#include "lyricue_display.h"

static AvahiEntryGroup *group = NULL;
static AvahiSimplePoll *simple_poll = NULL;
static char *name = NULL;
static AvahiClient *client = NULL;
static AvahiServiceBrowser *sb = NULL;
static int port = 0;
static char *type_in = NULL;
extern GHashTable *miniviews;
extern gchar *profile;

void entry_group_callback(AvahiEntryGroup *g, AvahiEntryGroupState state, AVAHI_GCC_UNUSED void *userdata) {
    assert(g == group || group == NULL);
    group = g;

    /* Called whenever the entry group state changes */

    switch (state) {
        case AVAHI_ENTRY_GROUP_ESTABLISHED :
            /* The entry group has been established successfully */
            l_debug("Service '%s' successfully established.", name);
            break;

        case AVAHI_ENTRY_GROUP_COLLISION : {
            char *n;

            /* A service name collision with a remote service
             * happened. Let's pick a new name */
            n = avahi_alternative_service_name(name);
            avahi_free(name);
            name = n;

            l_debug("Service name collision, renaming service to '%s'", name);

            /* And recreate the services */
            create_services(avahi_entry_group_get_client(g));
            break;
        }

        case AVAHI_ENTRY_GROUP_FAILURE :

            l_debug("Entry group failure: %s", avahi_strerror(avahi_client_errno(avahi_entry_group_get_client(g))));

            /* Some kind of failure happened while we were registering our services */
            avahi_simple_poll_quit(simple_poll);
            break;

        case AVAHI_ENTRY_GROUP_UNCOMMITED:
        case AVAHI_ENTRY_GROUP_REGISTERING:
            ;
    }
}
void create_services(AvahiClient *c) {
    char *n, type_txt[128], profile_txt[128];
    int ret;
    assert(c);

    /* If this is the first time we're called, let's create a new
     * entry group if necessary */

    if (!group)
        if (!(group = avahi_entry_group_new(c, entry_group_callback, NULL))) {
            l_debug("avahi_entry_group_new() failed: %s", avahi_strerror(avahi_client_errno(c)));
            goto fail;
        }

    /* If the group is empty (either because it was just created, or
     * because it was reset previously, add our entries.  */

    if (avahi_entry_group_is_empty(group)) {
        l_debug("Adding service '%s' type '%s'", name, type_in);

        /* Set type of service */
        snprintf(type_txt, strlen(type_in)+6, "type=%s", type_in);
        snprintf(profile_txt, strlen(profile)+9, "profile=%s", profile);

        /* Add the service for Lyricue Display */
        if ((ret = avahi_entry_group_add_service(group, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, 0, name, "_lyricue._tcp", NULL, NULL, port, type_txt, profile_txt, NULL)) < 0) {

            if (ret == AVAHI_ERR_COLLISION)
                goto collision;

            l_debug("Failed to add _lyricue._tcp service: %s", avahi_strerror(ret));
            goto fail;
        }

        /* Tell the server to register the service */
        if ((ret = avahi_entry_group_commit(group)) < 0) {
            l_debug("Failed to commit entry group: %s", avahi_strerror(ret));
            goto fail;
        }
    }

    return;

collision:

    /* A service name collision with a local service happened. Let's
     * pick a new name */
    n = avahi_alternative_service_name(name);
    avahi_free(name);
    name = n;

    l_debug("Service name collision, renaming service to '%s'", name);

    avahi_entry_group_reset(group);

    create_services(c);
    return;

fail:
    avahi_simple_poll_quit(simple_poll);
}

void client_callback(AvahiClient *c, AvahiClientState state, AVAHI_GCC_UNUSED void * userdata) {
    assert(c);

    /* Called whenever the client or server state changes */

    switch (state) {
        case AVAHI_CLIENT_S_RUNNING:

            /* The server has startup successfully and registered its host
             * name on the network, so it's time to create our services */
            create_services(c);
            break;

        case AVAHI_CLIENT_FAILURE:

            l_debug("Client failure: %s", avahi_strerror(avahi_client_errno(c)));
            avahi_simple_poll_quit(simple_poll);

            break;

        case AVAHI_CLIENT_S_COLLISION:

            /* Let's drop our registered services. When the server is back
             * in AVAHI_SERVER_RUNNING state we will register them
             * again with the new host name. */

        case AVAHI_CLIENT_S_REGISTERING:

            /* The server records are now being established. This
             * might be caused by a host name change. We need to wait
             * for our own records to register until the host name is
             * properly esatblished. */

            if (group)
                avahi_entry_group_reset(group);

            break;

        case AVAHI_CLIENT_CONNECTING:
            ;
    }
}

int publish_avahi(int port_passed, char *type_in_passed) {
    int error;
    AvahiGLibPoll *glib_poll;
    port = port_passed;
    type_in = strndup(type_in_passed,32);

    avahi_set_allocator (avahi_glib_allocator ());

    /* Create the GLIB Adaptor */
    glib_poll = avahi_glib_poll_new (NULL, G_PRIORITY_DEFAULT);

    name = avahi_strdup("Lyricue Display");

    /* Allocate a new client */
    client = avahi_client_new(avahi_glib_poll_get(glib_poll), 0, client_callback, NULL, &error);

    /* Check wether creating the client object succeeded */
    if (!client) {
        l_debug("Failed to create client: %s", avahi_strerror(error));
        unpublish_avahi();
    }

    
    /* Create the service browser */
    if (miniviews==NULL) {
        miniviews = g_hash_table_new(g_str_hash, g_str_equal);
    }
    if (!(sb = avahi_service_browser_new(client, AVAHI_IF_UNSPEC, AVAHI_PROTO_INET, "_lyricue._tcp", NULL, 0, browse_callback, client))) {
        l_debug("Failed to create service browser: %s\n", avahi_strerror(avahi_client_errno(client)));
    }


    return 0;
}


int unpublish_avahi() {
    if (client)
        avahi_client_free(client);

    avahi_free(name);
    return 0;
}

void browse_callback(
    AvahiServiceBrowser *b,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    AvahiBrowserEvent event,
    const char *name,
    const char *type,
    const char *domain,
    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
    void* userdata) {

    AvahiClient *c = userdata;
    assert(b);

    /* Called whenever a new services becomes available on the LAN or is removed from the LAN */

    switch (event) {
        case AVAHI_BROWSER_FAILURE:

            fprintf(stderr, "(Browser) %s\n", avahi_strerror(avahi_client_errno(avahi_service_browser_get_client(b))));
            avahi_simple_poll_quit(simple_poll);
            return;

        case AVAHI_BROWSER_NEW:
            /* We ignore the returned resolver object. In the callback
               function we free it. If the server is terminated before
               the callback function is called the server will free
               the resolver for us. */

            if (!(avahi_service_resolver_new(c, interface, protocol, name, type, domain, AVAHI_PROTO_INET, 0, resolve_callback, c)))
                fprintf(stderr, "Failed to resolve service '%s': %s\n", name, avahi_strerror(avahi_client_errno(c)));

            break;

        case AVAHI_BROWSER_REMOVE:
            fprintf(stderr, "(Browser) REMOVE: service '%s' of type '%s' in domain '%s'\n", name, type, domain);
            break;

        case AVAHI_BROWSER_ALL_FOR_NOW:
        case AVAHI_BROWSER_CACHE_EXHAUSTED:
            break;
    }
}

void resolve_callback(
    AvahiServiceResolver *r,
    AVAHI_GCC_UNUSED AvahiIfIndex interface,
    AVAHI_GCC_UNUSED AvahiProtocol protocol,
    AvahiResolverEvent event,
    const char *name,
    const char *type,
    const char *domain,
    const char *host_name,
    const AvahiAddress *address,
    uint16_t port,
    AvahiStringList *txt,
    AvahiLookupResultFlags flags,
    AVAHI_GCC_UNUSED void* userdata) {

    assert(r);

    /* Called whenever a service has been resolved successfully or timed out */

    switch (event) {
        case AVAHI_RESOLVER_FAILURE:
            l_debug("(Resolver) Failed to resolve service '%s' of type '%s' in domain '%s': %s\n", name, type, domain, avahi_strerror(avahi_client_errno(avahi_service_resolver_get_client(r))));
            break;

        case AVAHI_RESOLVER_FOUND: {
            char a[AVAHI_ADDRESS_STR_MAX], *t;

            avahi_address_snprint(a, sizeof(a), address);
            t = avahi_string_list_to_string(txt);
            char *value;
            size_t *size;
            char *type="type";
            avahi_string_list_get_pair(txt,&type, &value, size);
            l_debug("Type = %s",value);
            if (g_strcmp0(value,"miniview") == 0) {
                gchar *host = g_strdup_printf("%s:%u",a, port);
                l_debug("Found miniview on %s", host);
                if (!g_hash_table_contains(miniviews,host)) {
                    g_hash_table_insert(miniviews, g_strdup(name), host);
                }
            }
            avahi_free(value);
            avahi_free(type);
            avahi_free(t);
        }
    }

    avahi_service_resolver_free(r);
}

