/**
 * @file template.hpp
 * @brief header file for plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

/* defines */
typedef vector< map<string, string> > buckets;
typedef map<string, string> bucket;

class context {
public:
    context ();
    ~context ();
    int add(string key, string value);
    int add(string key, buckets bucks);

private:
    /* data */
    map<string, buckets> ctx;
};
