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

extern MYSQL *bibleDb;
extern ClutterActor *maintext;
extern ClutterActor *headtext;
extern gfloat stage_height;
gchar *bible_table = NULL;
gchar *bible_name = NULL;
gboolean is_sword = FALSE;
GRegex *re_newline = NULL;
GRegex *re_book = NULL;
GRegex *re_maxchapter = NULL;
GRegex *re_maxverse = NULL;


gchar *
do_grab_verse (const gchar * verse)
{
    l_debug ("Show verse %s", verse);
    gchar *book;
    int chapter_start, chapter_end, verse_start, verse_end;
    gchar **line = g_strsplit_set (verse, ":-", 5);
    book = g_strdup(line[0]);
    chapter_start = atoi (line[1]);
    verse_start = atoi (line[2]);
    chapter_end = atoi (line[3]);
    verse_end = atoi (line[4]);
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
    if (re_book == NULL) {
        re_book = g_regex_new ("^.*\\s(\\d)", G_REGEX_MULTILINE, 0, NULL);
    }
    if (re_newline == NULL) {
        re_newline = g_regex_new("\n\n", 0, 0, NULL);
    }
    int re_size = strlen(bible_table)+5;
    gchar *bible_re = g_malloc(re_size);
    g_snprintf(bible_re, re_size, "\\(%s\\)",bible_table);
    GRegex *re_bible = g_regex_new(bible_re, G_REGEX_MULTILINE, 0, NULL);
    gchar *text = NULL;
    gchar *text2 = NULL;
    gchar *text3 = NULL;
    text = g_regex_replace (re_book, output, -1, 0, "\\1", 0, NULL);
    text2 = g_regex_replace (re_bible, text, -1, 0, "", 0, NULL);
    text3 = g_regex_replace (re_newline, text2, -1, 0, "\n", 0, NULL);
    g_free(text2);
    g_free(text);

    return text3;
}

gchar *
do_grab_verse_db (const gchar * book, int chapter_start, int chapter_end,
                  int verse_start, int verse_end)
{
    l_debug ("Grabbing verse from db - %s %d:%d - %d:%d", book, chapter_start,
             verse_start, chapter_end, verse_end);
    MYSQL_ROW row;
    MYSQL_RES *result;

    if (bible_table == NULL) return "";

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
    if ((bible == NULL) || (g_strcmp0(bible,"")==0)) {
        is_sword=FALSE;
        bibleDb=NULL;
        return;
    }
    gchar **line = g_strsplit (bible, ":", 2);
    if ((line[1] == NULL) || (g_strcmp0(line[1],"") == 0)) return;
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

GString *
do_bible (const gchar * options)
{
    gchar **line = g_strsplit(options, ":", 2);   
    GString *retval = NULL;
    if (g_ascii_strncasecmp(line[0],"available",9) == 0) {
        retval = get_bibles();
    } else if (g_ascii_strncasecmp(line[0],"maxchapter",9) == 0) {
        retval = get_maxchapter(line[1]);
    } else if (g_ascii_strncasecmp(line[0],"maxverse",8) == 0) {
        retval = get_maxverse(line[1]);
    } else if (g_ascii_strncasecmp(line[0],"verse",9) == 0) {
        retval = show_verse(line[1], TRUE);
    } else if (g_ascii_strncasecmp(line[0],"verse_start",11) == 0) {
        retval = show_verse(line[1], FALSE);
    }
    g_strfreev(line);
    return retval;
}

GString *
get_bibles()
{
    JsonGenerator *generator = json_generator_new();
    JsonNode *rootnode = json_node_new(JSON_NODE_OBJECT);
    JsonObject *resultnode = json_object_new();
    JsonArray *resultarray = json_array_new();
    
    // Find sword bibles
    gchar *output = NULL;
    g_spawn_command_line_sync("diatheke -b system -k modulelist", &output, NULL, NULL, NULL);
    g_strchomp(output);
    gchar **line = g_strsplit(output,"\n",0);
    int linenum=0;
    while (line[linenum] != NULL) {
        if (g_ascii_strncasecmp(line[linenum],"Biblical Texts:",15) == 0) {
            linenum++;
            while (line[linenum] != NULL) {
                if (g_ascii_strncasecmp(line[linenum],"Commentaries:",13) == 0) {
                    while (line[linenum] != NULL) {
                        linenum++;
                    }
                    linenum--;
                } else {
                    gchar **bible = g_strsplit(line[linenum], " : ",2);
                    JsonObject *newobject = json_object_new();
                    json_object_set_string_member(newobject, "type", "sword");
                    json_object_set_string_member(newobject, "name", bible[0]);
                    json_object_set_string_member(newobject, "description", bible[1]);
                    json_array_add_object_element(resultarray, newobject);
                    g_strfreev(bible);
                }
                linenum++;
            }
            linenum--;
        }
        linenum++;
    }
    g_free(output);


    // Find bibleDb bibles
    if (bibleDb != NULL) {
        MYSQL_RES *result;
        MYSQL_ROW row;
        result = mysql_list_tables(bibleDb, NULL);
        while ((row = mysql_fetch_row(result))) {
            int res = do_query(bibleDb, "SELECT verse FROM %s WHERE book=\"Bible\"", row[0]);
            if (res == 0) {
                MYSQL_RES *result2;
                MYSQL_ROW row2;
                result2 = mysql_store_result(bibleDb);
                row2 = mysql_fetch_row(result2);
                JsonObject *newobject = json_object_new();
                json_object_set_string_member(newobject, "type", "db");
                json_object_set_string_member(newobject, "name", row[0]);
                json_object_set_string_member(newobject, "description", row2[0]);
                json_array_add_object_element(resultarray, newobject);
                
            }
        }
    }
    json_object_set_array_member(resultnode, "results",resultarray);
    json_node_set_object(rootnode,resultnode);
    json_generator_set_root(generator, rootnode);
    gchar *str = json_generator_to_data (generator,NULL);
    GString *ret = g_string_new(str);
    json_array_unref (resultarray);
    g_object_unref (generator);
    g_strfreev(line);
    return ret;
}

GString *
get_maxchapter(const gchar * book)
{
    GString *retval = g_string_new(NULL);
    if (is_sword) {
        if (re_maxchapter == NULL) {
            re_maxchapter = g_regex_new ("^.* ([0-9]*):[0-9].*$", G_REGEX_MULTILINE,0, NULL);
        }
        GString *command = g_string_new(NULL);
        g_string_printf(command, "diatheke -b %s -e UTF8 -k '%s'", bible_table, book);
        gchar *output = NULL;
        l_debug ("Command: %s", command->str);
        g_spawn_command_line_sync (g_string_free (command, FALSE), &output, NULL, NULL, NULL);
        gchar **line = g_strsplit(output,"\n",0);
        int linenum=0;
        int maxchapter=0;
        while (line[linenum] != NULL) {
            gchar *text = NULL;
            text = g_regex_replace(re_maxchapter, line[linenum], -1, 0, "\\1", 0, NULL);
            if (atoi(text) != 0) {
                maxchapter=atoi(text);
            }
            linenum++;
        }
        g_strfreev(line);
        g_string_printf(retval, "%d", maxchapter);
        return retval;
    } else {
        MYSQL_ROW row;
        MYSQL_RES *result;
        do_query(bibleDb, "SELECT MAX(chapternum) FROM %s WHERE book LIKE \"%s%%\"", bible_table, book);
        result = mysql_store_result(bibleDb);
        if ((row = mysql_fetch_row(result))) {
l_debug("%s",row[0]);
            g_string_printf(retval, "%s",row[0]);
            return retval;
        }
    }
    return NULL;
}

GString *
get_maxverse(const gchar * options)
{
    gchar **verse_split = g_strsplit(options,";",2);
    GString *retval = g_string_new(NULL);
    if (is_sword) {
        if (re_maxverse == NULL) {
            re_maxverse = g_regex_new ("^.* [0-9]*:([0-9]*): .*$", G_REGEX_MULTILINE,0, NULL);
        }
        GString *command = g_string_new(NULL);
        g_string_printf(command, "diatheke -b %s -e UTF8 -k '%s' %s", bible_table, verse_split[0], verse_split[1]);
        gchar *output = NULL;
        l_debug ("Command: %s", command->str);
        g_spawn_command_line_sync (g_string_free (command, FALSE), &output, NULL, NULL, NULL);
        gchar **line = g_strsplit(output,"\n",0);
        int linenum=0;
        int maxverse=0;
        while (line[linenum] != NULL) {
            gchar *text = NULL;
            text = g_regex_replace(re_maxverse, line[linenum], -1, 0, "\\1", 0, NULL);
            if (atoi(text) != 0) {
                maxverse=atoi(text);
            }
            linenum++;
        }
        g_strfreev(line);
        g_strfreev(verse_split);
        g_string_printf(retval, "%d", maxverse);
        return retval;
    } else {
        MYSQL_ROW row;
        MYSQL_RES *result;
        do_query(bibleDb, "SELECT MAX(versenum) FROM %s WHERE book LIKE \"%s%%\" AND chapternum=\"%s\"", bible_table, verse_split[0], verse_split[1]);
        result = mysql_store_result(bibleDb);
        if ((row = mysql_fetch_row(result))) {
            g_string_printf(retval, "%s",row[0]);
            g_strfreev(verse_split);
            return retval;
        }
    }
    g_strfreev(verse_split);
    return NULL;
}

GString *
show_verse(const gchar * verse_in, gboolean trim_end)
{
    GString *verse = g_string_new(parse_special(verse_in));
    l_debug("Show Verse: %s", verse->str);
    gchar *verse_text = do_grab_verse(verse->str);
    set_foottext("",NO_EFFECT,TRUE);
    set_headtext(verse->str,NO_EFFECT,TRUE);
    set_maintext(verse_text,NO_EFFECT,TRUE);
    gfloat width, height;
    gfloat hwidth, hheight;
    clutter_actor_get_size(maintext, &width, &height);
    clutter_actor_get_size(headtext, &hwidth, &hheight);
    l_debug("%s Size %fx%f",verse->str, width,height);
    while (height >= (stage_height-hheight)) {
            gchar **line = g_strsplit_set (verse->str, ":-", 5);
            if (!trim_end) {
                int verse_end = atoi(line[4]);
                g_string_printf(verse, "%s:%s:%s-%s:%d",line[0],line[1],line[2],line[3],verse_end-1);
            } else {
                int verse_start = atoi(line[2]);
                g_string_printf(verse, "%s:%s:%d-%s:%s",line[0],line[1],verse_start+1,line[3],line[4]);
            }
            g_strfreev(line);
            gchar *verse_text = do_grab_verse(verse->str);
            set_maintext(verse_text,NO_EFFECT,TRUE);
            g_free(verse_text);
            clutter_actor_get_size(maintext, &width, &height);
            l_debug("%s Size %fx%f",verse->str,width,height);
    }
    set_headtext(verse->str,NO_EFFECT,1);
    return verse;
}

