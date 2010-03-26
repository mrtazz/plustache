/**
 * @file template.cpp
 * @brief plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 * @version 0.1
 * @date 2010-03-12
 */

#include <template.hpp>

void template_t::hello_world()
{
    cout << "Hello World!\n";
}

template_t::template_t()
{

}

template_t::~template_t()
{

}

string template_t::render(string tmplate, context ctx)
{
    string ret = "";
    return ret;
}
