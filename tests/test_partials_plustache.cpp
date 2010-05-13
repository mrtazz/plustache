#include "template.hpp"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class PartialsTest : public ::testing::Test
{
 protected:
    string result_string;
    string result_file;
    string template_string;
    string partial_string;
    map<string, string> ctx;
    string file;
    string partial_file;

    PartialsTest()
    {
    }

    virtual ~PartialsTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "Hi I am {{name}}.\n";
        template_string += "{{> next_more}}\n";
        template_string += "What do I like? {{lpet}}!!";

        partial_string = "I like {{pet}}.";

        file = "sections.mustache";
        partial_file = "next_more.mustache";

        ofstream myfile;
        // write template to file
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();
        // write partial to file
        myfile.open (partial_file.c_str());
        myfile << partial_string;
        myfile.close();

        ctx["name"] = "Daniel";
        ctx["pet"] = "turtles";
        ctx["lpet"] = "Turtles";

        template_t t;
        result_string = t.render(template_string, ctx);
        result_file = t.render(file, ctx);
    }

    virtual void TearDown()
    {
        remove(file.c_str());
        remove(partial_file.c_str());
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(PartialsTest, TestPartialsFromString)
{
    string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.\n";
          expected += "What do I like? Turtles!!";
    EXPECT_EQ(expected, result_string);
}

TEST_F(PartialsTest, TestPartialsMustacheFromFile)
{
    string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.\n";
          expected += "What do I like? Turtles!!";
    EXPECT_EQ(expected, result_file);
}
