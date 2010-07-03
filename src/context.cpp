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
    ObjectType obj;
    obj[key] = value;
    ctx[key].push_back(obj);
    return 0;
}

/**
 * @brief method to add a collection to a specific key in the context
 *
 * @param key to store the data
 * @param c Collection to add
 *
 * @return 0 on success
 */
int context::add(string key, CollectionType c)
{
    ctx[key] = c;
    return 0;
}

int context::add(ObjectType o)
{
  for(ObjectType::const_iterator it = o.begin();
      it != o.end(); it++)
  {
    (*this).add(it->first, it->second);
  }
  return 0;
}

/**
 * @brief method to get a value from the context
 *
 * This is a generic getter which always returns a collection
 * (vector of maps) for a keyword. If the return value is a collection, the
 * collection is returned. If it is only a single value, a vector
 * with length 1 is returned. If the keyword wasn't found, a vector with
 * length 1 and an empty bucket for the keyword is returned.
 *
 * @param key
 *
 * @return collection for the keyword
 */
CollectionType context::get(string key)
{
    CollectionType ret;
    ret = ctx[key];
    if (ret.size() < 1)
    {
        ObjectType o;
        o[key] = "";
        ret.push_back(o);
    }
    return ret;
}
