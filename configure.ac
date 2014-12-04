#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.69)
AC_INIT(prajna, 0.01, fireaxe.hq@outlook.com)
AM_INIT_AUTOMAKE(foreign)

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.
AC_CONFIG_HEADERS([config.h])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([strrchr])

AC_OUTPUT([Makefile paramita/Makefile skandhas/Makefile]) 
