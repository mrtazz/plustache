#include "template.hpp"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class HtmlEscapeTest : public ::testing::Test
{
 protected:
    string result_escaped_string;
    string result_escaped_file;
    string result_unescaped_string;
    string result_unescaped_file;
    string escaped_string;
    string unescaped_string;
    map<string, string> ctx;
    string escaped_file;
    string unescaped_file;

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

        ctx["title"] = "<pre>\"\\&</pre>";
        ctx["ritle"] = "<pre>\"\\&</pre>";
        template_t t;
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
    string expected = "text &lt;pre&gt;&quot;&#92;&amp;&lt;/pre&gt; text\n";
    expected += "text &lt;pre&gt;&quot;&#92;&amp;&lt;/pre&gt; text";
    EXPECT_EQ(expected, result_escaped_string);
}

TEST_F(HtmlEscapeTest, TestHtmlEscapeMustacheFromFile)
{
    string expected = "text &lt;pre&gt;&quot;&#92;&amp;&lt;/pre&gt; text\n";
    expected += "text &lt;pre&gt;&quot;&#92;&amp;&lt;/pre&gt; text";
    EXPECT_EQ(expected, result_escaped_file);
}

TEST_F(HtmlEscapeTest, TestHtmlUnEscapeMustacheFromString)
{
    string expected = "text <pre>\"\\&</pre> text\n";
    expected += "text <pre>\"\\&</pre> text";
    EXPECT_EQ(expected, result_unescaped_string);
}

TEST_F(HtmlEscapeTest, TestHtmlUnEscapeMustacheFromFile)
{
    string expected = "text <pre>\"\\&</pre> text\n";
    expected += "text <pre>\"\\&</pre> text";
    EXPECT_EQ(expected, result_unescaped_file);
}
