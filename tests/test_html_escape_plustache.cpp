#include "template.hpp"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class HtmlEscapeTest : public ::testing::Test
{
 protected:
    string result_string;
    string result_file;
    string template_string;
    map<string, string> ctx;
    string file;

    HtmlEscapeTest()
    {
    }

    virtual ~HtmlEscapeTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "text {{{title}}} text\n";
        template_string += "text {{& title}} text\n";
        template_string += "text {{ title}} text";
        file = "multiple.mustache";

        std::ofstream myfile;
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();

        ctx["title"] = "<pre>\"\\&</pre>";
        template_t t;
        result_string = t.render(template_string, ctx);
        result_file = t.render(file, ctx);
    }

    virtual void TearDown()
    {
        remove(file.c_str());
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(HtmlEscapeTest, TestHtmlEscapeMustacheFromString)
{
    string expected = "text &lt;pre&gt;&quot;&#92;&amp;&lt;/pre&gt; text\n";
    expected += "text &lt;pre&gt;&quot;&#92;&amp;&lt;/pre&gt; text\n";
    expected += "text <pre>\"\\&</pre> text\n";
    EXPECT_EQ(expected, result_string);
}

TEST_F(HtmlEscapeTest, TestHtmlEscapeMustacheFromFile)
{
    string expected = "text &lt;pre&gt;&quot;&#92;&amp;&lt;/pre&gt; text\n";
    expected += "text &lt;pre&gt;&quot;&#92;&amp;&lt;/pre&gt; text\n";
    expected += "text <pre>\"\\&</pre> text\n";
    EXPECT_EQ(expected, result_file);
}
