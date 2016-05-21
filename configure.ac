AC_PREREQ([2.52])
AC_INIT([plustache], [0.3.0], [d@unwiredcouch.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])
LT_INIT
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
AC_CHECK_LIB([boost_regex], [main])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_ARG_ENABLE(coverage,
    AC_HELP_STRING([--enable-coverage],[Enable code coverage]), [CXXFLAGS=" -O0 -g -ftest-coverage -fprofile-arcs"])
AC_OUTPUT
