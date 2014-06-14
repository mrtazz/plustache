---
layout: project
title: plustache
---

# plustache - mustache templates for C++
Basic port of [mustache templating](http://mustache.github.com) to C++.

## Motivation
I just wanted to port mustache and build simple templating for C++.
And I am still trying hard to keep it simple.

## Usage

### Simple Usage
Create a template:

{% highlight html %}
<h1>{{ "{{ title " }}}}</h1>
Hi I am {{ "{{ name " }}}}.
I like {{ "{{ thing " }}}}.
{% endhighlight %}

Fill the context:

{% highlight c++ %}
ObjectType ctx;
ctx["title"] = "About";
ctx["name"] = "Daniel";
ctx["thing"] = "turtles";
{% endhighlight %}

Instantiate template class and render the template:

{% highlight c++ %}
template_t t;
string result = t.render(template, ctx);
{% endhighlight %}

Result:

{% highlight html %}
<h1>About</h1>
Hi I am Daniel.
I like turtles.
{% endhighlight %}

### Advanced Usage
Create the template:

{% highlight html %}
<h1>{{ "{{ title " }}}}</h1>
<ul>
  {{# friends}}
    <li> {{ "{{ name " }}}}</li>
    <li> {{ "{{ job " }}}}</li>
    <li> {{ "{{ status " }}}}</li>
  {{/ friends}}
</ul>
{% endhighlight %}

Create the context:

{% highlight c++ %}
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
{% endhighlight %}

Render the template:

{% highlight c++ %}
template_t t;
string result = t.render(template, ctx);
{% endhighlight %}


## Installation
Clone this repository:

{% highlight bash %}
git clone git://github.com/mrtazz/plustache.git
{% endhighlight %}

Run the install tasks:

{% highlight bash %}
autoreconf -i
./configure
make
make install
{% endhighlight %}

Or you can get it via [homebrew](http://github.com/mxcl/homebrew):

{% highlight bash %}
brew install plustache
{% endhighlight %}

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
