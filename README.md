# plustache - mustache templates for C++ [![Build Status](https://travis-ci.org/mrtazz/plustache.svg?branch=master)](https://travis-ci.org/mrtazz/plustache)[![Coverage Status](https://coveralls.io/repos/mrtazz/plustache/badge.svg?branch=master&service=github)](https://coveralls.io/github/mrtazz/plustache?branch=master)
Basic port of [mustache templating](http://mustache.github.com) to C++.

## Motivation
I just wanted to port mustache and build simple templating for C++.
And I am still trying hard to keep it simple.

## Usage

### Simple Usage
Create a template:

```html
<h1>{{title}}</h1>
Hi I am {{name}}.
I like {{thing}}.
```

Fill the context:

```C++
#include <string>
#include <plustache/plustache_types.hpp>
#include <plustache/template.hpp>

using std::string;
using PlustacheTypes::ObjectType;
using Plustache::template_t;

ObjectType ctx;
ctx["title"] = "About";
ctx["name"] = "Daniel";
ctx["thing"] = "turtles";
```

Instantiate template class and render the template:

```C++
template_t t;
string template("<h1>{{title}}</h1>\nHi I am {{name}}.\nI like {{thing}}.");

string result = t.render(template, ctx);
```

Result:

```html
<h1>About</h1>
Hi I am Daniel.
I like turtles.
```

### Advanced Usage
Create the template:

```html
<h1> {{title}} </h1>
<ul>
    {{# friends}}
      <li> {{name}}</li>
      <li> {{job}}</li>
      <li> {{status}}</li>
    {{/ friends}}
</ul>
```

Create the context:

```C++
// create types
context ctx;
CollectionType c;
ObjectType jim;
ObjectType john;
ObjectType jack;
// Fill values
ctx.add("title", "My friends");
jim["name"] = "Jim";
jim["job"] = "Wizard";
jim["status"] = "Eating";
john["name"] = "John";
john["job"] = "Rainbow Painter";
john["status"] = "Sleeping";
jack["name"] = "Jack";
jack["job"] = "Unicorn Trainer";
jack["status"] = "Riding";
// enter data
c.push_back(jim);
c.push_back(john);
ctx.add("friends", c);
// also possible
ctx.add("friends", jack);
```

Render the template:

```C++
template_t t;
string result = t.render(template, ctx);
```

## Installation
Clone this repository:

    git clone git://github.com/mrtazz/plustache.git

Run the install tasks:

    autoreconf -i
    ./configure
    make
    make install

Or you can get it via [homebrew](http://github.com/mxcl/homebrew):

    brew install plustache

## Running the unit tests

### Build the google test library:

    cd vendor/gtest-1.6.0
    ./configure
    make

On OS X, you may get an error:

    vendor/gtest-1.6.0/include/gtest/internal/gtest-port.h:499:13: fatal error:
    'tr1/tuple' file not found
    #   include <tr1/tuple>  // NOLINT

If so, re-run configure with the following argument

    ./configure CPPFLAGS=-DGTEST_USE_OWN_TR1_TUPLE=1
    make

### Build the test program

Run this from the top-level plustache source directory:

    make test-program

If you get the tr1/tuple error, do:

    ./configure CPPFLAGS=-DGTEST_USE_OWN_TR1_TUPLE=1
    make test-program

### Run the test program

    ./test-program


## Supported Functionality (as described in [the man page](http://mustache.github.com/mustache.5.html))
* Variables
* Sections
  * False Values/Empty Lists
  * Non-Empty-Lists
* Inverted Sections
* Comments
* Partials
* Set Delimiter
* HTML escape syntax (triple mustaches)

## TODO
* plustache executable

## Dependencies
* boost for regex and some other things
* google test for unit testing (included)
