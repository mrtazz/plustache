#include <string>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include "include/template.hpp"
#include "include/plustache_types.hpp"

// The fixture for testing class Foo.
class PartialsTest : public ::testing::Test
{
 protected:
    std::string result_string;
    std::string result_file;
    std::string template_string;
    std::string partial_string;
    PlustacheTypes::ObjectType ctx;
    std::string file;
    std::string partial_file;

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

        std::ofstream myfile;
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

        Plustache::template_t t;
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
    std::string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.\n";
          expected += "What do I like? Turtles!!";
    EXPECT_EQ(expected, result_string);
}

TEST_F(PartialsTest, TestPartialsMustacheFromFile)
{
    std::string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.\n";
          expected += "What do I like? Turtles!!";
    EXPECT_EQ(expected, result_file);
}
