## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(CLUTTER_CFLAGS) \ 
	$(GTK_CFLAGS) $(CLUTTERGTK_CFLAGS) $(CLUTTERGST_CFLAGS) \
    $(GSTREAMER_CFLAGS) $(JSONGLIB_CFLAGS) $(AVAHI_CFLAGS) \
    $(AVAHIGLIB_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -Wno-deprecated-declarations\
	 -g

bin_PROGRAMS = \
	lyricue_display

dist_bin_SCRIPTS = \
	lyricue \
	lyricue_remote

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
	bible.h \
	avahi.c \
	avahi.h

lyricue_display_LDADD = \
	$(CLUTTER_LIBS)  \
	$(GTK_LIBS) \
	$(CLUTTERGTK_LIBS) \
	$(CLUTTERGST_LIBS) \
	$(GSTREAMER_LIBS) \
	$(JSONGLIB_LIBS) \
	$(AVAHIGLIB_LIBS) \
	$(AVAHI_LIBS)

