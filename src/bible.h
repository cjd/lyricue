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

void bible_load(const gchar *bible);
gchar * do_grab_verse(const gchar *verse); 
gchar * do_grab_verse_sword(const gchar *book,
                            int chapter_start, 
                            int chapter_end, 
                            int verse_start, 
                            int verse_end);
gchar * do_grab_verse_db(const gchar *book,
                         int chapter_start, 
                         int chapter_end, 
                         int verse_start, 
                         int verse_end);
GString * do_bible(const gchar * options);
GString * get_bibles();
GString * get_maxchapter(const gchar * book);
GString * get_maxverse(const gchar * options);
GString * show_verse(const gchar * verse, gboolean trim_end);
