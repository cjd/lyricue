AC_INIT(lyricue, 4.0.9, http://www.lyricue.org)
AC_CONFIG_AUX_DIR([build-aux])

LIBS=`mysql_config --libs`
AC_SUBST(LIBS)

CFLAGS=`mysql_config --cflags`
AC_SUBST(CFLAGS)

m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
GETTEXT_PACKAGE=lyricue
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])

AM_PROG_LIBTOOL

YELP_HELP_INIT

PKG_CHECK_MODULES(CLUTTER, clutter-1.0)
PKG_CHECK_MODULES(CLUTTERGTK, clutter-gtk-1.0)
PKG_CHECK_MODULES(CLUTTERGST, clutter-gst-3.0,,[PKG_CHECK_MODULES(CLUTTERGST, clutter-gst-2.0,, [PKG_CHECK_MODULES(CLUTTERGST, clutter-gst-1.0)])])
PKG_CHECK_MODULES(GSTREAMER, gstreamer-1.0,, [PKG_CHECK_MODULES(CLUTTERGST, gstreamer-0.10)])
PKG_CHECK_MODULES(JSONGLIB, json-glib-1.0)
PKG_CHECK_MODULES(AVAHI, avahi-client)
PKG_CHECK_MODULES(AVAHIGLIB, avahi-glib)
AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
data/Makefile
help/Makefile
])
