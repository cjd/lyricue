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
#include <stdlib.h>
#include <mysql.h>

int db_select ();
int db_deselect ();
MYSQL* db_connect (const char *dbname, const char *dberror);
int db_disconnect (MYSQL *dbconnection);
void load_configuration ();
void save_configuration ();
int do_query(gboolean silent, MYSQL *dbconnection, const gchar* format, ...);
