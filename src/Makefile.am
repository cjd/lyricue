## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(LYRICUE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = lyricue \
	lyricue_display

lyricue_display_SOURCES = \
	lyricue_display.c\
	lyricue_display.h \
	database.c \
	database.h \
	display.c \
	display.h \
	utils.c \
	utils.h \
    i18n.h \
	bible.c \
	bible.h

lyricue_display_LDADD = \
	$(LYRICUE_LIBS)

lyricue_SOURCES = \
	main.c

lyricue_LDFLAGS = 

lyricue_LDADD = $(LYRICUE_LIBS)

