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
        template_string += "{{=<\% \%>=}}";
        template_string += "I like <\%pet\%>.";

        file = "multiple.mustache";

        std::ofstream myfile;
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();

        ctx["name"] = "Daniel";
        ctx["pet"] = "turtles";
        template_t t;
        result_string = t.render(template_string, ctx);
        template_t t2;
        result_file = t2.render(file, ctx);
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
           expected += "I like turtles.";
    EXPECT_EQ(expected, result_string);
}

TEST_F(ChangeDelimiterTest, TestChangeDelimiterFromFile)
{
    string expected = "Hi I am Daniel.\n";
           expected += "I like turtles.";
    EXPECT_EQ(expected, result_file);
}
