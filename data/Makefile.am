
sql_DATA = \
	Create_lyricDb.sql\
	Create_mediaDb.sql \
	Update_1.2.sql \
	Update_1.9.7.sql \
	Update_1.9.sql \
	Update_2.1.0.sql \
	Update_2.3.2.sql \
	Update_2.4.sql \
	Update_3.5.sql \
	Update_3.6.sql

share_DATA = \
	lyricue.png  \
	Lyricue-first-run-header.svg  \
	Lyricue-first-run-sidebar.png \
	lyricue-icon.png     \
	*.ui

etc_DATA = \
	default.conf \
	access.conf

desktop_DATA = \
    lyricue.desktop \
    lyricue_display.desktop

sharedir = \
	$(pkgdatadir)

sqldir = \
    $(sharedir)/mysql

etcdir = \
    $(sysconfdir)/lyricue

desktopdir = \
    $(datadir)/applications

apportdir = $(datadir)/apport/package-hooks
apport_DATA = source_lyricue.py

crashdbdir = $(sysconfdir)/apport/crashdb.conf.d
crashdb_DATA = lyricue-crashdb.conf


EXTRA_DIST = \
	$(share_DATA) \
	$(sql_DATA) \
	$(etc_DATA) \
	$(apport_DATA) \
	$(crashdb_DATA) \
    $(desktop_DATA)

## File created by the gnome-build tools

