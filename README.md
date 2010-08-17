# plustache - mustache templates for C++
Basic port of [mustache templating](http://mustache.github.com) to C++.

## Motivation
I just wanted to port mustache and build simple templating for C++.
And I am still trying hard to keep it simple.

## Usage

### Simple Usage
Create a template:

    <h1>{{title}}</h1>
    Hi I am {{name}}.
    I like {{thing}}.

Fill the context:

    ObjectType ctx;
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

### Advanced Usage
Create the template:

    <h1> {{title}} </h1>
    <ul>
      {{# friends}}
        <li> {{name}}</li>
        <li> {{job}}</li>
        <li> {{status}}</li>
      {{/ friends}}
    </ul>

Create the context:

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

Render the template:

    template_t t;
    string result = t.render(template, ctx);


## Installation
Clone this repository:

    git clone git://github.com/mrtazz/plustache.git

Run the install task:

    rake install prefix=installfolder

This creates a dynamic library (OSX only at the moment) and
copies the header files and library into $prefix/include and
$prefix/lib respectively.

Or you can get it via [homebrew](http://github.com/mxcl/homebrew):

    brew install plustache

## Supported Functionality (as described in [the man page](http://mustache.github.com/mustache.5.html))
* Variables
* Sections
  * False Values/Empty Lists
  * Non-Empty-Lists
* Inverted Sections
* Comments
* Partials
* Set Delimiter

## TODO
* plustache executable

## Dependencies
* boost for regex and some other things
* google test for unit testing
