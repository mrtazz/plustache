/**
 * @file template.hpp
 * @brief header file for plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 * @version 0.1
 * @date 2010-03-12
 */

#include <iostream>
#include <string>
#include <boost/algorithm/string/trim.hpp>
#include <map>
#include <boost/regex.hpp>

#include <context.hpp>

using namespace std;
using namespace boost;

class template_t {
public:
    template_t ();
    ~template_t ();
    void hello_world();
    string render(string tmplate, context ctx);
    string render(string tmplate, map<string, string> ctx);

private:
    /* opening and closing tags */
    string otag;
    string ctag;
    regex tag;
    regex section;
    string render_tags(string tmplate, context ctx);
    string render_tags(string tmplate, map<string, string> ctx);
    string render_sections(string tmplate, context ctx);
    string render_sections(string tmplate, map<string, string> ctx);
};
