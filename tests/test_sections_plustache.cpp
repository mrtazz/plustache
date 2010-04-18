#include "template.hpp"
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class SectionsTest : public ::testing::Test
{
 protected:
    string result;
    string template_string;
    map<string, string> ctx;

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
        ctx["name"] = "Daniel";
        ctx["pet"] = "turtles";
        ctx["showme"] = "true";
        ctx["dontshowme"] = "false";
        template_t t;
        result = t.render(template_string, ctx);
    }

    virtual void TearDown()
    {
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(SectionsTest, TestSectionMustache)
{
    string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.";
    EXPECT_EQ(expected, result);
}

