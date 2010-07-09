/**
 * @file template.hpp
 * @brief header file for plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */
#ifndef PLUSTACHE_CONTEXT_H
#define PLUSTACHE_CONTEXT_H
#include <iostream>
#include "plustache_types.hpp"

using namespace std;


class context {
public:
    context ();
    ~context ();
    int add(string key, string value);
    int add(string key, CollectionType c);
    int add(string key, ObjectType o);
    int add(ObjectType o);
    CollectionType get(string key);

private:
    /* data */
    map<string, CollectionType> ctx;
};
#endif
