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
    otag = "\\{\\{";
    ctag = "\\}\\}";
    tag.assign(otag + "(#|=|&|!|>|\\{)?(.+?)\\1?" + ctag);
    section.assign(otag + "\\#([^\\}]*)" + ctag + "\\s*(.+?)\\s*"
                   + otag + "/\\1"+ctag);
}

template_t::~template_t()
{

}

string template_t::render_tags(string tmplate, context ctx)
{
    string ret = "";
    return ret;
}

string template_t::render_tags(string tmplate, map<string, string> ctx)
{
    string ret = "";
    string rest = "";
    string::const_iterator start, end;
    match_results<std::string::const_iterator> matches;
    start = tmplate.begin();
    end = tmplate.end();
    if (!regex_search(start, end, matches, tag, match_default | format_all))
    {
        ret = tmplate;
    }
    while (regex_search(start, end, matches, tag, match_default | format_all))
    {
        string key(matches[2].first, matches[2].second);
        string text(start, matches[0].second);
        string repl;
        try { repl.assign(ctx[key]); }
        catch(int i) { repl.assign(""); }
        if (matches[1] == "!") repl.assign("");
        ret += regex_replace(text, tag, repl, match_default | format_all);
        rest.assign(matches[0].second, end);
        start = matches[0].second;
    }
    ret += rest;
    return ret;
}

string template_t::render_sections(string tmplate, context ctx)
{
    string ret = "";
    return ret;
}

string template_t::render_sections(string tmplate, map<string, string> ctx)
{
    string ret = "";
    string rest = "";
    string::const_iterator start, end;
    match_results<std::string::const_iterator> matches;
    start = tmplate.begin();
    end = tmplate.end();
    if (!regex_search(start, end, matches, section,
                        match_default | format_all))
    {
        ret = tmplate;
    }
    while (regex_search(start, end, matches, section,
                        match_default | format_all))
    {
        string text(start, matches[0].second);
        string key(matches[1].first, matches[1].second);
        algorithm::trim(key);
        string repl = "";
        string show = "false";
        try { show = ctx[key]; }
        catch(int i) { repl.assign(""); }
        if (show == "true") repl.assign(matches[2]);
        ret += regex_replace(text, section, repl, match_default | format_all);
        rest.assign(matches[0].second, end);
        start = matches[0].second;
    }
    ret += rest;
    return ret;
}

string template_t::render(string tmplate, context ctx)
{
    string first = template_t::render_sections(tmplate, ctx);
    string second = template_t::render_tags(first, ctx);
    return second;
}

string template_t::render(string tmplate, map<string, string> ctx)
{
    string first = template_t::render_sections(tmplate, ctx);
    string second = template_t::render_tags(first, ctx);
    return second;
}


