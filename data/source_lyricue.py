# Apport integration for Lyricue
#
# Copyright 2009 Chris Debenham
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3, as published
# by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranties of
# MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
# PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.
"""Stub for Apport"""
# pylint: disable-msg=F0401,C0103
# shut up about apport. We know. We aren't going to backport it for pqm
import apport
from apport.hookutils import attach_file_if_exists, packaging
import os.path
from xdg.BaseDirectory import xdg_data_home

# Paths where things we might want live
lyricue_log_path = os.path.join(xdg_data_home, "lyricue")
# things we may want to collect for the report
lyricue_config = os.path.join(lyricue_log_path, "config2")
lyricue_frontend_log = os.path.join(lyricue_log_path, "frontend.log")
lyricue_frontend_old_log = os.path.join(lyricue_log_path, "frontend.log.old")
lyricue_server_log = os.path.join(lyricue_log_path, "server-2346.log")
lyricue_server_old_log = os.path.join(lyricue_log_path, "server-2346.log.old")
lyricue_preview_log = os.path.join(lyricue_log_path, "server-2347.log")
lyricue_preview_old_log = os.path.join(lyricue_log_path, "server-2347.log.old")


def add_info(report):
    """add report info"""
    attach_file_if_exists(report, lyricue_config,
                                  "LyricueConfig")
    attach_file_if_exists(report, lyricue_frontend_log,
                                  "LyricueFrontendLog")
    attach_file_if_exists(report, lyricue_server_log,
                                  "LyricueServerLog")
    attach_file_if_exists(report, lyricue_preview_log,
                                  "LyricuePreviewLog")
    attach_file_if_exists(report, lyricue_frontend_old_log,
                                  "LyricueFrontendOldLog")
    attach_file_if_exists(report, lyricue_server_old_log,
                                  "LyricueServerOldLog")
    attach_file_if_exists(report, lyricue_preview_old_log,
                                  "LyricuePreviewOldLog")

    if not apport.packaging.is_distro_package(report['Package'].split()[0]):
        report['ThirdParty'] = 'True'
        report['CrashDB'] = 'lyricue'

    packages = ['lyricue',
		'libclutter-1.0-0',
		'libclutter-gst-1.0-0',
		'libclutter-gtk-1.0-0',
		'libclutter-gtk-0.10-0',
		'mysql-server']

    versions = ''
    for package in packages:
        try:
            version = packaging.get_version(package)
        except ValueError:
            version = 'N/A'
        if version is None:
            version = 'N/A'
        versions += '%s %s\n' % (package, version)
    report['LyricuePackages'] = versions
