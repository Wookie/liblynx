AC_PREREQ([2.59])
AC_INIT([lynx], [0.1], [dave@linuxprogrammer.org])

AC_CONFIG_SRCDIR([src/lynx.c])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([-Wall -Werror foreign 1.9.6])

AC_LANG_C
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL

AM_PATH_CHECK()

AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h stdint.h stdbool.h])

AC_FUNC_MALLOC

AC_COPYRIGHT(GNU Library General Public License)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
    tests/Makefile
])

AC_OUTPUT

