#include <template.hpp>
#include <context.hpp>
#include <iostream>

int main(int argc, const char *argv[])
{
    template_t t;
    string str_template;
    str_template = "text {{foo}} text";
    context ctx;
    ctx.add("foo", "bla");
    string s;
    s = t.render(str_template, ctx);
    cout << s << endl;
    return 0;
}
