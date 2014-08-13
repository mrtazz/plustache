#include <string>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include <plustache/template.hpp>
#include <plustache/plustache_types.hpp>

// The fixture for testing class Foo.
class NestedSectionsTest : public ::testing::Test
{
 protected:
    std::string result_string;
    std::string result_file;
    std::string template_string;
    PlustacheTypes::ObjectType ctx;
    std::string file;

    NestedSectionsTest()
    {
    }

    virtual ~NestedSectionsTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "Hi I am {{name}}.\n";
        template_string += "{{# showme}}";
        template_string += "I like {{pet}}.\n";
        template_string += "{{# showme2}}";
        template_string += "If you don't see this, something went wrong.";
        template_string += "{{/ showme2}}";
        template_string += "{{/ showme}}";
        file = "sections.mustache";

        std::ofstream myfile;
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();

        ctx["name"] = "Daniel";
        ctx["pet"] = "turtles";
        ctx["showme"] = "true";
        ctx["showme2"] = "true";
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
TEST_F(NestedSectionsTest, TestSectionMustacheFromString)
{
    std::string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.\n";
          expected += "If you don't see this, something went wrong.";
    EXPECT_EQ(expected, result_string);
}

TEST_F(NestedSectionsTest, TestSectionMustacheFromFile)
{
    std::string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.\n";
          expected += "If you don't see this, something went wrong.";
    EXPECT_EQ(expected, result_file);
}
