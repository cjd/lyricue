
sql_DATA = \
	Create_lyricDb.sql\
	Create_mediaDb.sql \
	Update_1.2.sql \
	Update_1.9.7.sql \
	Update_1.9.sql \
	Update_2.1.0.sql \
	Update_2.3.2.sql \
	Update_2.4.sql

share_DATA = \
	DownLeft.svg \
	lyricue.png  \
	UpLeft.svg \
	DownRight.svg  \
	Lyricue-first-run-header.svg  \
	Lyricue-first-run-sidebar.png \
	UpRight.svg \
	Down.svg  \
	Up.svg \
	Left.svg   \
	lyricue-icon.png     \
	Right.svg \
	lyricue.glade

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

