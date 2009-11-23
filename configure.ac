AC_INIT([lynx], [0.1], [dave@linuxprogrammer.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_LIBTOOL

AC_PROG_INSTALL

AC_LANG_C
AC_PROG_CC

AC_CHECK_HEADERS(stdint.h, , AC_MSG_ERROR[required header file missing])

AC_COPYRIGHT(GNU Library General Public License)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT

