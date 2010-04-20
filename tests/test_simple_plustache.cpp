#include "template.hpp"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class SimpleTest : public ::testing::Test
{
 protected:
    string result_string;
    string result_file;
    string template_string;
    map<string, string> ctx;
    string file;

    SimpleTest()
    {
    }

    virtual ~SimpleTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "text {{title}} text";
        file = "multiple.mustache";

        std::ofstream myfile;
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();

        ctx["title"] = "replaced";
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
TEST_F(SimpleTest, TestSimpleMustacheFromString)
{
    const string expected = "text replaced text";
    EXPECT_EQ(expected, result_string);
}

TEST_F(SimpleTest, TestSimpleMustacheFromFile)
{
    const string expected = "text replaced text";
    EXPECT_EQ(expected, result_file);
}
