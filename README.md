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

Run the install tasks:

    autoreconf -i
    ./configure
    make
    make install

Or you can get it via [homebrew](http://github.com/mxcl/homebrew):

    brew install plustache


### Building with Microsoft Visual Studio
The supplied MSBuild files will look for an installation of boost in the parent
directory of this repo. The boost regex library must be built. For example:

```
cd boost_1_55_0
bootstrap
b2 -j8 toolset=msvc-12.0 address-model=64 --with-regex --prefix=../boost install
```

The boost directories and other build parameters can be
configured by creating a
[Directories.targets](msvc/Directories.targets.example) file.

The gtest project files are generated by cmake. Use a command like this to
recreate the gtest project files:

```
cd msvc/x64/msvc120/gtest
cmake -G "Visual Studio 12 Win64" ../../../../vendor/gtest-1.6.0 -Dgtest_force_shared_crt=ON
```

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
* google test for unit testing
