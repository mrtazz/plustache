AM_CPPFLAGS = -I$(top_srcdir)/include
LDFLAGS=-lboost_regex-mt
pkginclude_HEADERS = include/plustache/template.hpp include/plustache/context.hpp include/plustache/plustache_types.hpp
check_PROGRAMS = test-program
test_program_CPPFLAGS=-Ivendor/gtest-1.7.0/include -I$(top_srcdir)/include
test_program_LDFLAGS=-Lvendor/gtest-1.7.0/lib/.libs -lgtest -lboost_regex-mt

test_program_SOURCES = tests/test_change_delimiter.cpp tests/test_collections_plustache.cpp tests/test_html_escape_plustache.cpp tests/test_inverted_sections.cpp tests/test_multiple_plustache.cpp tests/test_nested_sections_plustache.cpp tests/test_partials_plustache.cpp tests/test_sections_plustache.cpp tests/test_simple_plustache.cpp tests/tests.cpp
test_program_LDADD = .libs/libplustache.a

lib_LTLIBRARIES=libplustache.la
libplustache_la_SOURCES=src/template.cpp src/context.cpp


.PHONY: test check clean-coverage-files coverage-html

test: check
	./test-program

clean-local:
	find . -name "*.gcda" -print0 | xargs -0 rm

coverage.info: test
	lcov --compat-libtool --capture --directory src --output-file coverage.info
	lcov --compat-libtool --remove coverage.info "/usr*" -o coverage.info

coverage-html: coverage.info
	genhtml -t "plustache coverage report" --legend --show-details coverage.info --output-directory html
