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

void set_maintext(const gchar *text,
                  int transition, 
                  gboolean wrap);

void set_headtext(const gchar *text,
                  int transition, 
                  gboolean wrap);

void set_foottext(const gchar *text,
                  int transition, 
                  gboolean wrap);

int create_main_window(int argc, char *argv[]);

void create_outlined_text (ClutterActor *group,
                           const gchar *text,
                           const gchar *font,
                           const gchar *text_colour,
                           const gchar *shadow_colour,
                           gboolean wrap);

void change_backdrop (const gchar * id, gboolean loop);

gboolean input_cb (ClutterStage *stage, 
                   ClutterEvent *event,
                   gpointer      user_data);

void size_change (ClutterActor *myactor);

void loop_video (ClutterActor *video, gboolean *video_loop);

void media_pause ();

void load_font_defaults ();

void clear_group(ClutterActor *actor);
void destroy_actor(ClutterActor *actor);

void do_transition(ClutterActor *new,
                   ClutterActor *old,
                   int          transition,
                   gfloat       final_x,
                   gfloat       final_y);
