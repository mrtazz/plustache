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

using namespace std;

/** typedefs */
typedef map<string, string> context;

class template_t {
public:
    template_t ();
    ~template_t ();
    void hello_world();
    string render(string tmplate, context ctx);

private:
    /* data */
};
