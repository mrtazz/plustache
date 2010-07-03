/**
 * @file template.cpp
 * @brief plustache template
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */

#include <template.hpp>

/**
 * @brief constructor taking no arguments
 */
template_t::template_t()
{
    // set template path
    template_path = "";
    template_t::compile_data();
}

/**
 * @brief constructor taking the template path as argument
 *
 * @param tmpl_path path to the template directory
 */
template_t::template_t(string tmpl_path)
{
    template_path = tmpl_path;
}

/**
 * @brief function to compile all the basic data like regex, tags, etc.
 */
void template_t::compile_data()
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

/**
 * @brief destructor nothing to do here
 */
template_t::~template_t()
{

}

/**
 * @brief method to render tags with a given map
 *
 * @param tmplate template string to render
 * @param ctx map of values
 *
 * @return rendered string
 */
string template_t::render_tags(string tmplate, context ctx)
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
                string s = ctx.get(key)[0][key];
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
        // found a partial
        else if (modifier == ">")
        {
            repl.assign(template_t::render(template_t::get_partial(key), ctx));
        }
        // normal tag
        else
        {
            try
            {
                repl.assign(template_t::html_escape(ctx.get(key)[0][key]));
            }
            catch(int i) { repl.assign(""); }
        }

        // replace
        ret += regex_replace(text, tag, repl, match_default | format_all);
        // change delimiter after was removed
        if (modifier == "=")
        {
          // regex for finding delimiters
          regex delim("(.+?) (.+?)=");
          // match object
          match_results<std::string::const_iterator> delim_m;
          // search for the delimiters
          regex_search(matches[2].first, matches[2].second, delim_m, delim,
                       match_default | format_all);
          // set new otag and ctag
          string new_otag = delim_m[1];
          string new_ctag = delim_m[2];
          // change delimiters
          template_t::change_delimiter(new_otag, new_ctag);
        }
        // set start for next tag and rest of string
        rest.assign(matches[0].second, end);
        start = matches[0].second;
    }
    // append and return
    ret += rest;
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
string template_t::render_sections(string tmplate, context ctx)
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
        buckets values;
        values = ctx.get(key);
        if (values.size() == 1)
        {
            // if we don't have a collection, we find the key and an
            // empty map bucket means false
            if (values[0].find(key) != values[0].end())
            {
              show = values[0][key] != "" ? values[0][key] : "false";
            }
            // if we have a collection, we want to show it if there is
            // something to show
            else
            {
              show = values[0].size() > 0 ? "true" : "false";
            }
        }
        else if(values.size() > 1)
        {
            show = "true";
        }
        // inverted section?
        if (modifier == "^" && show == "false") show = "true";
        else if (modifier == "^" && show == "true") show = "false";
        // assign replacement content
        if (show == "true")
        {
            if (regex_search(matches[3].first, matches[3].second,
                             section, match_default | format_all))
            {
                repl.assign(template_t::render_sections(matches[3], ctx));
            }
            else
            {
                for(buckets::iterator it = values.begin();
                    it != values.end(); ++it)
                {
                  context small_ctx;
                  small_ctx = ctx;
                  for(bucket::const_iterator it_map = (*it).begin();
                      it_map != (*it).end(); it_map++)
                  {
                    small_ctx.add(it_map->first, it_map->second);
                  }
                  repl += template_t::render_tags(matches[3], small_ctx);
                }
            }
        }
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
    // get template
    string tmp = get_template(tmplate);

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
string template_t::render(string tmplate, bucket ctx)
{
    // get template
    string tmp = get_template(tmplate);
    context contxt;
    for(bucket::const_iterator it = ctx.begin(); it != ctx.end(); it++)
    {
        contxt.add(it->first, it->second);
    }

    string first = template_t::render_sections(tmp, contxt);
    string second = template_t::render_tags(first, contxt);
    return second;
}

//
// HELPER FUNCTIONS
//


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


/**
 * @brief method to load partial template from file
 *
 * @param s name of the partial to load
 *
 * @return partial template as string
 */
string template_t::get_partial(string partial)
{
    string ret = "";
    string file_with_path = template_path;
    partial += ".mustache";
    file_with_path += partial;
    // file path with template path prefix
    ifstream extended_file(file_with_path.c_str());
    // true if it was a valid file path
    if (extended_file.is_open())
    {
        ret.assign((istreambuf_iterator<char>(extended_file)),
                    istreambuf_iterator<char>());
        extended_file.close();
    }
    else
    {
        // file path without prefix
        ifstream file(partial.c_str());
        if(file.is_open())
        {
          ret.assign((istreambuf_iterator<char>(file)),
                      istreambuf_iterator<char>());
          file.close();
        }
    }
    return ret;
}

/**
 * @brief method to change delimiters
 *
 * @param opentag delimiter for open tag
 * @param closetag delimiter for closed tag
 */
void template_t::change_delimiter(string opentag, string closetag)
{
    otag = opentag;
    ctag = closetag;
    // tag and section regex
    template_t::tag.assign(otag + "(#|=|&|!|>|\\{)?(.+?)(\\})?" + ctag);
    template_t::section.assign(otag + "(\\^|\\#)([^\\}]*)" + ctag +
                               "\\s*(.+?)\\s*" + otag + "/\\2"+ctag);
}

/**
 * @brief function to prepare template for rendering
 *
 * @param tmpl path to template or template directory
 *
 * @return template as string
 */
string template_t::get_template(string tmpl)
{
    // string to hold the template
    string tmp = "";
    ifstream file(tmpl.c_str());
    ifstream file_from_tmpl_dir((template_path + tmpl).c_str());
    // true if it was a valid local file path
    if (file.is_open())
    {
        tmp.assign((istreambuf_iterator<char>(file)),
                    istreambuf_iterator<char>());
        file.close();
    }
    // maybe the template is in the standard directory
    else if (file_from_tmpl_dir.is_open())
    {
        tmp.assign((istreambuf_iterator<char>(file_from_tmpl_dir)),
                    istreambuf_iterator<char>());
        file_from_tmpl_dir.close();

    }
    // tmplate was maybe a complete template and no file path
    else
    {
        tmp = tmpl;
    }

    // cleanup
    if (file.is_open()) file.close();
    if (file_from_tmpl_dir.is_open()) file_from_tmpl_dir.close();

    // return template
    return tmp;
}
