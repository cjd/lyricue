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

MYSQL *lyricDb = NULL;
MYSQL *mediaDb = NULL;
extern GHashTable *config;
extern char *dbhostname;

int
db_select ()
{
    lyricDb = db_connect ("lyricDb", "error");
    mediaDb = db_connect ("mediaDb", "error");
    return TRUE;
}

int
db_deselect ()
{
    db_disconnect (lyricDb);
    db_disconnect (mediaDb);
    return TRUE;
}

MYSQL *
db_connect (const char *dbname, const char *dberror)
{
    MYSQL *tempDb = mysql_init (NULL);
    if (tempDb == NULL) {
        g_warning ("Error %u: %s", mysql_errno (tempDb),
                   mysql_error (tempDb));
        exit (1);
    }
    my_bool reconnect = 1;
    mysql_options (tempDb, MYSQL_OPT_RECONNECT, &reconnect);

    if (mysql_real_connect
        (tempDb, dbhostname, "lyric", "", dbname, 0, NULL, 0) == NULL) {
        g_warning ("Error %u: %s", mysql_errno (tempDb),
                   mysql_error (tempDb));
        exit (1);
    }
    // Re-run for mysql versions < 5.0.19
    mysql_options (tempDb, MYSQL_OPT_RECONNECT, &reconnect);
    mysql_set_character_set (tempDb, "utf8");

    return tempDb;
}

int
db_disconnect (MYSQL * dbconnection)
{
    mysql_close (dbconnection);
    return TRUE;
}

void
load_configuration ()
{
    l_debug ("Loading configuration");

    if (config != NULL) g_hash_table_remove_all(config);
    config = g_hash_table_new (g_str_hash, g_str_equal);
    MYSQL_ROW row;
    MYSQL_RES *result;
    int res =
      do_query (lyricDb, "SELECT config_key,config_value FROM config");
    if (res != 0) {
        return;
    }
    result = mysql_store_result (lyricDb);
    gboolean conf_found=FALSE;
    while ((row = mysql_fetch_row (result))) {
	conf_found=TRUE;
        g_hash_table_insert (config, g_strdup (row[0]), g_strdup (row[1]));
        l_debug ("Config \"%s\" set to \"%s\"", row[0], row[1]);
    }
    if (!conf_found) {
        l_debug("No configuration found - load lyricue to setup");
        exit(1);
    }
    load_font_defaults();
    mysql_free_result (result);
}

int
do_query (MYSQL * dbconnection, const gchar * format, ...)
{
    GString *query = g_string_new (NULL);
    va_list argp;
    va_start (argp, format);
    g_string_vprintf (query, format, argp);
    va_end (argp);

    l_debug ("SQL: %s", query->str);
    if (mysql_query (dbconnection, query->str)) {
        l_debug (_("SQL Error %u: %s"), mysql_errno (dbconnection),
                 mysql_error (dbconnection));
    }
    g_string_free (query, TRUE);
    return mysql_errno (lyricDb);
}
