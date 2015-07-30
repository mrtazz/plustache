AM_CPPFLAGS = -I$(top_srcdir)/include
pkginclude_HEADERS = include/plustache/template.hpp include/plustache/context.hpp include/plustache/plustache_types.hpp
check_PROGRAMS = test-program
test_program_CPPFLAGS=-Ivendor/gtest-1.6.0/include -I$(top_srcdir)/include
test_program_LDFLAGS=-Lvendor/gtest-1.6.0/lib/.libs -lgtest 

test_program_SOURCES = tests/test_change_delimiter.cpp tests/test_collections_plustache.cpp tests/test_html_escape_plustache.cpp tests/test_inverted_sections.cpp tests/test_multiple_plustache.cpp tests/test_nested_sections_plustache.cpp tests/test_partials_plustache.cpp tests/test_sections_plustache.cpp tests/test_simple_plustache.cpp tests/tests.cpp
test_program_LDADD = .libs/libplustache.a

lib_LTLIBRARIES=libplustache.la
libplustache_la_SOURCES=src/template.cpp src/context.cpp
