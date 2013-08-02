#include <string>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include "include/template.hpp"
#include "include/plustache_types.hpp"

// The fixture for testing class Foo.
class InvertedSectionsTest : public ::testing::Test
{
 protected:
    std::string result_string;
    std::string result_file;
    std::string template_string;
    PlustacheTypes::ObjectType ctx;
    std::string file;

    InvertedSectionsTest()
    {
    }

    virtual ~InvertedSectionsTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "Hi I am {{name}}.\n";
        template_string += "{{# showme}}";
        template_string += "I like {{pet}}.";
        template_string += "{{/ showme}}";
        template_string += "{{^ inverted}}";
        template_string += "Hope you can see me.";
        template_string += "{{/ inverted}}";
        template_string += "{{^ inverted2}}";
        template_string += "me too.";
        template_string += "{{/ inverted2}}";
        template_string += "{{^ stealth}}";
        template_string += "I'm invisible.";
        template_string += "{{/ stealth}}";
        file = "sections.mustache";

        std::ofstream myfile;
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();

        ctx["name"] = "Daniel";
        ctx["pet"] = "turtles";
        ctx["showme"] = "true";
        ctx["stealth"] = "true";
        ctx["inverted"] = "false";
        Plustache::template_t t;
        result_string = t.render(template_string, ctx);
        result_file = t.render(file, ctx);
    }

    virtual void TearDown()
    {
        remove(file.c_str());
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(InvertedSectionsTest, TestInvertedSectionMustacheFromString)
{
    std::string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.";
          expected += "Hope you can see me.";
          expected += "me too.";
    EXPECT_EQ(expected, result_string);
}

TEST_F(InvertedSectionsTest, TestInvertedSectionMustacheFromFile)
{
    std::string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.";
          expected += "Hope you can see me.";
          expected += "me too.";
    EXPECT_EQ(expected, result_file);
}
