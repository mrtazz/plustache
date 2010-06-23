/**
 * @file template.hpp
 * @brief header file for plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */

#include <iostream>
#include "plustache_types.hpp"

using namespace std;


class context {
public:
    context ();
    ~context ();
    int add(string key, string value);
    int add(string key, buckets bucks);
    buckets get(string key);

private:
    /* data */
    map<string, buckets> ctx;
};
