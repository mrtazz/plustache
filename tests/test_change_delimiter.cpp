#include "template.hpp"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class ChangeDelimiterTest : public ::testing::Test
{
 protected:
    string result_string;
    string result_file;
    string template_string;
    string result_notfound;
    string notfound;
    map<string, string> ctx;
    string file;

    ChangeDelimiterTest()
    {
    }

    virtual ~ChangeDelimiterTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "Hi I am {{name}}.\n";
        template_string += "{{=<\% \%>=}}\n";
        template_string += "I like <\%pet\%>.\n";

        file = "multiple.mustache";

        std::ofstream myfile;
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();

        ctx["name"] = "Daniel";
        ctx["pet"] = "turtles";
        template_t t;
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
TEST_F(ChangeDelimiterTest, TestChangeDelimiterFromString)
{
    string expected = "Hi I am Daniel.\n";
           expected += "I like turtles.\n";
    EXPECT_EQ(expected, result_string);
}

TEST_F(ChangeDelimiterTest, TestChangeDelimiterFromFile)
{
    string expected = "Hi I am Daniel.\n";
           expected += "I like turtles.\n";
    EXPECT_EQ(expected, result_file);
}
