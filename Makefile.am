## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po data 

lyricuedocdir = $(docdir)

lyricuedoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS \
	Development.txt \
    song_template.txt \
	sample_song.xml


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(lyricuedoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache
