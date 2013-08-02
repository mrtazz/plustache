#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.52])
AC_INIT([plustache], [0.1.2], [d@unwiredcouch.com])
AM_INIT_AUTOMAKE([0.1.2 foreign subdir-objects])
LT_INIT
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
AC_CHECK_LIB([boost_regex], [main])
AC_CHECK_LIB([gtest], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
