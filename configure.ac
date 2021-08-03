#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(typp, v1.3.17, rekhov.ka@gmail.com)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_INIT_AUTOMAKE([subdir-objects])

# Checks for libraries.
PKG_CHECK_MODULES([ncursesw], [ncursesw])
PKG_CHECK_MODULES([form], [form])
PKG_CHECK_MODULES([menu], [menu])
AC_CHECK_LIB([ncurses], [initscr])
AC_CHECK_LIB([m], [round])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile src/Makefile texts/Makefile man/Makefile])
AC_OUTPUT
