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

## Usage
Create a template:

    <h1>{{title}}</h1>
    Hi I am {{name}}.
    I like {{thing}}.

Fill the context:

    map<string, string> ctx;
    ctx["title"] = "About";
    ctx["name"] = "Daniel";
    ctx["thing"] = "turtles";

Instantiate template class and render the template:

    template_t t;
    string result = t.render(template, ctx);

Result:

    <h1>About</h1>
    Hi I am Daniel.
    I like turtles.

## TODO:
* Collections in sections
* Partials (if possible)
* Values in an object instead of hash only
* plustache cli command

## Dependencies
* google test for unit testing
* boost for regex and some other things
