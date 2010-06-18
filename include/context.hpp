/**
 * @file template.hpp
 * @brief header file for plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>

/* defines */
typedef vector<map<string, string>> buckets;
typedef map<string, string> bucket;

using namespace std;

class context {
public:
    context ();
    ~context ();

private:
    /* data */
    map<string, buckets> ctx;
    int add(string key, string value);
    int add(string key, buckets bucks);
};
