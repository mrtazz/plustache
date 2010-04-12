#include "template.hpp"
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class SimpleTest : public ::testing::Test
{
 protected:
    string result;
    string template_string;
    map<string, string> ctx;

    SimpleTest()
    {
    }

    virtual ~SimpleTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "text {{title}} text";
        ctx["title"] = "replaced";
        template_t t;
        result = t.render(template_string, ctx);
    }

    virtual void TearDown()
    {
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(SimpleTest, TestSimpleMustache)
{
    const string expected = "text replaced text";
    EXPECT_EQ(result, expected);
}

