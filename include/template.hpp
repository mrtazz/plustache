/**
 * @file template.hpp
 * @brief header file for plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 * @version 0.1
 * @date 2010-03-12
 */

#include <iostream>
#include <string>
#include <map>
#include <boost/regex.hpp>

#include <context.hpp>

using namespace std;

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
    boost::regex tag;
};
