# Changelog

## v0.4.0 (??/??/2016)
- Add MSVC build. (Joshua Napoli)
- fix bug with special characters in replacement text (John Chesley)
- add automated package builds via travis ci (Daniel Schauenberg)
- add coveralls support to travis build and switch to container infra (Daniel Schauenberg)
- add build setup for coverage reporting (Daniel Schauenberg)
- upgrade gtest to 1.7 and add lcov util (Daniel Schauenberg)
- Update README.md with GitHub aware Syntax coloring (Grant McGovern)
- Accept const string ref in template constructor (Maarten de Vries)
- Move header files to their own directory (Lorin Hochstein)

## v0.3.0 (01/29/2014)
* mention support of HTML escaping in README
* no more rakefile
* switch to autotools, vendorized gtest and fix tests
* Fixed constructor with path argument.
* Namespaced
* Fix throw/crash when using the tmpl\_path ctor
* add travis-ci config
* make rake test:coverage play nice with jenkins
* update rakefile
* generate unit test xml output
* add rake target for coverage report
* add gcovr utility
* add xml output of cppcheck

## v0.2.1 (07/29/2011)
* major style improvements for all files
* update Rakefile to new include style
* update tests to new include style
* update README with brew install

## v0.2.0 (08/16/2010)
* static library via rake
* dynamic library via rake
* install task

## v0.1.0 (07/03/2010)
* collections via vectors
* context object

## v0.0.1 (06/20/2010)
* basic mustache templates working
* no sections
