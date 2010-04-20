#include "template.hpp"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class SectionsTest : public ::testing::Test
{
 protected:
    string result_string;
    string result_file;
    string template_string;
    map<string, string> ctx;
    string file;

    SectionsTest()
    {
    }

    virtual ~SectionsTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "Hi I am {{name}}.\n";
        template_string += "{{# showme}}";
        template_string += "I like {{pet}}.";
        template_string += "{{/ showme}}";
        template_string += "{{# dontshowme}}";
        template_string += "If you see this, something went wrong.";
        template_string += "{{/ dontshowme}}";
        file = "sections.mustache";

        ofstream myfile;
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();

        ctx["name"] = "Daniel";
        ctx["pet"] = "turtles";
        ctx["showme"] = "true";
        ctx["dontshowme"] = "false";
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
TEST_F(SectionsTest, TestSectionMustacheFromString)
{
    string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.";
    EXPECT_EQ(expected, result_string);
}

TEST_F(SectionsTest, TestSectionMustacheFromFile)
{
    string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.";
    EXPECT_EQ(expected, result_file);
}
