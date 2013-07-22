#include "lyricue_display.h"

static AvahiEntryGroup *group = NULL;
static AvahiSimplePoll *simple_poll = NULL;
static char *name = NULL;
static AvahiClient *client = NULL;
static int port = 0;
static char *type_in = NULL;

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
    char *n, type_txt[128];
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
        l_debug("Adding service '%s'", name);

        /* Set type of service */
        l_debug("type(%lu) = %s",strlen(type_in),type_in);
        snprintf(type_txt, strlen(type_in)+6, "type=%s", type_in);

        /* Add the service for Lyricue Display */
        if ((ret = avahi_entry_group_add_service(group, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, 0, name, "_lyricue._tcp", NULL, NULL, port, type_txt, NULL)) < 0) {

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

    return 0;
}


int unpublish_avahi() {
    if (client)
        avahi_client_free(client);

    avahi_free(name);
    return 0;
}
