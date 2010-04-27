/**
 * @file template.cpp
 * @brief plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */

#include <template.hpp>

/**
 * @brief constructor, basically only assign regex
 * and initialize html escape lut
 */
template_t::template_t()
{
    // lookup table for html escape
    escape_lut["&"] = "&amp;";
    escape_lut["<"] = "&lt;";
    escape_lut[">"] = "&gt;";
    escape_lut["\\"] = "&#92;";
    escape_lut["\""] = "&quot;";
    // regex for what to escape in a html string
    escape_chars.assign("(<|>|\"|\\\\|&)");
    otag = "\\{\\{";
    ctag = "\\}\\}";
    // tag and section regex
    tag.assign(otag + "(#|=|&|!|>|\\{)?(.+?)(\\})?" + ctag);
    section.assign(otag + "(\\^|\\#)([^\\}]*)" + ctag + "\\s*(.+?)\\s*"
                   + otag + "/\\2"+ctag);
}

template_t::~template_t()
{

}

/**
 * @brief method to render tags with given context object
 *
 * @param tmplate template string
 * @param ctx context object
 *
 * @return rendered string
 */
string template_t::render_tags(string tmplate, context ctx)
{
    string ret = "";
    return ret;
}

/**
 * @brief method to render tags with a given map
 *
 * @param tmplate template string to render
 * @param ctx map of values
 *
 * @return rendered string
 */
string template_t::render_tags(string tmplate, map<string, string> ctx)
{
    // initialize data
    string ret = "";
    string rest = "";
    string::const_iterator start, end;
    match_results<std::string::const_iterator> matches;
    start = tmplate.begin();
    end = tmplate.end();
    // return whole string when no tags are found
    if (!regex_search(start, end, matches, tag, match_default | format_all))
    {
        ret = tmplate;
    }
    // loop through tags and replace
    while (regex_search(start, end, matches, tag, match_default | format_all))
    {
        string modifier(matches[1].first, matches[1].second);
        string key(matches[2].first, matches[2].second);
        algorithm::trim(key);
        algorithm::trim(modifier);
        string text(start, matches[0].second);
        string repl;
        // don't html escape this
        if (modifier == "&" || modifier == "{")
        {
            try
            {
                // get value
                string s = ctx[key];
                // escape backslash in string
                const string f = "\\";
                size_t found = s.find(f);
                while(found != string::npos)
                {
                    s.replace(found,f.length(),"\\\\");
                    found = s.find(f, found+2);
                }
                repl.assign(s);
            }
            catch(int i) { repl.assign(""); }
        }
        // this is a comment
        else if (modifier == "!")
        {
            repl.assign("");
        }
        // normal tag
        else
        {
            try { repl.assign(template_t::html_escape(ctx[key])); }
            catch(int i) { repl.assign(""); }
        }

        // replace
        ret += regex_replace(text, tag, repl, match_default | format_all);
        rest.assign(matches[0].second, end);
        start = matches[0].second;
    }
    // append and return
    ret += rest;
    return ret;
}

/**
 * @brief method to render sections with a given context object
 *
 * @param tmplate template string to render
 * @param ctx context object
 *
 * @return rendered string
 */
string template_t::render_sections(string tmplate, context ctx)
{
    string ret = "";
    return ret;
}

/**
 * @brief method to render sections with a given map
 *
 * @param tmplate template string to render
 * @param ctx map of values
 *
 * @return rendered string
 */
string template_t::render_sections(string tmplate, map<string, string> ctx)
{
    // initialize data structures
    string ret = "";
    string rest = "";
    string::const_iterator start, end;
    match_results<std::string::const_iterator> matches;
    start = tmplate.begin();
    end = tmplate.end();
    // return the whole template if no sections are found
    if (!regex_search(start, end, matches, section,
                        match_default | format_all))
    {
        ret = tmplate;
    }
    // loop through sections and render
    while (regex_search(start, end, matches, section,
                        match_default | format_all))
    {
        // string assignments
        string text(start, matches[0].second);
        string key(matches[2].first, matches[2].second);
        string modifier(matches[1]);
        // trimming
        algorithm::trim(key);
        algorithm::trim(modifier);
        string repl = "";
        string show = "false";
        show = ctx[key];
        // key miss in map means false
        if (show == "") show = "false";
        // inverted section?
        if (modifier == "^" && show == "false") show = "true";
        else if (modifier == "^" && show == "true") show = "false";
        // assign replacement content
        if (show == "true") repl.assign(matches[3]);
        else repl.assign("");
        ret += regex_replace(text, section, repl, match_default | format_all);
        rest.assign(matches[0].second, end);
        start = matches[0].second;
    }
    // append and return
    ret += rest;
    return ret;
}

/**
 * @brief method for rendering a template
 *
 * @param tmplate template to render as raw string or file path
 * @param ctx context object
 *
 * @return rendered string
 */
string template_t::render(string tmplate, context ctx)
{
    // string to hold the template
    string tmp = "";
    ifstream file(tmplate.c_str());
    // true if it was a valid file path
    if (file.is_open())
    {
        tmp.assign((istreambuf_iterator<char>(file)),
                    istreambuf_iterator<char>());
        file.close();
    }
    // tmplate was maybe a complete template and no file path
    else
    {
        tmp = tmplate;
    }

    string first = template_t::render_sections(tmp, ctx);
    string second = template_t::render_tags(first, ctx);
    return second;
}

/**
 * @brief method for rendering a template
 *
 * @param tmplate template to render as raw string or filepath
 * @param ctx map of values
 *
 * @return rendered string
 */
string template_t::render(string tmplate, map<string, string> ctx)
{
    // string to hold the template
    string tmp = "";
    ifstream file(tmplate.c_str());
    // true if it was a valid file path
    if (file.is_open())
    {
        tmp.assign((istreambuf_iterator<char>(file)),
                    istreambuf_iterator<char>());
        file.close();
    }
    // tmplate was maybe a complete template and no file path
    else
    {
        tmp = tmplate;
    }

    string first = template_t::render_sections(tmp, ctx);
    string second = template_t::render_tags(first, ctx);
    return second;
}

/**
 * @brief method to escape html strings
 *
 * @param s string to escape
 *
 * @return escaped string
 */
string template_t::html_escape(string s)
{
    /** initialize working strings and iterators */
    string ret = "";
    string rest = "";
    string::const_iterator start, end;
    match_results<std::string::const_iterator> matches;
    start = s.begin();
    end = s.end();
    // return original string if nothing is found
    if (!regex_search(start, end, matches, escape_chars,
                        match_default | format_all))
    {
        ret = s;
    }
    // search for html chars
    while (regex_search(start, end, matches, escape_chars,
                        match_default | format_all))
    {
        string key(matches[0].first, matches[0].second);
        string text(start, matches[0].second);
        algorithm::trim(key);
        string repl;
        repl = escape_lut[key];
        ret += regex_replace(text, escape_chars, repl,
                             match_default | format_all);
        rest.assign(matches[0].second, end);
        start = matches[0].second;
    }
    ret += rest;
    return ret;
}

