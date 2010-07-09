/**
 * @file template.hpp
 * @brief header file for plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */
#ifndef PLUSTACHE_TEMPLATE_H
#define PLUSTACHE_TEMPLATE_H
#include <iostream>
#include <fstream>
#include <streambuf>
#include <boost/algorithm/string/trim.hpp>
#include <boost/regex.hpp>

#include <plustache_types.hpp>
#include <context.hpp>

using namespace std;
using namespace boost;

class template_t {
public:
    template_t ();
    template_t (string tmpl_path);
    ~template_t ();
    string render(string tmplate, context ctx);
    string render(string tmplate, ObjectType ctx);

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
    string render_sections(string tmplate, context ctx);
    string html_escape(string s);
    string get_partial(string partial);
    void change_delimiter(string opentag, string closetag);
    void compile_data();
    string get_template(string tmpl);
};
#endif
