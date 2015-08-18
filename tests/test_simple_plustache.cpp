#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include <plustache/template.hpp>

// The fixture for testing class Foo.
class SimpleTest : public ::testing::Test
{
 protected:
    std::string result_string;
    std::string result_file;
    std::string template_string;
    std::string result_notfound;
    std::string notfound;
    std::string result_dollars;
    std::string dollars;
    std::string result_parens;
    std::string parens;
    std::map<std::string, std::string> ctx;
    std::string file;

    SimpleTest()
    {
    }

    virtual ~SimpleTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "text {{title}} text";
        notfound = "text {{fitle}} text";
        dollars = "text {{dollars}}";
        parens = "text {{ open_paren }}inside{{ close_paren }}";
        file = "multiple.mustache";

        std::ofstream myfile;
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();

        ctx["title"] = "replaced";
        ctx["dollars"] = "$0";
        ctx["open_paren"] = "(";
        ctx["close_paren"] = ")";

        Plustache::template_t t;
        result_string = t.render(template_string, ctx);
        result_file = t.render(file, ctx);
        result_notfound = t.render(notfound, ctx);
        result_dollars = t.render(dollars, ctx);
        result_parens = t.render(parens, ctx);
    }

    virtual void TearDown()
    {
        remove(file.c_str());
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(SimpleTest, TestSimpleMustacheFromString)
{
    const std::string expected = "text replaced text";
    EXPECT_EQ(expected, result_string);
}

TEST_F(SimpleTest, TestSimpleMustacheFromFile)
{
    const std::string expected = "text replaced text";
    EXPECT_EQ(expected, result_file);
}
TEST_F(SimpleTest, TestSimpleNotFoundMustacheFromString)
{
    const std::string expected = "text  text";
    EXPECT_EQ(expected, result_notfound);
}

TEST_F(SimpleTest, TestDollarSignsInValue)
{
    const std::string expected = "text $0";
    EXPECT_EQ(expected, result_dollars);
}

TEST_F(SimpleTest, TestParensInValue)
{
    const std::string expected = "text (inside)";
    EXPECT_EQ(expected, result_parens);
}
