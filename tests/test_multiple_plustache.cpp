#include "template.hpp"
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class MultipleTest : public ::testing::Test
{
 protected:
    string result;
    string template_string;
    map<string, string> ctx;

    MultipleTest()
    {
    }

    virtual ~MultipleTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "Hi I am {{name}}.\n";
        template_string += "I like {{pet}}.";
        ctx["name"] = "Daniel";
        ctx["pet"] = "turtles";
        template_t t;
        result = t.render(template_string, ctx);
    }

    virtual void TearDown()
    {
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(MultipleTest, TestMultipleMustache)
{
    string expected = "Hi I am Daniel.\n";
          expected += "I like turtles.";
    EXPECT_EQ(expected, result);
}

