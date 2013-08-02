#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include "include/template.hpp"

// The fixture for testing class Foo.
class SimpleTest : public ::testing::Test
{
 protected:
    std::string result_string;
    std::string result_file;
    std::string template_string;
    std::string result_notfound;
    std::string notfound;
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
        file = "multiple.mustache";

        std::ofstream myfile;
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();

        ctx["title"] = "replaced";
        Plustache::template_t t;
        result_string = t.render(template_string, ctx);
        result_file = t.render(file, ctx);
        result_notfound = t.render(notfound, ctx);
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
