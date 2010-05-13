/**
 * @file template.hpp
 * @brief header file for plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */

#include <iostream>
#include <fstream>
#include <streambuf>
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
    string render(string tmplate, context ctx);
    string render(string tmplate, map<string, string> ctx);

private:
    string template_path;
    /* opening and closing tags */
    string otag;
    string ctag;
    /* regex */
    regex tag;
    regex section;
    regex escape_chars;
    /* lut for HTML escape chars */
    map<string, string> escape_lut;
    /* render and helper methods */
    string render_tags(string tmplate, context ctx);
    string render_tags(string tmplate, map<string, string> ctx);
    string render_sections(string tmplate, context ctx);
    string render_sections(string tmplate, map<string, string> ctx);
    string html_escape(string s);
    string get_partial(string partial);
};
