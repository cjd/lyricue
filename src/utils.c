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
#include <utils.h>

GRegex * re_break = NULL;
GRegex * re_semi = NULL;

void
l_debug (const gchar * fmt, ...)
{
    va_list argp;
    char timestr[100];
    time_t t;

    t = time (NULL);
    if (strftime (timestr, sizeof (timestr), "%H:%M:%S %d/%m", localtime (&t))
        != 0) {
        printf ("(%s) ", timestr);
    }
    va_start (argp, fmt);
    vprintf (fmt, argp);
    va_end (argp);
    printf ("\n");
}

gchar * parse_special (const gchar * text)
{
    gchar *tmp = NULL;
    gchar *tmp2 = NULL;
    if (re_break == NULL) {
        re_break = g_regex_new("#BREAK#", G_REGEX_MULTILINE, 0, NULL);
    }
    if (re_semi == NULL) {
        re_semi = g_regex_new("#SEMI#", G_REGEX_MULTILINE, 0, NULL);
    }
    tmp = g_regex_replace(re_break, text, -1, 0, "\n", 0, NULL);
    tmp2 = g_regex_replace(re_semi, tmp, -1, 0, ":", 0, NULL);
    return tmp2;
}

