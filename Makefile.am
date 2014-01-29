LDFLAGS=-lboost_regex-mt
include_HEADERS = include/template.hpp include/context.hpp include/plustache_types.hpp
check_PROGRAMS = test-program
test_program_CPPFLAGS=-Ivendor/gtest-1.6.0/include
test_program_LDFLAGS=-Lvendor/gtest-1.6.0/lib/.libs -lgtest -lboost_regex-mt

test_program_SOURCES = tests/test_change_delimiter.cpp tests/test_collections_plustache.cpp tests/test_html_escape_plustache.cpp tests/test_inverted_sections.cpp tests/test_multiple_plustache.cpp tests/test_nested_sections_plustache.cpp tests/test_partials_plustache.cpp tests/test_sections_plustache.cpp tests/test_simple_plustache.cpp tests/tests.cpp
test_program_LDADD = .libs/libplustache.a

lib_LTLIBRARIES=libplustache.la
libplustache_la_SOURCES=src/template.cpp src/context.cpp
