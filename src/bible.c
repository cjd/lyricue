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
#include "bible.h"

MYSQL *bibleDb;
gchar *bible_table = NULL;
gchar *bible_name = NULL;
gboolean is_sword = FALSE;

gchar *
do_grab_verse (const gchar * verse)
{
    l_debug ("Show verse %s", verse);
    gchar *book;
    int chapter_start, chapter_end, verse_start, verse_end;
    gchar **line = g_strsplit (verse, ":", 2);
    book = g_strdup (line[0]);
    gchar **verses = g_strsplit (line[1], "-", 2);
    gchar **verseref = g_strsplit (verses[0], ":", 2);
    chapter_start = atoi (verseref[0]);
    verse_start = atoi (verseref[1]);
    verseref = g_strsplit (verses[1], ":", 2);
    chapter_end = atoi (verseref[0]);
    verse_end = atoi (verseref[1]);
    if (is_sword) {
        return do_grab_verse_sword (book, chapter_start, chapter_end,
                                    verse_start, verse_end);
    } else {
        return do_grab_verse_db (book, chapter_start, chapter_end,
                                 verse_start, verse_end);
    }
}

gchar *
do_grab_verse_sword (const gchar * book, int chapter_start, int chapter_end,
                     int verse_start, int verse_end)
{
    l_debug ("Grabbing verse from sword - %s %d:%d - %d:%d (%s)", book,
             chapter_start, verse_start, chapter_end, verse_end, bible_table);
    GString *command = g_string_new (NULL);
    g_string_printf (command, "diatheke -b %s -e UTF8 -k '%s' %d:%d-%d:%d",
                     bible_table, book, chapter_start, verse_start,
                     chapter_end, verse_end);
    gchar *output = NULL;
    l_debug ("Command: %s", command->str);
    g_spawn_command_line_sync (g_string_free (command, FALSE), &output, NULL,
                               NULL, NULL);
    g_strchomp (output);
    GRegex *re = NULL;
    re = g_regex_new ("^.*\\s(\\d)", G_REGEX_MULTILINE, 0, NULL);
    gchar *text = NULL;
    text = g_regex_replace (re, output, -1, 0, "\\1", 0, NULL);

    return text;
}

gchar *
do_grab_verse_db (const gchar * book, int chapter_start, int chapter_end,
                  int verse_start, int verse_end)
{
    l_debug ("Grabbing verse from db - %s %d:%d - %d:%d", book, chapter_start,
             verse_start, chapter_end, verse_end);
    MYSQL_ROW row;
    MYSQL_RES *result;

    if (chapter_start == chapter_end) {
        do_query (bibleDb,
                  "SELECT chapternum,versenum,verse FROM %s WHERE book LIKE \"%s\%\" AND chapternum=%d AND versenum >=%d AND versenum <=%d",
                  bible_table, book, chapter_start, verse_start, verse_end);
    } else {
        do_query (bibleDb,
                  "SELECT chapternum,versenum,verse FROM %s WHERE book LIKE \"%s\%\" AND ((chapternum = %d AND versenum > %d) OR (chapternum > %d AND chapternum < %d) OR (chapternum = %d AND versenum < %d))",
                  bible_table, book, chapter_start, verse_start,
                  chapter_start, chapter_end, chapter_end, verse_end);

    }
    result = mysql_store_result (bibleDb);
    GString *text = g_string_new (NULL);
    while ((row = mysql_fetch_row (result))) {
        g_string_append_printf (text, "%s:%s %s\n", row[0], row[1], row[2]);
    }
    return g_string_free (text, FALSE);
}

void
bible_load (const gchar * bible)
{
    if (bible == NULL) return;
    gchar **line = g_strsplit (bible, ":", 2);
    if (line[1] == NULL) return;
    gchar **desc = g_strsplit (line[1], ";", 2);
    bible_name = g_strdup (desc[1]);
    if (g_strcmp0 (desc[0], "db") == 0) {
        is_sword = FALSE;
        gchar **loc = g_strsplit (line[0], "@", 2);
        l_debug ("Loading Bible DB %s from %s", loc[0], loc[1]);
        bible_table = g_strdup (loc[0]);
        bibleDb = db_connect (loc[1], "error");
    } else {
        bible_table = g_strdup (line[0]);
        l_debug ("Loading Sword bibles %s", line[0]);
        is_sword = TRUE;
    }
}
