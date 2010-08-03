/***************************************************************************
 *            lyricue_display.c
 *
 *  Tue Jul 20 15:49:24 2010
 *  Copyright  2010  Chris Debenham
 *  <chris@adebenham.com>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
	 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#include "lyricue_display.h"

extern MYSQL *lyricDb;
extern gchar *bible_name;
extern int stage_width;
extern int stage_height;
extern gint bg_is_video;
extern ClutterActor *background;

gboolean blanked_state = FALSE;
gchar *default_bg = NULL;
gchar *current_bg = NULL;
gchar *temp_bg = NULL;
int current_item = 0;
int current_list = 0;
int loop_parent = 0;
GHashTable *config = NULL;
#define SERVER_PORT 2346

// Command line options
gboolean windowed = FALSE;
int server_port = SERVER_PORT;
gchar *dbhostname = NULL;
gchar *geometry = NULL;

static GOptionEntry entries[] = {
    {"window", 'w', 0, G_OPTION_ARG_NONE, &windowed, "Run in a window", NULL},
    {"remote", 'r', 0, G_OPTION_ARG_STRING, &dbhostname, "Database hostname",
     NULL},
    {"geometry", 'g', 0, G_OPTION_ARG_STRING, &geometry, "Window Geometry",
     NULL},
    {"port", 'p', 0, G_OPTION_ARG_INT, &server_port, "Port to listen on",
     NULL},
    {NULL}
};


int
main (int argc, char *argv[])
{
    bindtextdomain (GETTEXT_PACKAGE, NULL);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);

    g_type_init ();
    GError *error = NULL;
    GOptionContext *context;

    context = g_option_context_new ("- Lyricue display");
    g_option_context_add_main_entries (context, entries, GETTEXT_PACKAGE);
    g_option_context_set_ignore_unknown_options(context, TRUE);
    if (!g_option_context_parse (context, &argc, &argv, &error)) {
        g_print ("option parsing failed: %s\n", error->message);
        exit (1);
    }
    int ret = db_select ();
    load_configuration (lyricDb);
    bible_load ((gchar *) g_hash_table_lookup (config, "DefBible"));


    // Setup network
    GSocketService *service = g_socket_service_new ();
    GInetAddress *address = g_inet_address_new_any (G_SOCKET_FAMILY_IPV4);
    l_debug ("Listening on %d", server_port);
    if (!g_socket_listener_add_inet_port
        (G_SOCKET_LISTENER (service), server_port, NULL, NULL)) {
        l_debug ("Unable to listen on port %d", server_port);
        return EXIT_FAILURE;
    }
    g_object_unref (address);
    g_socket_service_start (service);
    g_signal_connect (service, "incoming", G_CALLBACK (new_connection), NULL);

    ret = create_main_window (argc, argv);

    clutter_main ();
    ret = db_deselect ();

    return EXIT_SUCCESS;
}

gboolean
network_read (GIOChannel * source, GIOCondition cond, gpointer data)
{
    GString *s = g_string_new (NULL);
    GError *error = NULL;
    GIOStatus ret = g_io_channel_read_line_string (source, s, NULL, &error);

    if (ret == G_IO_STATUS_EOF) {
        l_debug ("eof");
        return FALSE;
    } else if (ret == G_IO_STATUS_ERROR) {
        g_warning ("Error reading: %s\n", error->message);
        // Drop last reference on connection
        g_object_unref (data);
        // Remove the event source
        return FALSE;
    } else {
        s->str = g_strchomp (s->str);
        if (g_utf8_strlen (s->str, -1) > 0) {
            handle_command (source, s->str);
        }
        g_io_channel_shutdown (source, TRUE, NULL);
        g_object_unref (data);
        return FALSE;
    }

    return TRUE;
}

gboolean
new_connection (GSocketService * service,
                GSocketConnection * connection,
                GObject * source_object, gpointer user_data)
{
    GSocketAddress *sockaddr =
      g_socket_connection_get_remote_address (connection, NULL);
    GInetAddress *addr =
      g_inet_socket_address_get_address (G_INET_SOCKET_ADDRESS (sockaddr));
    guint16 port =
      g_inet_socket_address_get_port (G_INET_SOCKET_ADDRESS (sockaddr));

    l_debug ("New Connection from %s:%d", g_inet_address_to_string (addr),
             port);

    g_object_ref (connection);
    GSocket *socket = g_socket_connection_get_socket (connection);

    gint fd = g_socket_get_fd (socket);
    GIOChannel *channel = g_io_channel_unix_new (fd);
    g_io_add_watch (channel, G_IO_IN, (GIOFunc) network_read, connection);
    return TRUE;
}

void
handle_command (GIOChannel * source, const char *command)
{
    l_debug ("Received: %s", command);
    GString *returnstring = NULL;
    gchar **line = g_strsplit (command, ":", 2);
    if (line[1] != NULL) {
        line[0] = g_utf8_strdown (line[0], -1);
        if (g_strcmp0 (line[0], "preview") == 0) {
            do_preview (command);
        } else if (g_strcmp0 (line[0], "status") == 0) {
            returnstring = do_status ();
        } else if (g_strcmp0 (line[0], "snapshot") == 0) {
            do_snapshot ();
        } else if (g_strcmp0 (line[0], "reconfig") == 0) {
            do_reconfig ();
        } else if (g_strcmp0 (line[0], "backdrop") == 0) {
            do_backdrop (line[1]);
        } else if (g_strcmp0 (line[0], "blank") == 0) {
            do_blank (line[1]);
        } else if (g_strcmp0 (line[0], "change_to_db") == 0) {
            do_change_to_db (line[1]);
        } else if (g_strcmp0 (line[0], "next_point") == 0) {
            do_next_point (line[1]);
        } else if (g_strcmp0 (line[0], "loopparent") == 0) {
            do_loopparent (line[1]);
        } else if (g_strcmp0 (line[0], "get") == 0) {
            do_get (line[1]);
        } else if (g_strcmp0 (line[0], "display") == 0) {
            do_display (line[1]);
        } else if (g_strcmp0 (line[0], "osd") == 0) {
            do_osd (line[1]);
        } else if (g_strcmp0 (line[0], "media") == 0) {
            do_media (line[1]);
        }
    }
    g_strfreev (line);
    if (returnstring != NULL) {
        l_debug("The status message sent is: %s",returnstring->str);
        GIOStatus res = g_io_channel_write_chars (source, returnstring->str,
                                                  returnstring->len, NULL,
                                                  NULL);
        g_string_free (returnstring, TRUE);
        if (res != G_IO_STATUS_NORMAL)
            return;
        /* force flushing of the write buffer */
        res = g_io_channel_flush (source, NULL);
    }
    update_tracker();
}

void
do_media (const char *options)
{
    if (bg_is_video) {
        if (g_strcmp0 (options, "pause")) {
            media_pause ();
        } else if (g_strcmp0 (options, "skip")) {
        }
    }
}

void
do_preview (const char *options)
{
    set_maintext (options, 0, 1);
}

GString *
do_status ()
{
    l_debug ("Return status");
    GString *ret = g_string_new (NULL);
    g_string_printf (ret, "Status,W:%d,H:%d,F:%s,B:%s\n", stage_width,
                     stage_height, (gchar *) g_hash_table_lookup (config,
                                                                  "Main"),
                     bible_name);
    return ret;
}

void
do_snapshot ()
{
    l_debug ("do_snapshot not implemented");
}

void
do_reconfig ()
{
    l_debug ("do_reconfig");
    load_configuration (lyricDb);
}

void
do_backdrop (const char *options)
{
    l_debug ("do_backdrop: %s", options);
    gchar **line = g_strsplit (options, ":", 2);
    temp_bg = NULL;
    default_bg = g_strdup(line[0]);
    change_backdrop (default_bg, TRUE);
    g_strfreev (line);
}

void
do_blank (const char *options)
{
    l_debug ("do_blank: %s", options);
    set_maintext ("", 0, FALSE);
    set_headtext ("", 0, FALSE);
    set_foottext ("", 0, FALSE);
    if (options != NULL) {
        temp_bg = current_bg;
        change_backdrop (options, TRUE);
    } else {
        temp_bg = NULL;
    }
    blanked_state = TRUE;
}

void
do_change_to_db (const char *options)
{
    l_debug ("do_change_to_db: %s", options);
    bible_load (options);
}

void
do_next_point (const char *options)
{
    l_debug ("do_next_point not implemented");
}

void
do_loopparent (const char *options)
{
    l_debug ("do_loopparent %s", options);
    loop_parent = atoi (options);
}

void
do_get (const char *options)
{
    l_debug ("do_get not implemented");
}

void
do_osd (const char *options)
{
    l_debug ("do_osd not implemented");
}

void
do_display (const char *options)
{
    l_debug ("do_display");
    if (options != NULL) {
        gchar **line = g_strsplit (options, ":", 2);
        if (blanked_state && temp_bg) {
            change_backdrop (temp_bg, TRUE);
            blanked_state = FALSE;
            temp_bg = NULL;
        }
        blanked_state = FALSE;
        MYSQL_ROW row;
        MYSQL_RES *result;
        do_query (lyricDb, "SELECT playlist FROM playlist WHERE playorder=%d",
                  current_item);
        result = mysql_store_result (lyricDb);
        row = mysql_fetch_row (result);
		if (row != NULL) {
        	current_list = atoi (row[0]);
		}
        mysql_free_result (result);

        gchar *command = g_utf8_strdown (line[0], -1);

        if (g_strcmp0 (command, "playlist") == 0) {
            current_list = atoi (line[1]);

        } else if (g_strcmp0 (command, "current") == 0) {
            // Ignore and just display same page
            blanked_state = FALSE;

        } else if (g_strcmp0 (command, "next_page") == 0) {
            do_query (lyricDb,
                      "SELECT MIN(playorder) FROM playlist WHERE playlist=%d AND playorder > %d ORDER BY playorder",
                      current_list, current_item);
            result = mysql_store_result (lyricDb);
            row = mysql_fetch_row (result);
            mysql_free_result (result);
            if (row[0]) {
                // Show next page
                current_item = atoi (row[0]);
            } else {
                // End of song reached
                if (g_strcmp0 (line[1], "loop")) {
                    // Looping
                    do_query (lyricDb,
                              "SELECT MIN(playorder) FROM playlist WHERE playlist=%d",
                              current_list);
                    result = mysql_store_result (lyricDb);
                    row = mysql_fetch_row (result);
                    mysql_free_result (result);
                    current_item = atoi (row[0]);
                } else {
                    // Jump to next song
                    do_display ("next_song:0");
                }
            }

        } else if (g_strcmp0 (command, "prev_page") == 0) {
            do_query (lyricDb,
                      "SELECT MAX(playorder) FROM playlist WHERE playlist=%d AND playorder < %d ORDER BY playorder",
                      current_list, current_item);
            result = mysql_store_result (lyricDb);
            row = mysql_fetch_row (result);
            mysql_free_result (result);
            if (row[0]) {
                current_item = atoi (row[0]);
            } else {
                if (g_strcmp0 (line[1], "loop")) {
                    do_query (lyricDb,
                              "SELECT MAX(playorder) FROM playlist WHERE playlist=%d",
                              current_list);
                    result = mysql_store_result (lyricDb);
                    row = mysql_fetch_row (result);
                    mysql_free_result (result);
                    current_item = atoi (row[0]);
                }
            }

        } else if (g_strcmp0 (command, "next_song") == 0) {
            do_query (lyricDb,
                      "SELECT a.playorder,a.playlist FROM playlist AS a, playlist AS b WHERE a.data=b.playlist AND a.type=\"play\" AND b.playorder=%d",
                      current_item);
            result = mysql_store_result (lyricDb);
            row = mysql_fetch_row (result);
            mysql_free_result (result);
			if (row && (row[0] != NULL)) {
            	current_item = atoi (row[0]);
            	current_list = atoi (row[1]);
	            do_query (lyricDb,
                      "SELECT MIN(playorder) FROM playlist WHERE playorder > %d AND playlist=%d",
                      current_item, current_list);
	            result = mysql_store_result (lyricDb);
    	        row = mysql_fetch_row (result);
    	        mysql_free_result (result);
				if (row[0] != NULL) {
	    	        current_item = atoi (row[0]);
				}
			}

        } else if (g_strcmp0 (command, "prev_song") == 0) {
            do_query (lyricDb,
                      "SELECT a.playorder,a.playlist FROM playlist AS a, playlist AS b WHERE a.data=b.playlist AND a.type=\"play\" AND b.playorder=%d",
                      current_item);
            result = mysql_store_result (lyricDb);
            row = mysql_fetch_row (result);
            mysql_free_result (result);
			if (row && (row[0] != NULL)) {
	            current_item = atoi (row[0]);
    	        current_list = atoi (row[1]);
    	        do_query (lyricDb,
                      "SELECT MAX(playorder) FROM playlist WHERE playorder < %d AND playlist=%d",
                      current_item, current_list);
    	        result = mysql_store_result (lyricDb);
    	        row = mysql_fetch_row (result);
    	        mysql_free_result (result);
				if (row[0] != NULL) {
 	    	        current_item = atoi (row[0]);
				}
			}

        } else if (g_strcmp0 (command, "page") == 0) {
            do_query (lyricDb,
                      "SELECT playorder FROM playlist WHERE playlist=%d",
                      current_list);
            result = mysql_store_result (lyricDb);
            int count = 0;
            while ((count < atoi (line[1]))
                   && (row = mysql_fetch_row (result))) {
                count++;
            }
            if (row && (row[0] != NULL)) {
                current_item = atoi (row[0]);
            }
        } else {
            current_item = atoi (command);
        }

        do_query (lyricDb,
                  "SELECT type,data,transition FROM playlist WHERE playorder=%d",
                  current_item);
        result = mysql_store_result (lyricDb);
        row = mysql_fetch_row (result);
        if (row != NULL) {
            gchar *type = g_strdup (row[0]);
            gchar *data = g_strdup (row[1]);
            gchar *lyrics = "";
            gchar *header = "";
            gchar *footer = "";
            gboolean wrap = FALSE;
            int transition = atoi (row[2]);

            gboolean bg_changed = FALSE;
            if (g_strcmp0 (type, "back") == 0) {
                gchar **line = g_strsplit(data,":",2);
                default_bg = g_strdup(line[0]);
                change_backdrop (default_bg, TRUE);
                bg_changed = TRUE;
                g_strfreev(line);
            } else if (g_strcmp0 (type, "file") == 0) {
                gchar **line = g_strsplit(data,":",2);
                change_backdrop (line[0], FALSE);
                bg_changed = TRUE;
                g_strfreev(line);
            } else if (g_strcmp0 (type, "imag") == 0) {
                change_backdrop (data, FALSE);
                bg_changed = TRUE;
            } else if (g_strcmp0 (type, "vers") == 0) {
                do_query (lyricDb,
                          "SELECT title FROM playlist,playlists WHERE playlist.playlist=playlists.id AND playorder=%d",
                          current_item);
                result = mysql_store_result (lyricDb);
                row = mysql_fetch_row (result);
                gchar **selected = g_strsplit (data, ":", 2);
                gchar *verse = NULL;
                if (selected[1] == NULL) {
                    selected = g_strsplit (row[0], ":", 3);
                    gchar **datasplt = g_strsplit (data, "-", 2);
                    GString *verseref = g_string_new (NULL);
                    g_string_printf (verseref, "%s:%s:%s-%s:%s", selected[0],
                                     selected[1], datasplt[0], selected[1],
                                     datasplt[1]);
                    verse = do_grab_verse (g_string_free (verseref, FALSE));
                } else {
                    // Broken
                }

                if (verse != NULL) {
                    lyrics = g_strdup(verse);
                }
                header = g_strdup(row[0]);
                footer = g_strdup(bible_name);
                wrap = TRUE;
            } else if ((g_strcmp0 (type, "play") == 0) ||
                       (g_strcmp0 (type, "sub") == 0)) {
                do_query (lyricDb,
                          "SELECT playorder FROM playlist WHERE playlist=%s ORDER BY playorder",
                          data);
                result = mysql_store_result (lyricDb);
                row = mysql_fetch_row (result);
                do_display (row[0]);
            } else {            // Song page
                do_query (lyricDb,
                          "SELECT title,artist,lyrics,copyright FROM lyricMain AS l, page AS pa WHERE pa.songid=l.id AND pa.pageid=%s",
                          data);
                result = mysql_store_result (lyricDb);
                row = mysql_fetch_row (result);
                mysql_free_result (result);
                if (row != NULL) {
                    gchar *title = g_strdup (row[0]);
                    gchar *artist = g_strdup (row[1]);
                    gchar *copyright = g_strdup (row[3]);
                    GString *foot = g_string_new (NULL);
                    if (g_utf8_strlen (artist, 10) != 0) {
                        g_string_printf (foot, "Written by %s", artist);
                    }
                    if (g_utf8_strlen (copyright, 10) != 0) {
                        g_string_append_printf (foot, " - %s", copyright);
                    }
                    lyrics = g_strdup(row[2]);
                    header = g_strdup(title);
                    footer = g_strdup(foot->str);
                    g_string_free (foot, TRUE);
                }
            }

            // Look for associated background image
            if (!bg_changed) {
                int res = do_query (lyricDb,
                                    "SELECT imagename FROM associations WHERE playlist=%d",
                                    current_item);
                int bg_changed = FALSE;
                if (res == 0) {
                    result = mysql_store_result (lyricDb);
                    row = mysql_fetch_row (result);
                    if (row != NULL) {
                        change_backdrop (row[0], TRUE);
                        bg_changed = TRUE;
                    }
                    mysql_free_result (result);
                }
                if (!bg_changed) {
                    res =
                      do_query (lyricDb,
                                "SELECT a.imagename,q.data FROM associations as a, playlist AS p, playlist AS q WHERE p.type='play' AND p.data=q.playlist and a.playlist=p.playorder AND q.playorder=%d",
                                current_item);
                    if (res == 0) {
                        result = mysql_store_result (lyricDb);
                        row = mysql_fetch_row (result);
                        mysql_free_result (result);
                        if (row != NULL) {
                            change_backdrop (row[0], TRUE);
                            bg_changed = TRUE;
                        }
                    }
                }
                if (!bg_changed && (g_strcmp0(default_bg, current_bg) != 0)) {
                    l_debug("Reset bg to default");
                    change_backdrop(default_bg, TRUE);
                }
            }

            set_maintext(lyrics, transition, wrap);
            set_headtext(header, transition, wrap);
            set_foottext(footer, transition, wrap);
        }
    }


}

gboolean
update_tracker ()
{
    l_debug ("Updating tracker");

    // Only do if this is main server
    if (server_port == SERVER_PORT) {
        GString *title = g_string_new (NULL);
        if (blanked_state) {
            g_string_assign (title, "blank");
        }
        if (bg_is_video) {
            g_string_append_printf (title, "%.0f;%.0f;%d",
                                    clutter_media_get_progress (CLUTTER_MEDIA
                                                                (background))
                                    *
                                    clutter_media_get_duration (CLUTTER_MEDIA
                                                                (background)),
                                    clutter_media_get_duration (CLUTTER_MEDIA
                                                                (background)),
                                    clutter_media_get_playing (CLUTTER_MEDIA
                                                               (background)));
        } else {
            g_string_append (title, "0;0;0");
        }
        do_query (lyricDb,
                  "UPDATE playlists SET ref = %d, title = \"%s\" WHERE id=-1",
                  current_item, g_string_free (title, FALSE));
    }
	return TRUE;
}
