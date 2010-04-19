# plustache - mustache templates for C++
Basic port of mustache templating
[http://mustache.github.com](http://mustache.github.com) to C++.

## Why HTML templating in C++?
Honestly, I don't know, but I wanted to find out if/how it is
possible to port mustaches to a more static language.
And learn a lot in the progress.

That is also why the supported mustache functionality is still
very basic. More functionality
will be implemented, when I figure out what's the best way to do it.

## TODO:
* HTML escape/unescape
* Collections in sections
* Inverted sections
* Partials (if possible)
* Values in an object instead of hash only
* plustache cli command
* read template from file

## Dependencies
* google test for unit testing
* boost for regex and some other things
