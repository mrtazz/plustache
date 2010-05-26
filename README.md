# plustache - mustache templates for C++
Basic port of [mustache templating](http://mustache.github.com) to C++.

## Motivation
I want to find out if/how it is possible to port mustaches to a more static
language.  Also I found [ctemplate](http://code.google.com/p/google-ctemplate/)
to be rather complicated (I have to admit I never used it, but merely read the
documentation). Therefore I am trying to keep this one as simple as possible.

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

## TODO
* Collections in sections
* Context object instead of map only
* plustache executable

## Dependencies
* boost for regex and some other things
* google test for unit testing
