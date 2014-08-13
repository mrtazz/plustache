#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include <plustache/template.hpp>
#include <plustache/plustache_types.hpp>

// The fixture for testing class Foo.
class ChangeDelimiterTest : public ::testing::Test
{
 protected:
    std::string result_string;
    std::string result_file;
    std::string template_string;
    std::string result_notfound;
    PlustacheTypes::ObjectType ctx;
    std::string file;

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
        Plustache::template_t t;
        result_string = t.render(template_string, ctx);
        Plustache::template_t t2;
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
    std::string expected = "Hi I am Daniel.\n";
           expected += "I like turtles.";
    EXPECT_EQ(expected, result_string);
}

TEST_F(ChangeDelimiterTest, TestChangeDelimiterFromFile)
{
    std::string expected = "Hi I am Daniel.\n";
           expected += "I like turtles.";
    EXPECT_EQ(expected, result_file);
}
