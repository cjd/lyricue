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
extern unsigned long windowid;
extern int server_port;


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
gchar *osdtext_font  = "";

GtkWidget *window = NULL;
GtkWidget *clutter_widget = NULL;
ClutterActor *stage = NULL;
ClutterActor *maintext = NULL;
ClutterActor *maintext_old = NULL;
ClutterActor *headtext = NULL;
ClutterActor *headtext_old = NULL;
ClutterActor *foottext = NULL;
ClutterActor *foottext_old = NULL;
ClutterActor *background = NULL;
ClutterActor *background_old = NULL;
ClutterActor *osdtext = NULL;
ClutterActor *osdtext_bg = NULL;

gfloat stage_width = 0;
gfloat stage_height = 0;
gfloat window_width = 0;
gfloat window_height = 0;
gfloat text_maxwidth = 0;
gfloat text_maxheight = 0;
guint bg_is_video = 0;

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
#define DEFAULT    0
#define NOTRANS    1
#define FADE       2
#define SLIDE_TEXT 3
#define ROTATE     4

int
create_main_window (int argc, char *argv[])
{
    clutter_gst_init (&argc, &argv);
    gtk_init (&argc, &argv);
    stage_width = atof ((gchar *) g_hash_table_lookup (config, "Width"));
    stage_height = atof ((gchar *) g_hash_table_lookup (config, "Height"));
    if (geometry == NULL) {
        geometry = (gchar *) g_hash_table_lookup (config, "GeometryOverride");
    }
    if (windowid == 0) {
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        if (geometry != NULL && (g_utf8_strlen(geometry,10) > 0)) {
            if (!  gtk_window_parse_geometry(GTK_WINDOW (window),geometry)) {
                l_debug("Failed to parse geometry '%s'", geometry);
            } else {
                l_debug("Geometry '%s'", geometry);
            }
        }
        if (!windowed) gtk_window_fullscreen(GTK_WINDOW (window));
    } else {
        window = gtk_plug_new(windowid);
    }
    g_snprintf(argv[0],strlen(argv[0]),"lyricue_dis:%d",server_port);
    /* Create the clutter widget: */
    clutter_widget = gtk_clutter_embed_new ();
    gtk_container_add(GTK_CONTAINER(window), clutter_widget);
    gtk_widget_show_all (window);

    stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutter_widget));
    clutter_stage_set_color (CLUTTER_STAGE (stage), &black_colour);
    default_bg = (gchar *) g_hash_table_lookup (config, "BGImage");
    change_backdrop(default_bg, TRUE);
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

    // Setup events
    g_signal_connect (stage, "destroy", G_CALLBACK (exit), NULL);
    g_signal_connect (stage, "event", G_CALLBACK (input_cb), NULL);
    g_signal_connect (stage, "notify::width", G_CALLBACK (size_change), NULL);
    g_signal_connect (stage, "notify::height", G_CALLBACK (size_change),
                      NULL);

    clutter_set_font_flags(CLUTTER_FONT_MIPMAPPING);
    return TRUE;
}

void
set_maintext (const gchar * text, int transition, gboolean wrap)
{
    l_debug("Setting maintext");
    if (g_strcmp0(g_object_get_data(G_OBJECT(maintext), "text"), text) == 0) {
        l_debug("No change to text - returning");
        return;
    }

    // Finish off old animations
    if (CLUTTER_IS_ANIMATION(clutter_actor_get_animation(maintext))) clutter_animation_completed(clutter_actor_get_animation(maintext));
    if (CLUTTER_IS_ANIMATION(clutter_actor_get_animation(maintext_old))) clutter_animation_completed(clutter_actor_get_animation(maintext_old));


    ClutterActor *tmp = maintext_old;
    maintext_old = maintext;
    maintext = tmp;
    g_object_set_data(G_OBJECT(maintext), "text", (gpointer) text);
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
    if (g_strcmp0(g_object_get_data(G_OBJECT(headtext), "text"), text) == 0) {
        return;
    }
    g_object_set_data(G_OBJECT(headtext_old), "text", (gpointer) text);

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
    if (g_strcmp0(g_object_get_data(G_OBJECT(foottext), "text"), text) == 0) {
        return;
    }
    g_object_set_data(G_OBJECT(foottext_old), "text", (gpointer) text);

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

void set_osd (int speed, const gchar * text)
{
    l_debug("Setting OSD at %d speed",speed);

    if (osdtext != NULL) {
        clutter_actor_destroy(osdtext);
        clutter_actor_destroy(osdtext_bg);  
        osdtext = NULL;
        osdtext_bg = NULL;
    }

    osdtext = clutter_group_new();

	if (text == NULL || (g_utf8_strlen(text,10)==0)) {
        return;
    }

    ClutterColor *bgcolour = clutter_color_new (0x00, 0x00, 0x00, 0xA0);
    clutter_color_from_string (bgcolour, maintext_bgcol);
    create_outlined_text(osdtext, text, osdtext_font, maintext_fgcol, maintext_bgcol, FALSE);
    clutter_actor_set_anchor_point_from_gravity (osdtext, 
                                                 CLUTTER_GRAVITY_CENTER);
    osdtext_bg = clutter_rectangle_new_with_color(bgcolour);
    gfloat osd_height = clutter_actor_get_height(osdtext);
    gfloat osd_width = clutter_actor_get_width(osdtext);
    clutter_actor_set_size(osdtext_bg, stage_width, osd_height+5);
    clutter_actor_set_position(osdtext_bg, 0, stage_height - osd_height+5);
    clutter_actor_set_opacity(osdtext_bg, 0x80);
    clutter_container_add (CLUTTER_CONTAINER (stage), osdtext_bg, osdtext, NULL);
    clutter_actor_raise_top(osdtext_bg);
    clutter_actor_raise_top(osdtext);
    gfloat scale = osd_width / stage_width;
    if (scale < 1) scale = 1;
    gfloat duration = scale * speed;

    ClutterPath * osd_path = clutter_path_new();
    clutter_path_add_move_to(osd_path, stage_width + (osd_width/2), stage_height - (osd_height/2) + 3 );
    clutter_path_add_line_to(osd_path, -(osd_width/2), stage_height - (osd_height/2) + 3 );
    ClutterTimeline * osd_timeline = clutter_timeline_new(duration);
    ClutterBehaviour * osd_behaviour = clutter_behaviour_path_new(clutter_alpha_new_full(osd_timeline, CLUTTER_LINEAR), osd_path);
    clutter_behaviour_apply(osd_behaviour, osdtext);
    clutter_timeline_set_loop(osd_timeline, TRUE);
    clutter_timeline_start(osd_timeline);
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

    if (g_ascii_strncasecmp (line[0], "dvd", 3) == 0) {
        line[1] = line[0];
        line[0] = "dvd";
    } else if (line[1] == NULL) {
        line[1] = line[0];
        line[0] = "dir";
    }

    if (g_strcmp0 (line[0], "db") == 0) {
        do_query(mediaDb, "SELECT format, description, data, LENGTH(data) FROM media WHERE id=%s",line[1]);
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
                gchar *dbimage_filename = NULL;

                gint fd = g_file_open_tmp("lyricue-tmp.XXXXXX", &dbimage_filename, NULL);
                if (fd > 0) {
                    if (bg_is_video) g_source_remove(bg_is_video);
                    FILE *file = fdopen(fd,"w");
                    fwrite(row[2], atoi(row[3]), 1, file);
                    fclose(file);
                    close(fd);
                    bg_is_video = 0;
                    background = clutter_texture_new_from_file (dbimage_filename, NULL);
                    unlink(dbimage_filename);
                    g_free(dbimage_filename);
                    clutter_texture_set_keep_aspect_ratio (CLUTTER_TEXTURE
                                                        (background), TRUE);
                    clutter_actor_set_size (background, stage_width, stage_height);
                    clutter_actor_set_anchor_point_from_gravity (background,
                                                                CLUTTER_GRAVITY_CENTER);
                    clutter_actor_set_position (background, stage_width / 2,
                                             stage_height / 2);
                }
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
            if (windowid == 0) {
                clutter_media_set_playing (CLUTTER_MEDIA (background), TRUE);
                g_signal_connect (background, "eos", G_CALLBACK(loop_video), &video_loop);
                bg_is_video = g_timeout_add_seconds(1, (GSourceFunc) update_tracker, NULL);
            } else {
                clutter_media_set_playing (CLUTTER_MEDIA (background), TRUE);
                clutter_media_set_progress(CLUTTER_MEDIA (background), 0.05);
                clutter_media_set_playing (CLUTTER_MEDIA (background), FALSE);
            }
            
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
    } else if (g_strcmp0 (line[0], "dvd") == 0) {
        l_debug("playing DVD Video");
        background = clutter_gst_video_texture_new ();
        clutter_media_set_uri(CLUTTER_MEDIA (background), "dvd://");
        clutter_actor_set_anchor_point_from_gravity (background,
                                                     CLUTTER_GRAVITY_CENTER);
        clutter_actor_set_position (background, stage_width / 2,
                                    stage_height / 2);
        clutter_texture_set_keep_aspect_ratio (CLUTTER_TEXTURE
                                               (background), TRUE);
        clutter_actor_set_size (background, stage_width, stage_height);
        if (windowid == 0) {
            clutter_media_set_playing (CLUTTER_MEDIA (background), TRUE);
            bg_is_video = g_timeout_add_seconds(1, (GSourceFunc) update_tracker, NULL);
            //gboolean ret = gst_element_seek_simple(clutter_gst_video_texture_get_playbin(CLUTTER_GST_VIDEO_TEXTURE(background)), gst_format_get_by_nick("title"), GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT, 1);
        gst_element_seek(clutter_gst_video_texture_get_playbin(CLUTTER_GST_VIDEO_TEXTURE(background)), 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, 10 * GST_SECOND, 0,0);

        } else {
            clutter_media_set_playing (CLUTTER_MEDIA (background), TRUE);
            clutter_media_set_progress(CLUTTER_MEDIA (background), 0.05);
            clutter_media_set_playing (CLUTTER_MEDIA (background), FALSE);
        }

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
                    close_log();
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
    osdtext_font   = (gchar *) g_hash_table_lookup (config, "OSD");
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

    if (effect == DEFAULT) {
        gchar *deftrans = (gchar *) g_hash_table_lookup (config, "DefaultTransition");
        if (deftrans[0] == 'F') {
            effect = FADE;
        } else {
            effect = NOTRANS;
        }
    }

    // Default positioning
    clutter_actor_set_position (new, new_final_x, new_final_y);
    clutter_actor_set_rotation (new, CLUTTER_X_AXIS, 0,0,0,0);
    clutter_actor_set_rotation (new, CLUTTER_Y_AXIS, 0,0,0,0);
    clutter_actor_set_rotation (new, CLUTTER_Z_AXIS, 0,0,0,0);
    clutter_actor_set_opacity  (new, 0xff);

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
            clutter_actor_animate(new, CLUTTER_LINEAR,500,
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
            clutter_actor_animate(old, CLUTTER_LINEAR,500,
                                  "y", old_final_y,
                                  "x", old_final_x,
                                  NULL);
            break;
        case ROTATE:
            if (in_direction & X_AXIS) {
                clutter_actor_set_rotation (new, CLUTTER_X_AXIS,90,0,0,0);
                clutter_actor_animate(new, CLUTTER_LINEAR,500, "rotation-angle-x", 0, NULL);
                clutter_actor_animate(old, CLUTTER_LINEAR,500, "rotation-angle-x", (gfloat)-90 , "signal-swapped-after::completed", clear_group, old, NULL);
            }
            if (in_direction & Y_AXIS) {
                clutter_actor_set_rotation (new, CLUTTER_Y_AXIS,90,0,0,0);
                clutter_actor_animate(new, CLUTTER_LINEAR,500, "rotation-angle-y", 0, NULL);
                clutter_actor_animate(old, CLUTTER_LINEAR,500, "rotation-angle-y", (gfloat)-90 , "signal-swapped-after::completed", clear_group, old, NULL);
            }
            if (in_direction & Z_AXIS) {
                clutter_actor_set_rotation (new, CLUTTER_Z_AXIS,90,0,0,0);
                clutter_actor_animate(new, CLUTTER_LINEAR,500, "rotation-angle-z", 0, NULL);
                clutter_actor_animate(old, CLUTTER_LINEAR,500, "rotation-angle-z", (gfloat)-90 , "signal-swapped-after::completed", clear_group, old, NULL);
            }
        case FADE:
            clutter_actor_set_opacity(new, 0);
            clutter_actor_animate(new, CLUTTER_LINEAR,500,
                          "opacity", 0xff, NULL);
            clutter_actor_animate(old, CLUTTER_LINEAR,500,
                          "opacity", 0,
                          "signal-swapped-after::completed", clear_group,
                          old, NULL);
            break;
        case NOTRANS:
        default:
            clear_group(old);
            break;
    }
}
