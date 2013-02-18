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
extern gint blanked_state;
extern gchar *default_bg;
extern gchar *current_bg;
extern MYSQL *mediaDb;
extern unsigned long windowid;
extern int server_port;
extern MYSQL *lyricDb;
extern int current_item;


const ClutterColor black_colour = { 0x00, 0x00, 0x00, 0xff };

gchar *maintext_fgcol = "white";
gchar *maintext_bgcol = "black";
gchar *headtext_fgcol = "white";
gchar *headtext_bgcol = "black";
gchar *foottext_fgcol = "white";
gchar *foottext_bgcol = "black";
gchar *maintext_fgcol_old = "white";
gchar *maintext_bgcol_old = "black";
gchar *headtext_fgcol_old = "white";
gchar *headtext_bgcol_old = "black";
gchar *foottext_fgcol_old = "white";
gchar *foottext_bgcol_old = "black";

gchar *maintext_font = "";
gchar *headtext_font = "";
gchar *foottext_font = "";
gchar *osdtext_font = "";

GtkWidget *window = NULL;
GtkWidget *clutter_widget = NULL;
ClutterActor *stage = NULL;
ClutterActor *actors = NULL;
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
ClutterShader *shader = NULL;

gfloat stage_width = 0;
gfloat stage_height = 0;
gfloat window_width = 0;
gfloat window_height = 0;
gfloat text_maxwidth = 0;
gfloat text_maxheight = 0;
guint bg_is_video = 0;
guint cursor_timeout = 0;
gboolean video_loop = FALSE;

// Setup shaders
typedef struct
    {
        gchar *name;
        gchar *source;
    } ShaderSource;

static ShaderSource shaders[] = {
    {"box-blur",
     "uniform sampler2D tex;"
     "uniform float x_step, y_step;"
     "vec4 get_rgba_rel(sampler2D tex, float dx, float dy)"
     "{"
     "  return texture2D (tex, gl_TexCoord[0].st "
     "                         + vec2(dx, dy) * 2.0);"
     "}"
     "void main (){"
     "  vec4 color = texture2D (tex, vec2(gl_TexCoord[0]));"
     "  float count = 1.0;"
     "  color += get_rgba_rel (tex, -x_step, -y_step); count++;"
     "  color += get_rgba_rel (tex, -x_step,  0.0);    count++;"
     "  color += get_rgba_rel (tex, -x_step,  y_step); count++;"
     "  color += get_rgba_rel (tex,  0.0,    -y_step); count++;"
     "  color += get_rgba_rel (tex,  0.0,     0.0);    count++;"
     "  color += get_rgba_rel (tex,  0.0,     y_step); count++;"
     "  color += get_rgba_rel (tex,  x_step, -y_step); count++;"
     "  color += get_rgba_rel (tex,  x_step,  0.0);    count++;"
     "  color += get_rgba_rel (tex,  x_step,  y_step); count++;"
     "  color = color / count;"
     "  gl_FragColor = color;"
     "  gl_FragColor = gl_FragColor * gl_Color;" "}"},
    /* Terminating NULL sentinel */
    {NULL, NULL}
};

int
create_main_window (int argc, char *argv[])
{
    int ret = gtk_clutter_init (&argc, &argv);
    clutter_gst_init (&argc, &argv);
    stage_width = atof ((gchar *) g_hash_table_lookup (config, "Width"));
    stage_height = atof ((gchar *) g_hash_table_lookup (config, "Height"));
    if (geometry == NULL) {
        geometry = (gchar *) g_hash_table_lookup (config, "GeometryOverride");
    }
    if (windowid == 0) {
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        clutter_widget = gtk_clutter_embed_new ();
        gtk_container_add (GTK_CONTAINER (window), clutter_widget);
        gtk_widget_show_all (window);
        if (geometry != NULL && (g_utf8_strlen (geometry, 10) > 0)) {
            if (!gtk_window_parse_geometry (GTK_WINDOW (window), geometry)) {
                l_debug ("Failed to parse geometry '%s'", geometry);
            } else {
                l_debug ("Geometry '%s'", geometry);
            }
        }
        if (!windowed)
            gtk_window_fullscreen (GTK_WINDOW (window));
    } else {
        window = gtk_plug_new (windowid);
        clutter_widget = gtk_clutter_embed_new ();
        gtk_container_add (GTK_CONTAINER (window), clutter_widget);
        gtk_widget_show_all (window);
    }

    stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutter_widget));
    actors = clutter_group_new ();
    clutter_container_add (CLUTTER_CONTAINER (stage), actors, NULL);

    clutter_stage_set_color (CLUTTER_STAGE (stage), &black_colour);
    default_bg = (gchar *) g_hash_table_lookup (config, "BGImage");
    change_backdrop (default_bg, TRUE, DEFAULT);
    double window_scale_w =
      (double) clutter_actor_get_width (stage) / (double) stage_width;
    double window_scale_h =
      (double) clutter_actor_get_height (stage) / (double) stage_height;
    clutter_actor_set_scale (actors, window_scale_w, window_scale_h);
    text_maxheight =
      stage_height -
      (atoi ((gchar *) g_hash_table_lookup (config, "OverscanV")) * 2);
    text_maxwidth =
      stage_width -
      (atoi ((gchar *) g_hash_table_lookup (config, "OverscanH")) * 2);
    l_debug ("Creating main window at %dx%d",
             (int) clutter_actor_get_width (stage),
             (int) clutter_actor_get_height (stage));


    maintext = clutter_group_new ();
    maintext_old = clutter_group_new ();
    headtext = clutter_group_new ();
    headtext_old = clutter_group_new ();
    foottext = clutter_group_new ();
    foottext_old = clutter_group_new ();

    clutter_container_add (CLUTTER_CONTAINER (actors), maintext, NULL);
    clutter_container_add (CLUTTER_CONTAINER (actors), headtext, NULL);
    clutter_container_add (CLUTTER_CONTAINER (actors), foottext, NULL);
    clutter_container_add (CLUTTER_CONTAINER (actors), maintext_old, NULL);
    clutter_container_add (CLUTTER_CONTAINER (actors), headtext_old, NULL);
    clutter_container_add (CLUTTER_CONTAINER (actors), foottext_old, NULL);
    clutter_actor_show_all (stage);

    // Setup events
    g_signal_connect (stage, "destroy", G_CALLBACK (exit), NULL);
    g_signal_connect (stage, "event", G_CALLBACK (input_cb), NULL);
    g_signal_connect (stage, "notify::width", G_CALLBACK (size_change), NULL);
    g_signal_connect (stage, "notify::height", G_CALLBACK (size_change),
                      NULL);

    clutter_set_font_flags (CLUTTER_FONT_MIPMAPPING);
    shader = clutter_shader_new ();

    GError *error;

    error = NULL;
    gint shader_no = 0;

    clutter_shader_set_fragment_source (shader, shaders[shader_no].source,
                                        -1);
    clutter_shader_compile (shader, &error);
    if (error) {
        g_print ("unable to load shaders[%d] named '%s': %s\n",
                 shader_no, shaders[shader_no].name, error->message);
        g_error_free (error);

        return EXIT_FAILURE;
    }
    return TRUE;
}

void
set_maintext (const gchar * text, int transition, gboolean wrap)
{
    l_debug ("Setting maintext");
    if (!G_IS_OBJECT (maintext)
        || g_strcmp0 (g_object_get_data (G_OBJECT (maintext), "text"),
                      text) == 0) {
        l_debug ("No change to text - returning");
        return;
    }
    // Finish off old animations
    if (CLUTTER_IS_ANIMATION (clutter_actor_get_animation (maintext)))
        clutter_animation_completed (clutter_actor_get_animation (maintext));
    if (CLUTTER_IS_ANIMATION (clutter_actor_get_animation (maintext_old)))
        clutter_animation_completed (clutter_actor_get_animation
                                     (maintext_old));


    ClutterActor *tmp = maintext_old;
    maintext_old = maintext;
    maintext = tmp;
    g_object_set_data (G_OBJECT (maintext), "text", (gpointer) text);
    clear_group (maintext);
    create_outlined_text (maintext, text, maintext_font, maintext_fgcol,
                          maintext_bgcol, wrap);
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

    do_transition (maintext, maintext_old, transition, final_x, final_y);

    clutter_actor_raise_top (maintext);

}

void
set_headtext (const gchar * text, int transition, gboolean wrap)
{
    if (!G_IS_OBJECT (headtext)
        || g_strcmp0 (g_object_get_data (G_OBJECT (headtext), "text"),
                      text) == 0) {
        return;
    }
    g_object_set_data (G_OBJECT (headtext_old), "text", (gpointer) text);

    ClutterActor *tmp = headtext_old;
    headtext_old = headtext;
    headtext = tmp;
    clear_group (headtext);
    create_outlined_text (headtext, text, headtext_font, headtext_fgcol,
                          headtext_bgcol, wrap);
    clutter_actor_set_anchor_point_from_gravity (headtext,
                                                 CLUTTER_GRAVITY_NORTH);
    clutter_actor_set_position (headtext, stage_width / 2, 0);
    clear_group (headtext_old);
}

void
set_foottext (const gchar * text, int transition, gboolean wrap)
{
    if (!G_IS_OBJECT (foottext)
        || g_strcmp0 (g_object_get_data (G_OBJECT (foottext), "text"),
                      text) == 0) {
        return;
    }
    g_object_set_data (G_OBJECT (foottext_old), "text", (gpointer) text);

    ClutterActor *tmp = foottext_old;
    foottext_old = foottext;
    foottext = tmp;
    clear_group (foottext);
    create_outlined_text (foottext, text, foottext_font, foottext_fgcol,
                          foottext_bgcol, wrap);
    clutter_actor_set_anchor_point_from_gravity (foottext,
                                                 CLUTTER_GRAVITY_SOUTH);
    clutter_actor_set_position (foottext, stage_width / 2, stage_height);
    clear_group (foottext_old);
}

void
set_osd (int speed, const gchar * text)
{
    l_debug ("Setting OSD at %d speed", speed);

    if (osdtext != NULL) {
        clutter_actor_destroy (osdtext);
        clutter_actor_destroy (osdtext_bg);
        osdtext = NULL;
        osdtext_bg = NULL;
    }

    osdtext = clutter_group_new ();

    if (text == NULL || (g_utf8_strlen (text, 10) == 0)) {
        return;
    }

    ClutterColor *bgcolour = clutter_color_new (0x00, 0x00, 0x00, 0xA0);
    clutter_color_from_string (bgcolour, maintext_bgcol);
    create_outlined_text (osdtext, text, osdtext_font, maintext_fgcol,
                          maintext_bgcol, FALSE);
    clutter_actor_set_anchor_point_from_gravity (osdtext,
                                                 CLUTTER_GRAVITY_CENTER);
    osdtext_bg = clutter_rectangle_new_with_color (bgcolour);
    gfloat osd_height = clutter_actor_get_height (osdtext);
    gfloat osd_width = clutter_actor_get_width (osdtext);
    clutter_actor_set_size (osdtext_bg, stage_width, osd_height + 5);
    clutter_actor_set_position (osdtext_bg, 0, stage_height - osd_height + 5);
    clutter_actor_set_opacity (osdtext_bg, 0x80);
    clutter_container_add (CLUTTER_CONTAINER (actors), osdtext_bg, osdtext,
                           NULL);
    clutter_actor_raise_top (osdtext_bg);
    clutter_actor_raise_top (osdtext);
    gfloat scale = osd_width / stage_width;
    if (scale < 1)
        scale = 1;
    gfloat duration = scale * speed;

    ClutterPath *osd_path = clutter_path_new ();
    clutter_path_add_move_to (osd_path, stage_width + (osd_width / 2),
                              stage_height - (osd_height / 2) + 3);
    clutter_path_add_line_to (osd_path, -(osd_width / 2),
                              stage_height - (osd_height / 2) + 3);
    ClutterTimeline *osd_timeline = clutter_timeline_new (duration);
    ClutterBehaviour *osd_behaviour =
      clutter_behaviour_path_new (clutter_alpha_new_full
                                  (osd_timeline, CLUTTER_LINEAR), osd_path);
    clutter_behaviour_apply (osd_behaviour, osdtext);
    clutter_timeline_set_loop (osd_timeline, TRUE);
    clutter_timeline_start (osd_timeline);
}

void
create_outlined_text (ClutterActor * group, const gchar * text,
                      const gchar * font, const gchar * text_colour,
                      const gchar * shadow_colour, gboolean wrap)
{
    ClutterActor *textline[6];
    int i;

    clear_group (group);

    if (text == NULL)
        text = g_strdup ("");

    // Set Colours
    ClutterColor *fgcolour = clutter_color_new (0xFF, 0xFF, 0xFF, 0xFF);
    ClutterColor *bgcolour = clutter_color_new (0x00, 0x00, 0x00, 0xA0);
    clutter_color_from_string (bgcolour, shadow_colour);
    bgcolour->alpha = 0xA0;
    clutter_color_from_string (fgcolour, text_colour);

    // Get justification
    gchar *justify = (gchar *) g_hash_table_lookup (config, "Justification");
    // Get shadow offset
    int shadow_offset =
      atoi ((gchar *) g_hash_table_lookup (config, "ShadowSize"));

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
            clutter_actor_set_position (textline[i], 3 + shadow_offset,
                                        3 + shadow_offset);
        } else {
            clutter_actor_set_position (textline[i], ((i * 2) % 3),
                                        ((i * 2) / 3));
        }
        if (clutter_actor_get_width (textline[i]) > text_maxwidth) {
            clutter_actor_set_width (textline[i], text_maxwidth);
        }
    }
    clutter_actor_raise_top (textline[2]);
    clutter_actor_show_all (group);

//    return group;
}

void
change_backdrop (const gchar * id, gboolean loop, gint transition)
{
    if ((id == NULL) || (strlen (id) == 0)) {
        return;
    }
    l_debug ("change backdrop to %s", id);
    if (g_strcmp0 (id, current_bg) == 0) {
        l_debug ("Backdrop ID same - not changing");
        return;
    }
    //reset_timer(video_timer);
    gchar **line = g_strsplit (id, ";", 2);
    if ((line[1] != NULL) && (strlen (line[1]) == 0)) {
        return;
    }

    g_free (current_bg);
    current_bg = g_strdup (id);
    destroy_actor (background_old);
    background_old = background;
    background = NULL;

    if (g_ascii_strncasecmp (line[0], "dvd", 3) == 0) {
        line[1] = line[0];
        line[0] = "dvd";
    } else if (strlen (line[0]) > 5) {
        line[0] = "dir";
        line[1] = g_strdup (id);
    } else if (line[1] == NULL) {
        line[1] = line[0];
        line[0] = "dir";
    }


    if (g_strcmp0 (line[0], "db") == 0) {
        do_query (mediaDb,
                  "SELECT format, description, data, LENGTH(data) FROM media WHERE id=%s",
                  line[1]);
        MYSQL_ROW row;
        MYSQL_RES *result;
        result = mysql_store_result (mediaDb);
        row = mysql_fetch_row (result);
        if (row != NULL) {
            if (g_strcmp0 (row[0], "bg") == 0) {
                l_debug ("Changing backdrop colour to %s", row[1]);
                if (bg_is_video)
                    g_source_remove (bg_is_video);
                bg_is_video = 0;
                ClutterColor *bgcolour = clutter_color_new (0, 0, 0, 0);
                clutter_color_from_string (bgcolour, row[1]);
                background = clutter_rectangle_new_with_color (bgcolour);
                clutter_actor_set_size (background, stage_width,
                                        stage_height);
                clutter_actor_set_position (background, 0, 0);
                clutter_color_free (bgcolour);
            } else {
                l_debug ("Changing backdrop to dbimage");
                gchar *dbimage_filename = NULL;

                gint fd =
                  g_file_open_tmp ("lyricue-tmp.XXXXXX", &dbimage_filename,
                                   NULL);
                if (fd > 0) {
                    if (bg_is_video)
                        g_source_remove (bg_is_video);
                    FILE *file = fdopen (fd, "w");
                    fwrite (row[2], atoi (row[3]), 1, file);
                    fclose (file);
                    close (fd);
                    bg_is_video = 0;
                    background =
                      clutter_texture_new_from_file (dbimage_filename, NULL);
                    unlink (dbimage_filename);
                    g_free (dbimage_filename);
                    clutter_texture_set_keep_aspect_ratio (CLUTTER_TEXTURE
                                                           (background),
                                                           TRUE);
                    gint w, h;
                    clutter_texture_get_base_size (CLUTTER_TEXTURE
                                                   (background), &w, &h);
                    if (((gfloat) w / (gfloat) h) <
                        (stage_width / stage_height)) {
                        clutter_actor_set_size (background,
                                                (w * (stage_height / h)),
                                                stage_height);
                    } else {
                        clutter_actor_set_size (background, stage_width,
                                                (h * (stage_width / w)));
                    }
                    clutter_actor_set_anchor_point_from_gravity (background,
                                                                 CLUTTER_GRAVITY_CENTER);
                    clutter_actor_set_position (background, stage_width / 2,
                                                stage_height / 2);
                }
            }
        }
    } else if (g_strcmp0 (line[0], "solid") == 0) {
        gchar **col = g_strsplit (line[1], ":", 2);
        l_debug ("Changing backdrop colour to %s", col[0]);
        if (bg_is_video)
            g_source_remove (bg_is_video);
        bg_is_video = 0;
        ClutterColor *bgcolour = clutter_color_new (0, 0, 0, 0);
        clutter_color_from_string (bgcolour, col[0]);
        background = clutter_rectangle_new_with_color (bgcolour);
        clutter_actor_set_size (background, stage_width, stage_height);
        clutter_actor_set_position (background, 0, 0);
        clutter_color_free (bgcolour);
        g_free (col);
    } else if (g_strcmp0 (line[0], "dir") == 0) {
        GFileInfo *info = g_file_query_info (g_file_new_for_path (line[1]),
                                             G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE,
                                             G_FILE_QUERY_INFO_NONE, NULL,
                                             NULL);
        if (!info) {
            l_debug ("Backdrop not loadable:%s", line[1]);
            background = background_old;
            background_old = NULL;
            return;
        }
        if (g_content_type_is_a
            (g_file_info_get_content_type (info), "video/*")
            || g_content_type_is_a (g_file_info_get_content_type (info),
                                    "audio/*")) {
            l_debug ("Backdrop is media");
            background = clutter_gst_video_texture_new ();
            clutter_media_set_filename (CLUTTER_MEDIA (background), line[1]);
            clutter_actor_set_anchor_point_from_gravity (background,
                                                         CLUTTER_GRAVITY_CENTER);
            clutter_actor_set_position (background, stage_width / 2,
                                        stage_height / 2);
            clutter_texture_set_keep_aspect_ratio (CLUTTER_TEXTURE
                                                   (background), TRUE);
            gint w, h;
            clutter_texture_get_base_size (CLUTTER_TEXTURE (background), &w,
                                           &h);
            if (((gfloat) w / (gfloat) h) < (stage_width / stage_height)) {
                clutter_actor_set_size (background, (w * (stage_height / h)),
                                        stage_height);
            } else {
                clutter_actor_set_size (background, stage_width,
                                        (h * (stage_width / w)));
            }
            clutter_media_set_playing (CLUTTER_MEDIA (background), TRUE);
            video_loop = loop;
#if CLUTTER_GST_MAJOR_VERSION == 1
            GstElement *playbin =
              clutter_gst_video_texture_get_pipeline
              (CLUTTER_GST_VIDEO_TEXTURE (background));
#else
            GstElement *playbin =
              clutter_gst_video_texture_get_playbin (CLUTTER_GST_VIDEO_TEXTURE
                                                     (background));
#endif
            if (windowid == 0) {
                g_signal_connect (background, "eos", G_CALLBACK (loop_video),
                                  NULL);
                bg_is_video =
                  g_timeout_add_seconds (1, (GSourceFunc) update_tracker,
                                         NULL);
            } else {
                g_object_set (G_OBJECT (playbin), "flags", 1, NULL);
                bg_is_video =
                  g_timeout_add_seconds (3, (GSourceFunc) stop_media, NULL);
            }
            clutter_media_set_playing (CLUTTER_MEDIA (background), TRUE);

        } else
          if (g_content_type_is_a
              (g_file_info_get_content_type (info), "image/*")) {
            l_debug ("Backdrop is an image");
            if (bg_is_video)
                g_source_remove (bg_is_video);
            bg_is_video = 0;
            background = clutter_texture_new_from_file (line[1], NULL);
            clutter_texture_set_keep_aspect_ratio (CLUTTER_TEXTURE
                                                   (background), TRUE);
            gint w, h;
            clutter_texture_get_base_size (CLUTTER_TEXTURE (background), &w,
                                           &h);
            if (((gfloat) w / (gfloat) h) < (stage_width / stage_height)) {
                clutter_actor_set_size (background, (w * (stage_height / h)),
                                        stage_height);
            } else {
                clutter_actor_set_size (background, stage_width,
                                        (h * (stage_width / w)));
            }
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
        l_debug ("playing DVD Video");
        background = clutter_gst_video_texture_new ();
        clutter_media_set_uri (CLUTTER_MEDIA (background), "dvd://");
        clutter_actor_set_anchor_point_from_gravity (background,
                                                     CLUTTER_GRAVITY_CENTER);
        clutter_actor_set_position (background, stage_width / 2,
                                    stage_height / 2);
        clutter_texture_set_keep_aspect_ratio (CLUTTER_TEXTURE
                                               (background), TRUE);
        gint w, h;
        clutter_texture_get_base_size (CLUTTER_TEXTURE (background), &w, &h);
        if (((gfloat) w / (gfloat) h) < (stage_width / stage_height)) {
            clutter_actor_set_size (background, (w * (stage_height / h)),
                                    stage_height);
        } else {
            clutter_actor_set_size (background, stage_width,
                                    (h * (stage_width / w)));
        }
        clutter_media_set_playing (CLUTTER_MEDIA (background), TRUE);
        video_loop = loop;
#if CLUTTER_GST_MAJOR_VERSION == 1
        GstElement *playbin =
          clutter_gst_video_texture_get_pipeline (CLUTTER_GST_VIDEO_TEXTURE
                                                  (background));
#else
        GstElement *playbin =
          clutter_gst_video_texture_get_playbin (CLUTTER_GST_VIDEO_TEXTURE
                                                 (background));
#endif

        GstElement *resindvd =
          gst_bin_get_by_name (GST_BIN (playbin), "dvdsrc");
        int title = atoi (line[1] + 6);
        gst_element_seek_simple (resindvd, gst_format_get_by_nick ("title"),
                                 GST_SEEK_FLAG_NONE, title);
        l_debug ("Playing DVD title:%d", title);

        if (windowid == 0) {
            bg_is_video =
              g_timeout_add_seconds (1, (GSourceFunc) update_tracker, NULL);
        } else {
            g_object_set (G_OBJECT (playbin), "flags", 1, NULL);
            bg_is_video =
              g_timeout_add_seconds (3, (GSourceFunc) stop_media, NULL);
        }

    } else if (g_strcmp0 (line[0], "uri") == 0) {
        l_debug ("playing direct uri %s", line[1]);
        background = clutter_gst_video_texture_new ();
        clutter_media_set_uri (CLUTTER_MEDIA (background), line[1]);
        clutter_actor_set_anchor_point_from_gravity (background,
                                                     CLUTTER_GRAVITY_CENTER);
        clutter_actor_set_position (background, stage_width / 2,
                                    stage_height / 2);
        clutter_texture_set_keep_aspect_ratio (CLUTTER_TEXTURE
                                               (background), TRUE);
        gint w, h;
        clutter_texture_get_base_size (CLUTTER_TEXTURE (background), &w, &h);
        if (((gfloat) w / (gfloat) h) < (stage_width / stage_height)) {
            clutter_actor_set_size (background, (w * (stage_height / h)),
                                    stage_height);
        } else {
            clutter_actor_set_size (background, stage_width,
                                    (h * (stage_width / w)));
        }
        clutter_media_set_playing (CLUTTER_MEDIA (background), TRUE);
        video_loop = loop;
#if CLUTTER_GST_MAJOR_VERSION == 1
        GstElement *playbin =
          clutter_gst_video_texture_get_pipeline (CLUTTER_GST_VIDEO_TEXTURE
                                                  (background));
#else
        GstElement *playbin =
          clutter_gst_video_texture_get_playbin (CLUTTER_GST_VIDEO_TEXTURE
                                                 (background));
#endif

        if (windowid == 0) {
            bg_is_video =
              g_timeout_add_seconds (1, (GSourceFunc) update_tracker, NULL);
        } else {
            g_object_set (G_OBJECT (playbin), "flags", 1, NULL);
            bg_is_video =
              g_timeout_add_seconds (3, (GSourceFunc) stop_media, NULL);
        }

    }
    if (background) {
        clutter_container_add (CLUTTER_CONTAINER (actors), background, NULL);
        clutter_actor_lower_bottom (background);
    } else {
        background = background_old;
        background_old = NULL;
        clutter_actor_lower_bottom (background);
    }

    maintext_fgcol_old = g_strdup (maintext_fgcol);
    maintext_bgcol_old = g_strdup (maintext_bgcol);
    headtext_fgcol_old = g_strdup (headtext_fgcol);
    headtext_bgcol_old = g_strdup (headtext_bgcol);
    foottext_fgcol_old = g_strdup (foottext_fgcol);
    foottext_bgcol_old = g_strdup (foottext_bgcol);

    // Set text colours
    if ((g_strcmp0
         (maintext_fgcol,
          (gchar *) g_hash_table_lookup (config, "Colour")) != 0)
        ||
        (g_strcmp0
         (maintext_bgcol,
          (gchar *) g_hash_table_lookup (config, "ShadowColour")) != 0)) {
        maintext_fgcol = (gchar *) g_hash_table_lookup (config, "Colour");
        maintext_bgcol =
          (gchar *) g_hash_table_lookup (config, "ShadowColour");
        headtext_fgcol = (gchar *) g_hash_table_lookup (config, "Colour");
        headtext_bgcol =
          (gchar *) g_hash_table_lookup (config, "ShadowColour");
        foottext_fgcol = (gchar *) g_hash_table_lookup (config, "Colour");
        foottext_bgcol =
          (gchar *) g_hash_table_lookup (config, "ShadowColour");
    }
    do_query (mediaDb,
              "SELECT textcolour, shadowcolour FROM media WHERE CONCAT(\"db;\",id)=\"%s\" OR (format=\"file\" AND category=\"%s\")",
              current_bg, line[1]);
    MYSQL_RES *result;
    MYSQL_ROW row;
    result = mysql_store_result (mediaDb);
    row = mysql_fetch_row (result);
    if (row != NULL) {
        if ((g_strcmp0 (maintext_fgcol, row[0]) != 0)
            || (g_strcmp0 (maintext_bgcol, row[1]) != 0)) {
            if (strlen (row[0]) > 0) {
                maintext_fgcol = g_strdup (row[0]);
                headtext_fgcol = g_strdup (row[0]);
                foottext_fgcol = g_strdup (row[0]);
            }
            if (strlen (row[1]) > 0) {
                maintext_bgcol = g_strdup (row[1]);
                headtext_bgcol = g_strdup (row[1]);
                foottext_bgcol = g_strdup (row[1]);
            }
        }
    }

    if (g_strcmp0 (maintext_bgcol, maintext_bgcol_old) != 0) {
        ClutterColor *fgcolour = clutter_color_new (0xFF, 0xFF, 0xFF, 0xFF);
        ClutterColor *bgcolour = clutter_color_new (0x00, 0x00, 0x00, 0xA0);
        clutter_color_from_string (bgcolour, maintext_bgcol);
        bgcolour->alpha = 0xA0;
        clutter_color_from_string (fgcolour, maintext_fgcol);

        int n_kids = clutter_group_get_n_children(CLUTTER_GROUP(maintext));
        int i;
        for (i = 0; i<n_kids; i++) {
            if (i == 2) {
                clutter_text_set_color(CLUTTER_TEXT(clutter_group_get_nth_child(CLUTTER_GROUP(maintext),i)), fgcolour);
            } else {
                clutter_text_set_color(CLUTTER_TEXT(clutter_group_get_nth_child(CLUTTER_GROUP(maintext),i)), bgcolour);
            }
        }
    }
    // Fade out old background
    if (CLUTTER_IS_ACTOR (background_old)) {
        if (transition == 65536) {
            destroy_actor (background_old);
        } else {
            clutter_actor_animate (background_old, CLUTTER_LINEAR, 500,
                                   "opacity", 0,
                                   "signal-swapped-after::completed",
                                   destroy_actor, background_old, NULL);
        }
    }

}

void
fade_backdrop (gint amount)
{
    clutter_actor_set_opacity (background, amount);
    clutter_actor_show (background);
}

void
blur_backdrop (gint amount)
{
    if (amount == 0) {
        clutter_actor_set_shader (background, NULL);
    } else {
        set_shader_num (background, 0);
    }
    clutter_actor_show (background);
}

gboolean
input_cb (ClutterStage * mystage, ClutterEvent * event, gpointer user_data)
{

    gboolean handled = FALSE;
    gchar *ignoremouse;
    switch (event->type) {
        case CLUTTER_BUTTON_RELEASE:
            ignoremouse = (gchar *) g_hash_table_lookup (config, "IgnoreMouse");
            if (ignoremouse != NULL && atoi(ignoremouse) == 1) {
                break;
            }
            switch (clutter_event_get_button (event)) {
                case 1:
                    handle_command (NULL, "display:next_page:");
                    break;
                case 2:
                    handle_command (NULL, "display:prev_song:");
                    break;
                case 3:
                    handle_command (NULL, "display:prev_page:");
                    break;
                default:
                    break;
            }
            break;
        case CLUTTER_KEY_PRESS:
            switch (clutter_event_get_key_symbol (event)) {
                case CLUTTER_Q:
                case CLUTTER_Escape:
                    close_log ();
                    clear_group (stage);
                    clutter_main_quit ();
                    handled = TRUE;
                    break;
                case CLUTTER_Left:
                case CLUTTER_KP_Left:
                case CLUTTER_Page_Up:
                    handle_command (NULL, "display:prev_page:");
                    break;
                case CLUTTER_Right:
                case CLUTTER_KP_Right:
                case CLUTTER_Page_Down:
                    handle_command (NULL, "display:next_page:");
                    break;
                case CLUTTER_Up:
                case CLUTTER_KP_Up:
                    handle_command (NULL, "display:prev_song:");
                    break;
                case CLUTTER_Down:
                case CLUTTER_KP_Down:
                    handle_command (NULL, "display:next_song:");
                    break;
                case CLUTTER_0:
                case CLUTTER_KP_0:
                case CLUTTER_KP_Insert:
                case CLUTTER_c:
                case CLUTTER_x:
                    if (blanked_state == BLANK_NONE) {
                        handle_command (NULL, "blank::");
                    } else {
                        handle_command (NULL, "display:current:");
                    }
                    break;
                case CLUTTER_b:
                    if (blanked_state == BLANK_NONE) {
                        handle_command (NULL, "blank:solid;black:");
                    } else {
                        handle_command (NULL, "display:current:");
                    }
                    break;
                case CLUTTER_p:
                case CLUTTER_space:
                    handle_command (NULL, "media:pause:");
                    break;
                case CLUTTER_1:
                case CLUTTER_KP_1:
                    handle_command (NULL, "display:page:1");
                    break;
                case CLUTTER_2:
                case CLUTTER_KP_2:
                    handle_command (NULL, "display:page:2");
                    break;
                case CLUTTER_3:
                case CLUTTER_KP_3:
                    handle_command (NULL, "display:page:3");
                    break;
                case CLUTTER_4:
                case CLUTTER_KP_4:
                    handle_command (NULL, "display:page:4");
                    break;
                case CLUTTER_5:
                case CLUTTER_KP_5:
                    handle_command (NULL, "display:page:5");
                    break;
                case CLUTTER_6:
                case CLUTTER_KP_6:
                    handle_command (NULL, "display:page:6");
                    break;
                case CLUTTER_7:
                case CLUTTER_KP_7:
                    handle_command (NULL, "display:page:7");
                    break;
                case CLUTTER_8:
                case CLUTTER_KP_8:
                    handle_command (NULL, "display:page:8");
                    break;
                case CLUTTER_9:
                case CLUTTER_KP_9:
                    handle_command (NULL, "display:page:9");
                    break;
                default:
                    l_debug ("Unknown key");
                    break;
            }
            break;
        case CLUTTER_MOTION:
            clutter_stage_show_cursor (CLUTTER_STAGE (stage));
            if (cursor_timeout)
                g_source_remove (cursor_timeout);
            cursor_timeout =
              g_timeout_add_seconds (3, (GSourceFunc) hide_cursor, NULL);
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
        clutter_actor_set_scale (actors, window_scale_w, window_scale_h);
    }
}

void
loop_video (ClutterActor * video)
{
    if (video_loop) {
        clutter_media_set_progress (CLUTTER_MEDIA (video), 0.0);
        clutter_media_set_playing (CLUTTER_MEDIA (video), 1);
    } else {
        if (bg_is_video)
            g_source_remove (bg_is_video);
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
media_skip (gint duration)
{
    if (bg_is_video) {
        l_debug ("Skipping to %d", duration);
#if CLUTTER_GST_MAJOR_VERSION == 1
        gst_element_seek (clutter_gst_video_texture_get_pipeline
                          (CLUTTER_GST_VIDEO_TEXTURE (background)), 1.0,
                          GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
                          GST_SEEK_TYPE_SET, duration * GST_SECOND, 0, 0);
#else
        gst_element_seek (clutter_gst_video_texture_get_playbin
                          (CLUTTER_GST_VIDEO_TEXTURE (background)), 1.0,
                          GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
                          GST_SEEK_TYPE_SET, duration * GST_SECOND, 0, 0);
#endif
    }
}

void
load_font_defaults ()
{
    maintext_font = (gchar *) g_hash_table_lookup (config, "Main");
    headtext_font = (gchar *) g_hash_table_lookup (config, "Header");
    foottext_font = (gchar *) g_hash_table_lookup (config, "Footer");
    osdtext_font = (gchar *) g_hash_table_lookup (config, "OSD");
    maintext_fgcol = (gchar *) g_hash_table_lookup (config, "Colour");
    headtext_fgcol = (gchar *) g_hash_table_lookup (config, "Colour");
    foottext_fgcol = (gchar *) g_hash_table_lookup (config, "Colour");
    maintext_bgcol = (gchar *) g_hash_table_lookup (config, "ShadowColour");
    headtext_bgcol = (gchar *) g_hash_table_lookup (config, "ShadowColour");
    foottext_bgcol = (gchar *) g_hash_table_lookup (config, "ShadowColour");
}

void
clear_group (ClutterActor * actor)
{
    if (actor != NULL) {
        if (CLUTTER_IS_GROUP (actor)) {
            clutter_group_remove_all (CLUTTER_GROUP (actor));
        }
    }
}

void
destroy_actor (ClutterActor * actor)
{
    if (actor != NULL) {
        if (CLUTTER_IS_MEDIA (actor)) {
            clutter_media_set_playing (CLUTTER_MEDIA (actor), FALSE);
        }
        if (CLUTTER_IS_ACTOR (actor)) {
            clutter_actor_destroy (actor);
            actor = NULL;
        }
    }
}

void
do_transition (ClutterActor * new, ClutterActor * old, int transition,
               gfloat final_x, gfloat final_y)
{

    gfloat new_start_x, new_start_y, new_final_x, new_final_y;
    gfloat old_start_x, old_start_y, old_final_x, old_final_y;
    if (CLUTTER_IS_ACTOR (new))
        clutter_actor_get_position (new, &new_start_x, &new_start_y);
    if (CLUTTER_IS_ACTOR (old))
        clutter_actor_get_position (old, &old_start_x, &old_start_y);
    old_final_x = old_start_x;
    old_final_y = old_start_y;
    new_start_x = final_x;
    new_start_y = final_y;
    new_final_x = final_x;
    new_final_y = final_y;
    // Transition
    int out_direction = transition % (2 << NUM_TRANS);
    transition = transition >> NUM_TRANS;
    int in_direction = transition % (2 << NUM_TRANS);
    int effect = transition >> NUM_TRANS;

    if (effect == DEFAULT) {
        gchar *deftrans =
          (gchar *) g_hash_table_lookup (config, "DefaultTransition");
        if (deftrans[0] == 'F') {
            effect = FADE;
        } else {
            effect = NOTRANS;
        }
    } else if (effect == RANDOM) {
        effect = (rand() % (RANDOM-2)) + 2;
        in_direction = rand() % (2 << NUM_TRANS);
        out_direction = rand() % (2 << NUM_TRANS);
    }
    // Default positioning
    clutter_actor_set_position (new, new_final_x, new_final_y);
    clutter_actor_set_rotation (new, CLUTTER_X_AXIS, 0, 0, 0, 0);
    clutter_actor_set_rotation (new, CLUTTER_Y_AXIS, 0, 0, 0, 0);
    clutter_actor_set_rotation (new, CLUTTER_Z_AXIS, 0, 0, 0, 0);
    clutter_actor_set_opacity (new, 0xff);

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
            clutter_actor_animate (new, CLUTTER_LINEAR, 500,
                                   "y", new_final_y, "x", new_final_x, NULL);

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
            clutter_actor_animate (old, CLUTTER_LINEAR, 500,
                                   "y", old_final_y, "x", old_final_x,
                                   "signal-swapped-after::completed",
                                   clear_group, old, NULL);
            break;
        case ROTATE:
            if (in_direction & X_AXIS) {
                clutter_actor_set_rotation (new, CLUTTER_X_AXIS, 90, 0, 0, 0);
                clutter_actor_animate (new, CLUTTER_LINEAR, 500,
                                       "rotation-angle-x", 0, NULL);
                clutter_actor_animate (old, CLUTTER_LINEAR, 500,
                                       "rotation-angle-x", (gfloat) - 90,
                                       "signal-swapped-after::completed",
                                       clear_group, old, NULL);
            }
            if (in_direction & Y_AXIS) {
                clutter_actor_set_rotation (new, CLUTTER_Y_AXIS, 90, 0, 0, 0);
                clutter_actor_animate (new, CLUTTER_LINEAR, 500,
                                       "rotation-angle-y", 0, NULL);
                clutter_actor_animate (old, CLUTTER_LINEAR, 500,
                                       "rotation-angle-y", (gfloat) - 90,
                                       "signal-swapped-after::completed",
                                       clear_group, old, NULL);
            }
            if (in_direction & Z_AXIS) {
                clutter_actor_set_rotation (new, CLUTTER_Z_AXIS, 90, 0, 0, 0);
                clutter_actor_animate (new, CLUTTER_LINEAR, 500,
                                       "rotation-angle-z", 0, NULL);
                clutter_actor_animate (old, CLUTTER_LINEAR, 500,
                                       "rotation-angle-z", (gfloat) - 90,
                                       "signal-swapped-after::completed",
                                       clear_group, old, NULL);
            }
        case FADE:
            clutter_actor_set_opacity (new, 0);
            clutter_actor_animate (new, CLUTTER_LINEAR, 500,
                                   "opacity", 0xff, NULL);
            clutter_actor_animate (old, CLUTTER_LINEAR, 500,
                                   "opacity", 0,
                                   "signal-swapped-after::completed",
                                   clear_group, old, NULL);
            break;
        case NOTRANS:
        default:
            clear_group (old);
            break;
    }
}

static int
next_p2 (gint a)
{
    int rval = 1;

    while (rval < a)
        rval <<= 1;

    return rval;
}

void
set_shader_num (ClutterActor * actor, gint new_no)
{
    int tex_width;
    int tex_height;
    gint shader_no;

    if (new_no >= 0 && shaders[new_no].name) {
        ClutterShader *shader;
        GError *error;
        shader_no = new_no;

        l_debug ("setting shaders[%i] named '%s'\n",
                 shader_no, shaders[shader_no].name);

        shader = clutter_shader_new ();

        error = NULL;
        g_object_set (G_OBJECT (shader),
                      "fragment-source", shaders[shader_no].source, NULL);

        /* try to bind the shader, provoking an error we catch if there is issues
         * with the shader sources we've provided. At a later stage it should be
         * possible to iterate through a set of alternate shader sources (glsl ->
         * asm -> cg?) and the one that succesfully compiles is used.
         */
        clutter_shader_compile (shader, &error);
        if (error) {
            l_debug ("unable to set shaders[%i] named '%s': %s",
                     shader_no, shaders[shader_no].name, error->message);
            g_error_free (error);
            clutter_actor_set_shader (actor, NULL);
        } else {
            clutter_actor_set_shader (actor, NULL);
            clutter_actor_set_shader (actor, shader);

            if (CLUTTER_IS_TEXTURE (actor)) {
                /* XXX - this assumes *a lot* about how things are done
                 * internally on *some* hardware and driver
                 */
                tex_width = clutter_actor_get_width (actor);
                tex_width = next_p2 (tex_width);

                tex_height = clutter_actor_get_height (actor);
                tex_height = next_p2 (tex_height);

                clutter_actor_set_shader_param_float (actor, "x_step",
                                                      1.0f / tex_width);
                clutter_actor_set_shader_param_float (actor, "y_step",
                                                      1.0f / tex_height);
            }
        }
    }
}

gboolean
hide_cursor ()
{
    clutter_stage_hide_cursor (CLUTTER_STAGE (stage));
    return FALSE;
}

gboolean
stop_media ()
{
    l_debug ("Stop media");
    clutter_media_set_playing (CLUTTER_MEDIA (background), FALSE);
    if (bg_is_video)
        g_source_remove (bg_is_video);
    return FALSE;
}

gboolean
take_snapshot (const char *filename)
{
    l_debug ("Saving snapshot to %s", filename);
    guchar *data =
      clutter_stage_read_pixels (CLUTTER_STAGE (stage), 0, 0, -1, -1);
    GdkPixbuf *pixbuf =
      gdk_pixbuf_new_from_data (data, GDK_COLORSPACE_RGB, TRUE, 8,
                                clutter_actor_get_width (stage),
                                clutter_actor_get_height (stage),
                                clutter_actor_get_width (stage) * 4, NULL,
                                NULL);
    gdk_pixbuf_save (pixbuf, filename, "jpeg", NULL, "quality", "90", NULL);
    g_free (data);
    return TRUE;
}

gboolean
take_dbsnapshot (int playorder)
{
    gsize buffer_size;
    gchar *buffer;
    gchar options[10];

    if (playorder > 0) {
        snprintf(options,10,"%d",playorder);
        do_display(options,TRUE);
    } else {
        playorder=current_item;
    }
    l_debug ("Saving snapshot of playlist item %d", playorder);
    guchar *data =
      clutter_stage_read_pixels (CLUTTER_STAGE (stage), 0, 0, -1, -1);
    GdkPixbuf *pixbuf =
      gdk_pixbuf_new_from_data (data, GDK_COLORSPACE_RGB, TRUE, 8,
                                clutter_actor_get_width (stage),
                                clutter_actor_get_height (stage),
                                clutter_actor_get_width (stage) * 4, NULL,
                                NULL);
    float scale = clutter_actor_get_width(stage)/256;
    GdkPixbuf *scaled =
      gdk_pixbuf_scale_simple (pixbuf, 256, clutter_actor_get_height(stage)/scale, GDK_INTERP_BILINEAR);
    gdk_pixbuf_save_to_buffer (scaled,&buffer,&buffer_size, "jpeg", NULL, "quality", "90", NULL);
    char chunk[2*1024*1024]; //2Mb max
    mysql_real_escape_string(lyricDb, chunk, buffer, buffer_size);
    // Custom sql connection so we don't log full image data
    GString *query = g_string_new (NULL);
    l_debug("Writing snapshot to playlist");
    g_string_printf(query, "UPDATE playlist SET snapshot='%s' WHERE playorder=%d",chunk, playorder);
    if (mysql_query (lyricDb, query->str)) {
        l_debug (_("SQL Error %u: %s"), mysql_errno (lyricDb),
          mysql_error (lyricDb));
    }
    g_free (data);
    g_string_free (query, TRUE);

    return TRUE;
}

gboolean
playlist_snapshot(int playlist)
{
    l_debug("Save playlist snapshots %d",NO_EFFECT);
    gchar *cmd = g_strdup_printf ("playlist:%d", playlist);
    do_display (cmd,TRUE);
    change_backdrop (default_bg, TRUE, NO_EFFECT);
    do_display ("display:0",TRUE);
    do_display ("next_page:0",TRUE);
    g_free (cmd);
    int last_item = -1;
    while (last_item < current_item) {
        l_debug ("%d", current_item);
        last_item = current_item;
        do_display ("next_page:0",TRUE);
        take_dbsnapshot (0);
    }
    return TRUE;
}
