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

#include <stdio.h>
#include <sys/time.h>
#include <glib.h>
#include <lyricue_display.h>
#include <utils.h>

extern int server_port;
extern gboolean debugging;
GRegex * re_break = NULL;
GRegex * re_semi = NULL;
GRegex * re_amp = NULL;
FILE * logfile = NULL;

void
l_debug (const gchar * fmt, ...)
{
    va_list argp;
    char timestr[100];
    time_t t;
    if (logfile == NULL) {
        gchar logname[32],ologname[32];
        g_snprintf(logname, 32, "server-%d.log",server_port);
        g_snprintf(ologname, 32, "server-%d.log.old",server_port);
        gchar *logpath = g_build_filename(g_get_user_data_dir(),"lyricue",logname,NULL);
        gchar *ologpath = g_build_filename(g_get_user_data_dir(),"lyricue",ologname,NULL);
        g_rename(logpath,ologpath);
        logfile = g_fopen(logpath, "w");
        if (debugging) {
            g_printf("Logging to %s\n", logpath);
        }
    }

    t = time (NULL);
    if (strftime (timestr, sizeof (timestr), "%H:%M:%S %d/%m", localtime (&t))
        != 0) {
        if (debugging) {
            g_fprintf (stderr, "(%s) ", timestr);
        }
        g_fprintf (logfile, "(%s) ", timestr);
    }

    if (debugging) {
        // stderr
        va_start (argp, fmt);
        g_vfprintf (stderr, fmt, argp);
        g_fprintf (stderr, "\n");
        va_end(argp);
    }

    // logfile
    va_start (argp, fmt);
    g_vfprintf (logfile, fmt, argp);
    g_fprintf (logfile,"\n");
    va_end(argp);

    fflush(logfile);
}

void close_log()
{
    fclose(logfile);
}
gchar * parse_special (const gchar * text)
{
    gchar *tmp = NULL;
    gchar *tmp2 = NULL;
    gchar *tmp3 = NULL;
    if (re_break == NULL) {
        re_break = g_regex_new("#BREAK#", G_REGEX_MULTILINE, 0, NULL);
    }
    if (re_semi == NULL) {
        re_semi = g_regex_new("#SEMI#", G_REGEX_MULTILINE, 0, NULL);
    }
    if (re_amp == NULL) {
        re_amp = g_regex_new("&", G_REGEX_MULTILINE, 0, NULL);
    }
    tmp = g_regex_replace(re_break, text, -1, 0, "\n", 0, NULL);
    tmp2 = g_regex_replace(re_semi, tmp, -1, 0, ":", 0, NULL);
    tmp3 = g_regex_replace(re_amp, tmp2, -1, 0, "&amp;", 0, NULL);
    return tmp3;
}

