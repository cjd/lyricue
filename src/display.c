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

extern GHashTable *config;
extern gboolean windowed;
extern gchar *dbhostname;
extern gchar *geometry;
extern gboolean blanked_state;
extern gchar *default_bg;
extern gchar *current_bg;
extern MYSQL *mediaDb;


const ClutterColor black_colour = { 0x00, 0x00, 0x00, 0xff };

gchar *maintext_fgcol = "white";
gchar *maintext_bgcol = "black";
gchar *headtext_fgcol = "white";
gchar *headtext_bgcol = "black";
gchar *foottext_fgcol = "white";
gchar *foottext_bgcol = "black";

gchar *maintext_font = "";
gchar *headtext_font = "";
gchar *foottext_font = "";

ClutterActor *stage = NULL;
ClutterActor *maintext = NULL;
ClutterActor *maintext_old = NULL;
ClutterActor *headtext = NULL;
ClutterActor *headtext_old = NULL;
ClutterActor *foottext = NULL;
ClutterActor *foottext_old = NULL;
ClutterActor *background = NULL;
ClutterActor *background_old = NULL;

gfloat stage_width = 0;
gfloat stage_height = 0;
gfloat window_width = 0;
gfloat window_height = 0;
gfloat text_maxwidth = 0;
gfloat text_maxheight = 0;
gint bg_is_video = 0;

// Transition directions
#define NONE   0;
#define WAIT   1
#define UP     2
#define DOWN   4
#define RIGHT  8
#define LEFT   16
#define X_AXIS 32
#define Y_AXIS 64
#define Z_AXIS 128
#define NUM_TRANS 8

// Transition types
#define NORMAL     0
#define SLIDE_TEXT 1
#define WIPE       2
#define CLIP       3
#define ROTATE     4


int
create_main_window (int argc, char *argv[])
{
    clutter_gst_init (&argc, &argv);
    stage = clutter_stage_get_default ();
    stage_width = atof ((gchar *) g_hash_table_lookup (config, "Width"));
    stage_height = atof ((gchar *) g_hash_table_lookup (config, "Height"));
    gfloat wide = stage_width;
    gfloat high = stage_height;
    if (geometry != NULL && windowed) {
        gchar **line = g_strsplit (geometry, "x", 2);
        wide = atoi (line[0]);
        high = atoi (line[1]);
        if (high != 0) {
            clutter_actor_set_height (stage, high);
        }
        if (wide != 0) {
            clutter_actor_set_width (stage, wide);
        }
    }
    if (windowed) {
        clutter_stage_set_user_resizable (CLUTTER_STAGE (stage), TRUE);
    }
    clutter_stage_set_fullscreen (CLUTTER_STAGE (stage), !windowed);
    clutter_stage_set_color (CLUTTER_STAGE (stage), &black_colour);
    default_bg = (gchar *) g_hash_table_lookup (config, "BGImage");
    change_backdrop(default_bg, TRUE);
    clutter_actor_show_all (stage);
    double window_scale_w =
      (double) clutter_actor_get_width (stage) / (double) stage_width;
    double window_scale_h =
      (double) clutter_actor_get_height (stage) / (double) stage_height;
    clutter_actor_set_scale (stage, window_scale_w, window_scale_h);
    text_maxheight =
      stage_height -
      (atoi ((gchar *) g_hash_table_lookup (config, "OverscanV")) * 2);
    text_maxwidth =
      stage_width -
      (atoi ((gchar *) g_hash_table_lookup (config, "OverscanH")) * 2);
    l_debug ("Creating main window at %dx%d",
             (int) clutter_actor_get_width (stage),
             (int) clutter_actor_get_height (stage));


    // Setup events
    g_signal_connect (stage, "event", G_CALLBACK (input_cb), NULL);
    g_signal_connect (stage, "notify::width", G_CALLBACK (size_change), NULL);
    g_signal_connect (stage, "notify::height", G_CALLBACK (size_change),
                      NULL);

    maintext = clutter_group_new();
    maintext_old = clutter_group_new();
    headtext = clutter_group_new();
    headtext_old = clutter_group_new();
    foottext = clutter_group_new();
    foottext_old = clutter_group_new();

    clutter_container_add (CLUTTER_CONTAINER (stage), maintext, NULL);
    clutter_container_add (CLUTTER_CONTAINER (stage), headtext, NULL);
    clutter_container_add (CLUTTER_CONTAINER (stage), foottext, NULL);
    clutter_container_add (CLUTTER_CONTAINER (stage), maintext_old, NULL);
    clutter_container_add (CLUTTER_CONTAINER (stage), headtext_old, NULL);
    clutter_container_add (CLUTTER_CONTAINER (stage), foottext_old, NULL);
    clutter_actor_show_all (stage);
    return TRUE;
}

void
set_maintext (const gchar * text, int transition, gboolean wrap)
{
    l_debug("Setting maintext");

    // Finish off old animations
    if (CLUTTER_IS_ANIMATION(clutter_actor_get_animation(maintext))) clutter_animation_completed(clutter_actor_get_animation(maintext));
    if (CLUTTER_IS_ANIMATION(clutter_actor_get_animation(maintext_old))) clutter_animation_completed(clutter_actor_get_animation(maintext_old));

    ClutterActor *tmp = maintext_old;
    maintext_old = maintext;
    maintext = tmp;
    clear_group(maintext);
    create_outlined_text (maintext, text, maintext_font, maintext_fgcol, maintext_bgcol, wrap);
    gchar *horiloc =
      (gchar *) g_hash_table_lookup (config, "HorizontalLocation");
    gchar *vertloc =
      (gchar *) g_hash_table_lookup (config, "VerticalLocation");

    gfloat final_x = stage_width / 2;
    gfloat final_y = stage_height / 2;

    if (horiloc[0] == 'L') {
        final_x = clutter_actor_get_width (maintext) / 2;
    } else if (horiloc[0] == 'R') {
        final_x = stage_width - (clutter_actor_get_width (maintext) / 2);
    }
    if (vertloc[0] == 'T') {
        final_y =
          (clutter_actor_get_height (maintext) / 2) +
          clutter_actor_get_height (foottext);
    } else if (vertloc[0] == 'B') {
        final_y =
          stage_height - ((clutter_actor_get_height (maintext) / 2) +
                          clutter_actor_get_height (foottext));
    }

    clutter_actor_set_anchor_point_from_gravity (maintext,
                                                 CLUTTER_GRAVITY_CENTER);

    do_transition(maintext, maintext_old, transition, final_x, final_y);

    clutter_actor_raise_top(maintext);

}

void
set_headtext (const gchar * text, int transition, gboolean wrap)
{
    ClutterActor *tmp = headtext_old;
    headtext_old = headtext;
    headtext = tmp;
    clear_group(headtext);
    create_outlined_text (headtext, text, headtext_font, headtext_fgcol, headtext_bgcol, wrap);
    clutter_actor_set_anchor_point_from_gravity (headtext,
                                                 CLUTTER_GRAVITY_NORTH);
    clutter_actor_set_position (headtext, stage_width / 2, 0);
    clear_group(headtext_old);
}

void
set_foottext (const gchar * text, int transition, gboolean wrap)
{
    ClutterActor *tmp = foottext_old;
    foottext_old = foottext;
    foottext = tmp;
    clear_group(foottext);
    create_outlined_text (foottext, text, foottext_font, foottext_fgcol, foottext_bgcol, wrap);
    clutter_actor_set_anchor_point_from_gravity (foottext,
                                                 CLUTTER_GRAVITY_SOUTH);
    clutter_actor_set_position (foottext, stage_width / 2, stage_height);
    clear_group(foottext_old);
}

void
create_outlined_text (ClutterActor *group, const gchar * text, const gchar * font, const gchar * text_colour, const gchar * shadow_colour, gboolean wrap)
{
    ClutterActor *textline[6];
    int i;

    clear_group(group);

	if (text == NULL) text = g_strdup("");

    // Set Colours
    ClutterColor *fgcolour = clutter_color_new (0xFF, 0xFF, 0xFF, 0xFF);
    ClutterColor *bgcolour = clutter_color_new (0x00, 0x00, 0x00, 0xA0);
    clutter_color_from_string (bgcolour, shadow_colour);
    bgcolour->alpha = 0xA0;
    clutter_color_from_string (fgcolour, text_colour);

    // Get justification
    gchar *justify = (gchar *) g_hash_table_lookup (config, "Justification");

    for (i = 0; i <= 5; i++) {
        if (i == 2) {
            textline[i] = clutter_text_new_full (font, text, fgcolour);
        } else {
            textline[i] = clutter_text_new_full (font, text, bgcolour);
        }
        clutter_text_set_line_wrap (CLUTTER_TEXT (textline[i]), wrap);
        if (justify[0] == 'L') {
            clutter_text_set_line_alignment (CLUTTER_TEXT (textline[i]),
                                             PANGO_ALIGN_LEFT);
        } else if (justify[0] == 'R') {
            clutter_text_set_line_alignment (CLUTTER_TEXT (textline[i]),
                                             PANGO_ALIGN_RIGHT);
        } else {
            clutter_text_set_line_alignment (CLUTTER_TEXT (textline[i]),
                                             PANGO_ALIGN_CENTER);
        }
        clutter_text_set_use_markup (CLUTTER_TEXT (textline[i]), TRUE);
        clutter_actor_set_anchor_point_from_gravity (textline[i],
                                                     CLUTTER_GRAVITY_NORTH_WEST);
        clutter_container_add (CLUTTER_CONTAINER (group), textline[i], NULL);
        if (i == 5) {
            clutter_actor_set_position (textline[i], 4, 4);
        } else {
            clutter_actor_set_position (textline[i], ((i * 2) % 3),
                                        ((i * 2) / 3));
        }
        if (clutter_actor_get_width (textline[i]) > text_maxwidth) {
            clutter_actor_set_width (textline[i], text_maxwidth);
        }
    }
    clutter_actor_raise_top (textline[2]);
    clutter_actor_show_all(group);

//    return group;
}

void
change_backdrop (const gchar * id, gboolean video_loop)
{
    l_debug ("change backdrop to %s", id);
    if (g_strcmp0 (id, current_bg) == 0) {
        l_debug ("Backdrop ID same - not changing");
        return;
    }
    g_free(current_bg);
    current_bg = g_strdup(id);
    destroy_actor(background_old);
    background_old = background;
    background = NULL;
    //reset_timer(video_timer);
    gchar **line = g_strsplit (current_bg, ";", 2);

    if (g_strcmp0 (line[0], "db") == 0) {
        do_query(mediaDb, "SELECT format, description, data FROM media WHERE id=%s",line[1]);
        MYSQL_ROW row;
        MYSQL_RES *result;
        result = mysql_store_result (mediaDb);
        row = mysql_fetch_row (result);
        if (row != NULL) {
            if (g_strcmp0(row[0],"bg") == 0) {
                l_debug ("Changing backdrop colour to %s", row[1]);
                if (bg_is_video) g_source_remove(bg_is_video);
                bg_is_video = 0;
                ClutterColor *bgcolour = clutter_color_new(0,0,0,0);
                clutter_color_from_string (bgcolour, row[1]);
                background = clutter_rectangle_new_with_color (bgcolour);
                clutter_actor_set_size (background, stage_width, stage_height);
                clutter_actor_set_position (background, 0, 0);
                clutter_color_free(bgcolour);
            } else {
                l_debug ("Changing backdrop to dbimage");
                gchar *tempname;
                gint fd = g_file_open_tmp("lyricue-tmp.XXXXX", &tempname, NULL);
                if (fd > 0) {
                    if (bg_is_video) g_source_remove(bg_is_video);
                    bg_is_video = 0;
                    background = clutter_texture_new_from_file (tempname, NULL);
                    clutter_texture_set_keep_aspect_ratio (CLUTTER_TEXTURE
                                                        (background), TRUE);
                    clutter_actor_set_size (background, stage_width, stage_height);
                    clutter_actor_set_anchor_point_from_gravity (background,
                                                                CLUTTER_GRAVITY_CENTER);
                    clutter_actor_set_position (background, stage_width / 2,
                                             stage_height / 2);
                }
                g_free(tempname);
            }
        }
    } else if (g_strcmp0 (line[0], "solid") == 0) {
        gchar **col = g_strsplit (line[1], ":",2);
        l_debug ("Changing backdrop colour to %s", col[0]);
        if (bg_is_video) g_source_remove(bg_is_video);
        bg_is_video = 0;
        ClutterColor *bgcolour = clutter_color_new(0,0,0,0);
        clutter_color_from_string (bgcolour, col[0]);
        background = clutter_rectangle_new_with_color (bgcolour);
        clutter_actor_set_size (background, stage_width, stage_height);
        clutter_actor_set_position (background, 0, 0);
        clutter_color_free(bgcolour);
        g_free(col);
    } else if (g_strcmp0 (line[0], "dir") == 0) {
        GFileInfo *info = g_file_query_info (g_file_new_for_path (line[1]),
                                             G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE,
                                             G_FILE_QUERY_INFO_NONE, NULL,
                                             NULL);
        if (!info) {
            l_debug ("Backdrop not loadable");
            background = background_old;
            background_old = NULL;
            return;
        }
        if (g_content_type_is_a
            (g_file_info_get_content_type (info), "video/*")) {
            l_debug ("Backdrop is a video");
            background = clutter_gst_video_texture_new ();
            clutter_media_set_filename (CLUTTER_MEDIA (background), line[1]);
            clutter_actor_set_anchor_point_from_gravity (background,
                                                         CLUTTER_GRAVITY_CENTER);
            clutter_actor_set_position (background, stage_width / 2,
                                        stage_height / 2);
            clutter_texture_set_keep_aspect_ratio (CLUTTER_TEXTURE
                                                   (background), TRUE);
            clutter_actor_set_size (background, stage_width, stage_height);
            clutter_media_set_playing (CLUTTER_MEDIA (background), TRUE);
            g_signal_connect (background, "eos", G_CALLBACK(loop_video), &video_loop);
            bg_is_video = g_timeout_add_seconds(1, (GSourceFunc) update_tracker, NULL);
            
        } else
          if (g_content_type_is_a
              (g_file_info_get_content_type (info), "image/*")) {
            l_debug ("Backdrop is an image");
            if (bg_is_video) g_source_remove(bg_is_video);
            bg_is_video = 0;
            background = clutter_texture_new_from_file (line[1], NULL);
            clutter_texture_set_keep_aspect_ratio (CLUTTER_TEXTURE
                                                   (background), TRUE);
            clutter_actor_set_size (background, stage_width, stage_height);
            clutter_actor_set_anchor_point_from_gravity (background,
                                                         CLUTTER_GRAVITY_CENTER);
            clutter_actor_set_position (background, stage_width / 2,
                                        stage_height / 2);
        } else {
            l_debug ("Unknown Filetype %s",
                     g_file_info_get_content_type (info));
            return;
        }
        g_object_unref (info);
    }
    if (background) {
        clutter_container_add (CLUTTER_CONTAINER (stage), background, NULL);
        clutter_actor_lower_bottom (background);
    } else {
        background = background_old;
        background_old = NULL;
        clutter_actor_lower_bottom (background);
    }

    // Set text colours
    do_query(mediaDb,"SELECT textcolour, shadowcolour FROM media WHERE id=\"%s\" OR CONCAT(\"db;\", id)=\"%s\"", current_bg, current_bg);
    MYSQL_RES *result;
    MYSQL_ROW row;
    result = mysql_store_result (mediaDb);
    row = mysql_fetch_row (result);
    if (row != NULL) {
        if ((g_strcmp0(maintext_fgcol,row[0]) != 0) || (g_strcmp0(maintext_bgcol, row[1]) != 0)) {
            maintext_fgcol = g_strdup(row[0]);
            headtext_fgcol = g_strdup(row[0]);
            foottext_fgcol = g_strdup(row[0]);
            maintext_bgcol = g_strdup(row[1]);
            headtext_bgcol = g_strdup(row[1]);
            foottext_bgcol = g_strdup(row[1]);
        }
    } else {
        if ((g_strcmp0(maintext_fgcol,(gchar *) g_hash_table_lookup (config, "Colour")) != 0) || (g_strcmp0(maintext_bgcol, (gchar *) g_hash_table_lookup (config, "ShadowColour")) != 0)) {
            maintext_fgcol = (gchar *) g_hash_table_lookup (config, "Colour");
            maintext_bgcol = (gchar *) g_hash_table_lookup (config, "ShadowColour");
            headtext_fgcol = (gchar *) g_hash_table_lookup (config, "Colour");
            headtext_bgcol = (gchar *) g_hash_table_lookup (config, "ShadowColour");
            foottext_fgcol = (gchar *) g_hash_table_lookup (config, "Colour");
            foottext_bgcol = (gchar *) g_hash_table_lookup (config, "ShadowColour");
        }
    }
    

    // Fade out old background
    if (CLUTTER_IS_ACTOR(background_old)) {
    clutter_actor_animate(background_old, CLUTTER_LINEAR,500,
                          "opacity", 0,
                          "signal-swapped-after::completed", destroy_actor, background_old,
                          NULL);
    }

}

gboolean
input_cb (ClutterStage * mystage, ClutterEvent * event, gpointer user_data)
{

    gboolean handled = FALSE;
    switch (event->type) {
        case CLUTTER_KEY_PRESS:
            switch (clutter_event_get_key_symbol (event)) {
                case CLUTTER_Q:
                case CLUTTER_Escape:
                    clear_group(stage);
                    clutter_main_quit ();
                    handled = TRUE;
                    break;
                case CLUTTER_Left:
                case CLUTTER_KP_Left:
                case CLUTTER_Page_Up:
                    do_display ("prev_page:");
                    break;
                case CLUTTER_Right:
                case CLUTTER_KP_Right:
                case CLUTTER_Page_Down:
                    do_display ("next_page:");
                    break;
                case CLUTTER_Up:
                case CLUTTER_KP_Up:
                    do_display ("prev_song:");
                    break;
                case CLUTTER_Down:
                case CLUTTER_KP_Down:
                    do_display ("next_song:");
                    break;
                case CLUTTER_0:
                case CLUTTER_KP_0:
                case CLUTTER_KP_Insert:
                case CLUTTER_c:
                case CLUTTER_x:
                    if (blanked_state) {
                        do_display ("current:");
                    } else {
                        do_blank (NULL);
                    }
                    break;
                case CLUTTER_b:
                    if (blanked_state) {
                        do_display ("current:");
                    } else {
                        do_blank ("solid;black:");
                    }
                    break;
                case CLUTTER_p:
                case CLUTTER_space:
                    media_pause ();
                    break;
                case CLUTTER_1:
                case CLUTTER_KP_1:
                    do_display ("page:1");
                    break;
                case CLUTTER_2:
                case CLUTTER_KP_2:
                    do_display ("page:2");
                    break;
                case CLUTTER_3:
                case CLUTTER_KP_3:
                    do_display ("page:3");
                    break;
                case CLUTTER_4:
                case CLUTTER_KP_4:
                    do_display ("page:4");
                    break;
                case CLUTTER_5:
                case CLUTTER_KP_5:
                    do_display ("page:5");
                    break;
                case CLUTTER_6:
                case CLUTTER_KP_6:
                    do_display ("page:6");
                    break;
                case CLUTTER_7:
                case CLUTTER_KP_7:
                    do_display ("page:7");
                    break;
                case CLUTTER_8:
                case CLUTTER_KP_8:
                    do_display ("page:8");
                    break;
                case CLUTTER_9:
                case CLUTTER_KP_9:
                    do_display ("page:9");
                    break;
                default:
                    l_debug ("Unknown key");
                    break;
            }
            break;
        default:
            break;
    }
    return handled;
}

void
size_change (ClutterActor * myactor)
{
    gfloat new_window_width, new_window_height;
    clutter_actor_get_size (stage, &new_window_width, &new_window_height);
    if (((int) new_window_width != window_width)
        || ((int) new_window_height != window_height)) {
        window_width = (int) new_window_width;
        window_height = (int) new_window_height;
        gfloat window_scale_w = new_window_width / stage_width;
        gfloat window_scale_h = new_window_height / stage_height;
        l_debug ("Resizing main window to %.0fx%.0f", new_window_width,
                 new_window_height);
        clutter_actor_set_scale (stage, window_scale_w, window_scale_h);
    }
}

void
loop_video (ClutterActor * video, gboolean * video_loop)
{
    if (video_loop) {
        clutter_media_set_progress (CLUTTER_MEDIA (video), 0);
    } else {
        if (bg_is_video) g_source_remove(bg_is_video);
    }
}

void
media_pause ()
{
    if (bg_is_video) {
        clutter_media_set_playing (CLUTTER_MEDIA (background),
                                   !clutter_media_get_playing (CLUTTER_MEDIA
                                                               (background)));
    }
}

void
load_font_defaults()
{
    maintext_font  = (gchar *) g_hash_table_lookup (config, "Main");
    headtext_font  = (gchar *) g_hash_table_lookup (config, "Header");
    foottext_font  = (gchar *) g_hash_table_lookup (config, "Footer");
}

void
clear_group(ClutterActor *actor)
{
    if (actor != NULL) {
        if (CLUTTER_IS_GROUP(actor)) {
            clutter_group_remove_all(CLUTTER_GROUP(actor));
        }
    }
}

void
destroy_actor(ClutterActor *actor)
{
    if (actor != NULL) {
        if (CLUTTER_IS_ACTOR(actor)) {
            clutter_actor_destroy(actor);
            actor=NULL;
        }
    }
}

void 
do_transition(ClutterActor *new, ClutterActor *old, int transition, gfloat final_x, gfloat final_y)
{

    gfloat new_start_x, new_start_y, new_final_x, new_final_y;
    gfloat old_start_x, old_start_y, old_final_x, old_final_y;
    if (CLUTTER_IS_ACTOR(new)) clutter_actor_get_position(new, &new_start_x, &new_start_y);
    if (CLUTTER_IS_ACTOR(old)) clutter_actor_get_position(old, &old_start_x, &old_start_y);
    old_final_x = old_start_x;
    old_final_y = old_start_y;
    new_start_x = final_x;
    new_start_y = final_y;
    new_final_x = final_x;
    new_final_y = final_y;
    // Transition
    int out_direction = transition % (2 << NUM_TRANS );
    transition = transition >> NUM_TRANS;
    int in_direction = transition % (2 << NUM_TRANS);
    int effect = transition >> NUM_TRANS;

    // Default positioning
    clutter_actor_set_position (new, new_final_x, new_final_y);
    clutter_actor_set_rotation (new, CLUTTER_X_AXIS, 0,0,0,0);
    clutter_actor_set_rotation (new, CLUTTER_Y_AXIS, 0,0,0,0);
    clutter_actor_set_rotation (new, CLUTTER_Z_AXIS, 0,0,0,0);

    switch (effect) {
        case SLIDE_TEXT:
            if (in_direction & UP) {
                new_start_y = new_start_y * 3;
            } else if (in_direction & DOWN) {
                new_start_y = -new_start_y;
            }
            if (in_direction & LEFT) {
                new_start_x = new_start_x * 3;
            } else if (in_direction & RIGHT) {
                new_start_x = -new_start_x;
            }
            clutter_actor_set_position (new, new_start_x, new_start_y);
            clutter_actor_animate(new, CLUTTER_LINEAR,1000,
                                  "y", new_final_y,
                                  "x", new_final_x,
                                  NULL);

            if (out_direction & UP) {
                old_final_y = -old_final_y;
            } else if (out_direction & DOWN) {
                old_final_y = old_final_y * 3;
            }
            if (out_direction & LEFT) {
                old_final_x = -old_final_x;
            } else if (out_direction & RIGHT) {
                old_final_x = old_final_x * 3;
            }
            clutter_actor_set_position (old, old_start_x, old_start_y);
            clutter_actor_animate(old, CLUTTER_LINEAR,1000,
                                  "y", old_final_y,
                                  "x", old_final_x,
                                  NULL);
            break;
        case ROTATE:
            if (in_direction & X_AXIS) {
                clutter_actor_set_rotation (new, CLUTTER_X_AXIS,90,0,0,0);
                clutter_actor_animate(new, CLUTTER_LINEAR,1000, "rotation-angle-x", 0, NULL);
                clutter_actor_animate(old, CLUTTER_LINEAR,1000, "rotation-angle-x", (gfloat)-90 , "signal-swapped-after::completed", clear_group, old, NULL);
            }
            if (in_direction & Y_AXIS) {
                clutter_actor_set_rotation (new, CLUTTER_Y_AXIS,90,0,0,0);
                clutter_actor_animate(new, CLUTTER_LINEAR,1000, "rotation-angle-y", 0, NULL);
                clutter_actor_animate(old, CLUTTER_LINEAR,1000, "rotation-angle-y", (gfloat)-90 , "signal-swapped-after::completed", clear_group, old, NULL);
            }
            if (in_direction & Z_AXIS) {
                clutter_actor_set_rotation (new, CLUTTER_Z_AXIS,90,0,0,0);
                clutter_actor_animate(new, CLUTTER_LINEAR,1000, "rotation-angle-z", 0, NULL);
                clutter_actor_animate(old, CLUTTER_LINEAR,1000, "rotation-angle-z", (gfloat)-90 , "signal-swapped-after::completed", clear_group, old, NULL);
            }
        case WIPE:
        case CLIP:
        case NORMAL:
        default:
            clutter_actor_set_opacity(new, 0);
            clutter_actor_animate(new, CLUTTER_LINEAR,1000,
                          "opacity", 0xff, NULL);
            clutter_actor_animate(old, CLUTTER_LINEAR,1000,
                          "opacity", 0,
                          "signal-swapped-after::completed", clear_group,
                          old, NULL);
            break;
    }
}
