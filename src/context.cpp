/**
 * @file template.cpp
 * @brief plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */

#include <context.hpp>

context::context()
{

}

context::~context()
{

}

/**
 * @brief method to add a simple key/value to the context
 *
 * @param key
 * @param value
 *
 * @return 0 on success
 */
int context::add(string key, string value)
{

}

/**
 * @brief method to add a bucket to a specific key in the context
 *
 * @param key to store the data
 * @param bucks buckets
 *
 * @return 0 on success
 */
int context::add(string key, buckets bucks)
{

}

/**
 * @brief method to get a value from the context
 *
 * This is a generic getter which always returns buckets
 * (vector of maps) for a keyword. If the return value is a collection, the
 * collection is returned as buckets. If it is only a single value, a vector
 * with length 1 is returned. If the keyword wasn't found, a vector with
 * length 0 is returned.
 *
 * @param key
 *
 * @return buckets for the keyword
 */
buckets context::get(string key)
{

}
