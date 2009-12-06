## Proecess this file with automake to produce Makefile.in

TESTS = check_lynx
check_PROGRAMS = check_lynx
check_lynx_SOURCES = check_lynx.c $(top_builddir)/src/lynx.h
check_lynx_CFLAGS = @CHECK_CFLAGS@
check_lynx_LDADD = $(top_builddir)/src/liblynx.la @CHECK_LIBS@
