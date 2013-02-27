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
extern MYSQL *mediaDb;
extern MYSQL *bibleDb;
extern gchar *bible_name;
extern gchar *bible_table;
extern gfloat stage_width;
extern gfloat stage_height;
extern gint bg_is_video;
extern ClutterActor *background;

gint blanked_state = BLANK_NONE;
gchar *default_bg = NULL;
gchar *current_bg = NULL;
gchar *temp_bg = NULL;
int current_item = 0;
int current_list = 0;
GHashTable *config = NULL;
#define SERVER_PORT 2346

// Command line options
gboolean windowed = FALSE;
gboolean debugging = FALSE;
int server_port = SERVER_PORT;
gchar *dbhostname = "localhost";
gchar *geometry = NULL;
unsigned long windowid = 0;

static GOptionEntry entries[] = {
    {"window", 'w', 0, G_OPTION_ARG_NONE, &windowed, "Run in a window", NULL},
    {"remote", 'r', 0, G_OPTION_ARG_STRING, &dbhostname, "Database hostname",
     NULL},
    {"geometry", 'g', 0, G_OPTION_ARG_STRING, &geometry, "Window Geometry",
     NULL},
    {"port", 'p', 0, G_OPTION_ARG_INT, &server_port, "Port to listen on",
     NULL},
    {"miniview", 'm', 0, G_OPTION_ARG_INT, &windowid, "Embed in windowid",
     NULL},
    {"debug", 'd', 0, G_OPTION_ARG_NONE, &debugging, "Enable debug output",
     NULL},
    {NULL}
};


int
main (int argc, char *argv[])
{
    unsetenv ("LIBGL_ALWAYS_INDIRECT");
    setenv ("CLUTTER_DISABLE_MIPMAPPED_TEXT", "1", 0);
    bindtextdomain (GETTEXT_PACKAGE, NULL);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);
    srand(time(NULL));

    g_type_init ();
    GError *error = NULL;
    GOptionContext *context;

    context = g_option_context_new ("- Lyricue display");
    g_option_context_add_main_entries (context, entries, GETTEXT_PACKAGE);
    g_option_context_set_ignore_unknown_options (context, TRUE);
    if (!g_option_context_parse (context, &argc, &argv, &error)) {
        g_print ("option parsing failed: %s\n", error->message);
        exit (1);
    }
    int ret = db_select ();
    if (ret) {
        // Really should handle this ;)
    }
    load_configuration (lyricDb);
    bible_load ((gchar *) g_hash_table_lookup (config, "DefBible"));


    // Setup network
    GSocketService *service = g_socket_service_new ();
    GInetAddress *address = g_inet_address_new_any (G_SOCKET_FAMILY_IPV4);
    g_snprintf (argv[0], 29, "Lyricue Display on port %04d", server_port);
    l_debug ("Process Name:%s", argv[0]);

    if (!g_socket_listener_add_inet_port
        (G_SOCKET_LISTENER (service), server_port, NULL, NULL)) {
        l_debug ("Unable to listen on port %d", server_port);
        return EXIT_FAILURE;
    }
    g_object_unref (address);
    g_socket_service_start (service);
    g_signal_connect (service, "incoming", G_CALLBACK (new_connection), NULL);

    // Setup tracker entry in DB
    do_query (lyricDb, "DELETE FROM playlists WHERE id=-1");
    do_query (lyricDb, "INSERT INTO playlists SET id=-1,ref=0,title=''");

    ret = create_main_window (argc, argv);

    if (windowid == 0) {
        clutter_main ();
    } else {
        gtk_main ();
    }
    ret = db_deselect ();

    l_debug("Exiting");
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
        s->str = g_strstrip (s->str);
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
    update_miniview (command);
    if (line[1] != NULL) {
        line[0] = g_utf8_strdown (line[0], -1);
        if (g_strcmp0 (line[0], "preview") == 0) {
            do_preview (line[1]);
        } else if (g_strcmp0 (line[0], "status") == 0) {
            returnstring = do_status ();
        } else if (g_strcmp0 (line[0], "dbsnapshot") == 0) {
            do_dbsnapshot (line[1]);
        } else if (g_strcmp0 (line[0], "plsnapshot") == 0) {
            do_plsnapshot (line[1]);
            returnstring = g_string_new("done");
        } else if (g_strcmp0 (line[0], "snapshot") == 0) {
            returnstring = do_snapshot (line[1]);
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
        } else if (g_strcmp0 (line[0], "get") == 0) {
            do_get (line[1]);
        } else if (g_strcmp0 (line[0], "display") == 0) {
            do_display (line[1],FALSE);
        } else if (g_strcmp0 (line[0], "osd") == 0) {
            do_osd (line[1]);
        } else if (g_strcmp0 (line[0], "media") == 0) {
            do_media (line[1]);
        } else if (g_strcmp0 (line[0], "fade") == 0) {
            do_fade (line[1]);
        } else if (g_strcmp0 (line[0], "blur") == 0) {
            do_blur (line[1]);
        } else if (g_strcmp0 (line[0], "save") == 0) {
            do_save (line[1]);
        } else if (g_strcmp0 (line[0], "query") == 0) {
            returnstring = do_query_json (line[1]);
        }
    }
    g_strfreev (line);
    if (returnstring != NULL) {
        l_debug ("The status message sent is: %s", returnstring->str);
        GIOStatus res = g_io_channel_write_chars (source, returnstring->str,
                                                  returnstring->len, NULL,
                                                  NULL);
        g_string_free (returnstring, TRUE);
        if (res != G_IO_STATUS_NORMAL)
            return;
        /* force flushing of the write buffer */
        res = g_io_channel_flush (source, NULL);
    }
    update_tracker ();
}

void
do_media (const char *options)
{
    if (bg_is_video) {
        gchar **line = g_strsplit (options, ":", 2);
        if (g_ascii_strncasecmp (line[0], "pause", 5) == 0) {
            media_pause ();
        } else if (g_ascii_strncasecmp (line[0], "skip", 4) == 0) {
            media_skip (atoi (line[1]));
        }
        g_strfreev (line);
    }
}

void
do_fade (const char *options)
{
    fade_backdrop (atoi (options));
}

void
do_blur (const char *options)
{
    blur_backdrop (atoi (options));
}

void
do_preview (const char *options)
{
    gchar **line = g_strsplit (options, ":", 2);
    gboolean wrap = TRUE;
    unblank ();
    if (g_strcmp0 (line[0], "ignore") != 0) {
        gchar **extras = g_strsplit (parse_special (line[0]), "\n", 4);
        if ((g_strv_length (extras) == 6)
            && (g_strcmp0 (extras[3], "nowrap") == 0)) {
            wrap = FALSE;
        }
        set_headtext (parse_special (extras[0]), 0, 1);

        if (g_strv_length (extras) >= 3) {
            GString *footer = g_string_new (NULL);

            if (g_utf8_strlen (extras[2], 10) != 0) {
                g_string_printf (footer, "%s %s - %s",
                                 gettext ("Written by "), extras[1],
                                 extras[2]);
            } else {
                if (g_utf8_strlen (extras[1], 10) != 0) {
                    g_string_printf (footer, "%s %s",
                                     gettext ("Written by "), extras[1]);
                } else {
                    g_string_assign (footer, "");
                }
            }
            set_foottext (footer->str, 0, 1);
            g_string_free (footer, TRUE);
        }
        g_strfreev (extras);

    }
    set_maintext (parse_special (line[1]), 0, wrap);
    g_strfreev (line);
}

GString *
do_status ()
{
    l_debug ("Return status");
    GString *ret = g_string_new (NULL);
    g_string_printf (ret, "Status,W:%.0f,H:%.0f,F:%s,T:%s,B:%s\n", stage_width,
                     stage_height, (gchar *) g_hash_table_lookup (config,
                                                                  "Main"),
                     bible_table, bible_name);
    return ret;
}

GString *
do_snapshot (const char *options)
{
    l_debug ("do_snapshot");
    gchar **line = g_strsplit (options, ":", 2);
    int width=0;
    if (line[1] != NULL) {
        width=atoi(line[1]);
    }
    GString *ret = take_snapshot (line[0], width);
    g_strfreev (line);
    return ret;
}

void
do_dbsnapshot (const char *options)
{
    l_debug ("do_snapshot");
    gchar **line = g_strsplit (options, ":", 2);
    take_dbsnapshot (atoi(line[0]));
    g_strfreev (line);
}

void
do_plsnapshot (const char *options)
{
    l_debug ("do_snapshot");
    gchar **line = g_strsplit (options, ":", 2);
    playlist_snapshot(atoi(line[0]));
    g_strfreev (line);
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
    default_bg = parse_special (line[0]);
    change_backdrop (default_bg, TRUE, DEFAULT);
    g_strfreev (line);
}

void
unblank ()
{
    if (blanked_state == BLANK_BG) {
        change_backdrop (temp_bg, TRUE, DEFAULT);
    }
    blanked_state = BLANK_NONE;
}

void
do_blank (const char *options)
{
    l_debug ("do_blank: %s", options);
    gchar **line = g_strsplit (options, ":", 2);
    if (strlen (options) <= 1) {
        options = NULL;
    }

    if (blanked_state == BLANK_BG) {
        l_debug ("Re-show text");
        do_display ("current",FALSE);
    } else if ((blanked_state == BLANK_TEXT) && options != NULL) {
        l_debug ("clear text and set BG");
        temp_bg = current_bg;
        change_backdrop (line[0], TRUE, DEFAULT);
        blanked_state = BLANK_BG;
    } else if ((blanked_state == BLANK_TEXT) && options == NULL) {
        l_debug ("Re-show text - 2");
        do_display ("current",FALSE);
    } else if (options != NULL) {
        l_debug ("clear text and set BG - 2");
        temp_bg = current_bg;
        change_backdrop (line[0], TRUE, DEFAULT);
        set_maintext ("", 0, FALSE);
        set_headtext ("", 0, FALSE);
        set_foottext ("", 0, FALSE);
        blanked_state = BLANK_BG;
    } else {
        l_debug ("Clear text");
        set_maintext ("", 0, FALSE);
        set_headtext ("", 0, FALSE);
        set_foottext ("", 0, FALSE);
        blanked_state = BLANK_TEXT;
    }
    g_strfreev (line);
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
do_get (const char *options)
{
    l_debug ("do_get not implemented");
}

void
do_osd (const char *options)
{
    l_debug ("do_osd");
    if (options != NULL) {
        gchar **line = g_strsplit (options, ":", 2);
        int speed = 10000;
        if (g_strcmp0 (line[0], "slow") == 0) {
            speed = 20000;
        } else if (g_strcmp0 (line[0], "fast") == 0) {
            speed = 5000;
        } else if (g_strcmp0 (line[0], "default") == 0) {
            speed = 10000;
        } else {
            speed = atoi (line[0]);
        }
        gchar *text = parse_special (line[1]);
        set_osd (speed, text);
    }
}

void
do_display (const char *options, const int quick_show)
{
    l_debug ("do_display");
    if (options != NULL) {
        gchar **line = g_strsplit (options, ":", 2);
        unblank ();
        MYSQL_ROW row;
        MYSQL_RES *result;
        gboolean bg_changed = FALSE;
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
            // Clear text and then redisplay same page
            set_maintext ("", 0, FALSE);
            set_headtext ("", 0, FALSE);
            set_foottext ("", 0, FALSE);
            if (g_strcmp0 (line[1], "nobg") == 0) {
                bg_changed = TRUE;
            }
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
                gchar **loop = g_strsplit (line[1], ";", 2);
                if (g_strcmp0 (loop[0], "loop") == 0) {
                    // Looping
                    int loop_parent = 0;
                    if (loop[1] != NULL) {
                        loop_parent = atoi (loop[1]);
                    }
                    if (loop_parent == 0) {
                        l_debug ("Looping a song, back to page 1");
                        do_query (lyricDb,
                                  "SELECT MIN(playorder) FROM playlist WHERE playlist=%d",
                                  current_list);
                        result = mysql_store_result (lyricDb);
                        row = mysql_fetch_row (result);
                        mysql_free_result (result);
                        if (row[0] != NULL) {
                            current_item = atoi (row[0]);
                        }
                    } else {
                        l_debug ("Looping a sublist");
                        do_query (lyricDb,
                                  "SELECT MIN(p1.playorder) FROM playlist AS p1, playlist AS p2 WHERE p1.playorder>p2.playorder AND p2.type='play' AND p2.data=%d AND p1.playlist=%d",
                                  current_list, loop_parent);
                        result = mysql_store_result (lyricDb);
                        row = mysql_fetch_row (result);
                        mysql_free_result (result);
                        if (row[0] != NULL) {
                            current_item = atoi (row[0]);
                        } else {
                            // Loop back to top of parent
                            do_query (lyricDb,
                                      "SELECT MIN(playorder) FROM playlist WHERE playlist=%d",
                                      loop_parent);
                            result = mysql_store_result (lyricDb);
                            row = mysql_fetch_row (result);
                            mysql_free_result (result);
                            if (row[0] != NULL) {
                                current_item = atoi (row[0]);
                            }
                        }
                    }
                } else {
                    // Jump to next song
                    do_display ("next_song:0",FALSE);
                    return;
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
                if (g_strcmp0 (line[1], "loop") == 0) {
                    // Loop back to end of playlist
                    do_query (lyricDb,
                              "SELECT MAX(playorder) FROM playlist WHERE playlist=%d",
                              current_list);
                    result = mysql_store_result (lyricDb);
                    row = mysql_fetch_row (result);
                    mysql_free_result (result);
                    if (row[0] != NULL) {
                        current_item = atoi (row[0]);
                    }
                } else {
                    // Jump back to last page of previous song
                    do_query(lyricDb,
                             "SELECT MAX(playorder) FROM playlist "
                             "WHERE playlist="
                             "(SELECT data FROM playlist "
                             " WHERE playorder= "
                             "  (SELECT MAX(playorder) FROM playlist "
                             "   WHERE playorder < "
                             "   (SELECT playorder FROM playlist "
                             "    WHERE type='play' AND data=%d) "
                             "    AND playlist = "
                             "    (SELECT playlist FROM playlist "
                             "     WHERE type='play' AND data=%d)))",
                             current_list,
                             current_list);
                    result = mysql_store_result (lyricDb);
                    row = mysql_fetch_row (result);
                    mysql_free_result (result);
                    if (row[0] != NULL) {
                        current_item = atoi (row[0]);
                    }
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
            }
            do_query (lyricDb,
                      "SELECT MIN(playorder) FROM playlist WHERE playorder > %d AND playlist=%d",
                      current_item, current_list);
            result = mysql_store_result (lyricDb);
            row = mysql_fetch_row (result);
            if (row[0] != NULL) {
                current_item = atoi (row[0]);
            }
            mysql_free_result (result);

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
            }
            do_query (lyricDb,
                      "SELECT MAX(playorder) FROM playlist WHERE playorder < %d AND playlist=%d",
                      current_item, current_list);
            result = mysql_store_result (lyricDb);
            row = mysql_fetch_row (result);
            mysql_free_result (result);
            if (row[0] != NULL) {
                current_item = atoi (row[0]);
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
            gboolean wrap = TRUE;
            int transition = atoi (row[2]);
            if (quick_show) {
                transition = NO_EFFECT;
            }

            if (g_strcmp0 (type, "back") == 0) {
                default_bg = g_strdup (data);
                change_backdrop (default_bg, TRUE, transition);
                bg_changed = TRUE;
                g_strfreev (line);
            } else if (g_strcmp0 (type, "file") == 0) {
                change_backdrop (data, FALSE, transition);
                bg_changed = TRUE;
                g_strfreev (line);
            } else if (g_strcmp0 (type, "imag") == 0) {
                change_backdrop (data, FALSE, transition);
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
                    lyrics = g_strdup (verse);
                }
                header = g_strdup (row[0]);
                footer = g_strdup (bible_name);
                wrap = TRUE;
            } else if ((g_strcmp0 (type, "play") == 0) ||
                       (g_strcmp0 (type, "sub") == 0)) {
                do_query (lyricDb,
                          "SELECT playorder FROM playlist WHERE playlist=%s ORDER BY playorder",
                          data);
                result = mysql_store_result (lyricDb);
                row = mysql_fetch_row (result);
                do_display (row[0],FALSE);
                return;
            } else {            // Song page
                do_query (lyricDb,
                          "SELECT title,artist,lyrics,copyright FROM lyricMain AS l, page AS pa WHERE (pa.songid=l.id OR pa.songid=-l.id) AND pa.pageid=%s",
                          data);
                result = mysql_store_result (lyricDb);
                row = mysql_fetch_row (result);
                mysql_free_result (result);
                if (row != NULL) {
                    gchar *title = g_strdup (row[0]);
                    gchar *artist = g_strdup (row[1]);
                    gchar *lyrictmp = g_strdup (row[2]);
                    gchar *copyright = g_strdup (row[3]);
                    GString *foot = g_string_new (NULL);
                    if (g_utf8_strlen (artist, 10) != 0) {
                        g_string_printf (foot, "Written by %s", artist);
                    }
                    if (g_utf8_strlen (copyright, 10) != 0) {
                        if (g_ascii_strncasecmp(copyright,"Preset",6) == 0) {
                            copyright=(gchar *) g_hash_table_lookup (config,copyright);
                        }
                        g_string_append_printf (foot, " - %s", copyright);
                    }
                    lyrics = g_strdup (lyrictmp);
                    header = g_strdup (title);
                    footer = g_strdup (foot->str);
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
                        change_backdrop (row[0], TRUE, transition);
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
                            change_backdrop (row[0], TRUE, transition);
                            bg_changed = TRUE;
                        }
                    }
                }
                if (!bg_changed && (g_strcmp0 (default_bg, current_bg) != 0)) {
                    l_debug ("Reset bg to default");
                    change_backdrop (default_bg, TRUE, transition);
                }
            }

            if (quick_show) {
                transition = NO_EFFECT;
            }
            set_maintext (parse_special (lyrics), transition, wrap);
            set_headtext (parse_special (header), transition, wrap);
            set_foottext (parse_special (footer), transition, wrap);
        }
    }
}

gboolean
update_tracker ()
{
    //l_debug ("Updating tracker");

    // Only do if this is main server
    if (server_port == SERVER_PORT) {
        GString *title = g_string_new (NULL);
        if (blanked_state == BLANK_BG) {
            g_string_assign (title, "blank_bg");
        } else if (blanked_state == BLANK_TEXT) {
            g_string_assign (title, "blank_text");
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

void
update_miniview (const char *command)
{
    if (server_port == SERVER_PORT) {
        l_debug ("miniview time");
        GSocketClient *client = g_socket_client_new ();
        GSocketConnection *conn =
          g_socket_client_connect_to_host (client, dbhostname, 2348, NULL,
                                           NULL);
        if (conn != NULL) {
            GOutputStream *out =
              g_io_stream_get_output_stream (G_IO_STREAM (conn));
            g_output_stream_write (out, command, strlen (command), NULL,
                                   NULL);
            g_object_unref (conn);
        }
        g_object_unref (client);
    }
}

void
do_save (const char *options)
{
    l_debug ("Save as presentation");
    gchar **line = g_strsplit (options, ":", 2);
    gchar *cmd = g_strdup_printf ("playlist:%d", atoi (line[0]));
    do_display (cmd,TRUE);
    do_display ("display:0",TRUE);
    do_display ("next_page:0",TRUE);
    g_free (cmd);
    int count = 1;
    int last_item = -1;
    while (last_item < current_item) {
        l_debug ("%d", current_item);
        gchar *filename = g_strdup_printf ("%s/slide-%d.jpg", line[1], count);
        last_item = current_item;
        do_display ("next_page:0",TRUE);
        take_snapshot (filename,0);
        g_free (filename);
        count++;
    }
    g_strfreev (line);
}

GString *
do_query_json (const char *options)
{
    l_debug ("Query with response as JSON");
    gchar **line = g_strsplit (options, ":", 2);
    if (line[1] != NULL) {
        line[0] = g_utf8_strdown (line[0], -1);
        MYSQL_ROW row;
        MYSQL_RES *result;

        if (g_strcmp0(line[0],"lyricdb") == 0) {
            do_query (lyricDb,"%s",line[1]);
            result = mysql_store_result (lyricDb);
        } else if (g_strcmp0(line[0],"mediadb") == 0) {
            do_query (mediaDb,"%s",line[1]);
            result = mysql_store_result (mediaDb);
        } else if (g_strcmp0(line[0],"bibledb") == 0) {
            do_query (bibleDb,"%s",line[1]);
            result = mysql_store_result (bibleDb);
        } else {
            g_strfreev (line);
            return NULL;
        }

        if (result == NULL) return NULL;

        JsonGenerator *generator = json_generator_new();
        JsonNode *rootnode = json_node_new(JSON_NODE_OBJECT);

        JsonObject *resultnode = json_object_new();

        JsonArray *resultarray = json_array_new();

    
        unsigned int num_fields = mysql_num_fields(result);
        MYSQL_FIELD *fields;
        fields = mysql_fetch_fields(result);

        unsigned int i;
        while ((row = mysql_fetch_row (result))) {
            JsonObject *newobject = json_object_new();
            for(i = 0; i < num_fields; i++) {
                json_object_set_string_member(newobject,fields[i].name,row[i] ? row[i] : "NULL");
            }
            json_array_add_object_element(resultarray, newobject);
        }
        mysql_free_result (result);
        json_object_set_array_member(resultnode, "results",resultarray);
        json_node_set_object(rootnode,resultnode);
        json_generator_set_root(generator, rootnode);

        gchar *str = json_generator_to_data (generator,NULL);

        GString *ret = g_string_new(str);
        json_array_unref (resultarray);
        g_object_unref (generator);
        g_strfreev (line);
        return ret;
    }
    
    g_strfreev (line);
    return NULL;
}
