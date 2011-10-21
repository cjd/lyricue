/***************************************************************************
 *            lyricue_display.h
 *
 *  Tue Jul 20 15:54:37 2010
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <gtk/gtk.h>
#if GTK_MAJOR_VERSION == 3
#include <gtk/gtkx.h>
#endif
#include <clutter/clutter.h>
#include <clutter-gtk/clutter-gtk.h>
#include <clutter-gst/clutter-gst.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>
#include <gio/gio.h>
#include <string.h>
#include "i18n.h"
#include "database.h"
#include "display.h"
#include "bible.h"
#include "utils.h"


gboolean new_connection(GSocketService *service,
                        GSocketConnection *connection,
                        GObject *source_object,
                        gpointer user_data);

gboolean network_read(GIOChannel *source,
                      GIOCondition cond,
                      gpointer data);

void handle_command (GIOChannel *source, const char *command);
void do_media (const char* options);
void do_fade (const char* options);
void do_blur (const char* options);
void do_preview (const char* options);
GString * do_status ();
void do_snapshot();
void do_reconfig();
void do_backdrop(const char* options);
void unblank();
void do_blank(const char* options);
void do_change_to_db(const char* options);
void do_next_point(const char* options);
void do_loopparent(const char* options);
void do_get(const char* options);
void do_display(const char* options);
void do_osd(const char* options);
gboolean update_tracker();
void update_miniview (const char *command);

#define BLANK_NONE 0
#define BLANK_TEXT 1
#define BLANK_BG 2

