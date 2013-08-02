#include <string>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include "include/template.hpp"
#include "include/plustache_types.hpp"

// The fixture for testing class Foo.
class HtmlEscapeTest : public ::testing::Test
{
 protected:
    std::string result_escaped_string;
    std::string result_escaped_file;
    std::string result_unescaped_string;
    std::string result_unescaped_file;
    std::string escaped_string;
    std::string unescaped_string;
    PlustacheTypes::ObjectType ctx;
    std::string escaped_file;
    std::string unescaped_file;

    HtmlEscapeTest()
    {
    }

    virtual ~HtmlEscapeTest()
    {
    }

    virtual void SetUp()
    {
        escaped_string = "text {{ title }} text\n";
        escaped_string += "text {{ ritle }} text";
        unescaped_string = "text {{{ title }}} text\n";
        unescaped_string += "text {{& ritle }} text";
        unescaped_file = "unescaped.mustache";
        escaped_file = "escaped.mustache";

        // escaped
        std::ofstream myfile_escaped;
        myfile_escaped.open(escaped_file.c_str());
        myfile_escaped << escaped_string;
        myfile_escaped.close();
        // unescaped
        std::ofstream myfile_unescaped;
        myfile_unescaped.open(unescaped_file.c_str());
        myfile_unescaped << unescaped_string;
        myfile_unescaped.close();

        ctx["title"] = "<pre>\"\\&foo\\</pre>";
        ctx["ritle"] = "<pre>\"\\\\&</pre>";
        Plustache::template_t t;
        result_escaped_string = t.render(escaped_string, ctx);
        result_escaped_file = t.render(escaped_file, ctx);
        result_unescaped_string = t.render(unescaped_string, ctx);
        result_unescaped_file = t.render(unescaped_file, ctx);
    }

    virtual void TearDown()
    {
        remove(escaped_file.c_str());
        remove(unescaped_file.c_str());
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(HtmlEscapeTest, TestHtmlEscapeMustacheFromString)
{
    std::string expected = "text &lt;pre&gt;&quot;&#92;&amp;foo&#92;&lt;\
/pre&gt; text\n";
    expected += "text &lt;pre&gt;&quot;&#92;&#92;&amp;&lt;/pre&gt; text";
    EXPECT_EQ(expected, result_escaped_string);
}

TEST_F(HtmlEscapeTest, TestHtmlEscapeMustacheFromFile)
{
    std::string expected = "text &lt;pre&gt;&quot;&#92;&amp;foo&#92;&lt;\
/pre&gt; text\n";
    expected += "text &lt;pre&gt;&quot;&#92;&#92;&amp;&lt;/pre&gt; text";
    EXPECT_EQ(expected, result_escaped_file);
}

TEST_F(HtmlEscapeTest, TestHtmlUnEscapeMustacheFromString)
{
    std::string expected = "text <pre>\"\\&foo\\</pre> text\n";
    expected += "text <pre>\"\\\\&</pre> text";
    EXPECT_EQ(expected, result_unescaped_string);
}

TEST_F(HtmlEscapeTest, TestHtmlUnEscapeMustacheFromFile)
{
    std::string expected = "text <pre>\"\\&foo\\</pre> text\n";
    expected += "text <pre>\"\\\\&</pre> text";
    EXPECT_EQ(expected, result_unescaped_file);
}
