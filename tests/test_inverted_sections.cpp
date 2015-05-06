#include <string>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include <plustache/template.hpp>
#include <plustache/plustache_types.hpp>

// The fixture for testing class Foo.
class InvertedSectionsTest : public ::testing::Test
{
 protected:
    PlustacheTypes::ObjectType ctx;

    InvertedSectionsTest()
    {
    }

    virtual ~InvertedSectionsTest()
    {
    }

    virtual void SetUp()
    {
        ctx["name"] = "Daniel";
        ctx["pet"] = "turtles";
        ctx["showme"] = "true";
        ctx["stealth"] = "true";
        ctx["inverted"] = "false";
    }

    virtual void TearDown()
    {
    }
};

// Tests that a simple mustache tag is replaced
TEST_F(InvertedSectionsTest, TestInvertedSection)
{
    std::string tmplate=
        "Hi I am {{name}}.\n"
        "{{# showme}}"
        "I like {{pet}}."
        "{{/ showme}}"
        "{{^ inverted}}"
        "Hope you can see me."
        "{{/ inverted}}"
        "{{^ inverted2}}"
        "me too."
        "{{/ inverted2}}"
        "{{^ stealth}}"
        "I'm invisible."
        "{{/ stealth}}";
    std::string expected =
        "Hi I am Daniel.\n"
        "I like turtles."
        "Hope you can see me."
        "me too.";
    
    Plustache::template_t t;
    std::string actual = t.render(tmplate, ctx);
    
    EXPECT_EQ(expected, actual);
}

TEST_F(InvertedSectionsTest, TestInvertedSectionWithNewlines)
{
    std::string tmplate =
R"---tmplate---(
Hi I am {{name}}.
{{# showme}}
I like {{pet}}.
{{/ showme}}
{{^ inverted}}
Hope you can see me.
{{/ inverted}}
{{^ inverted2}}
me too.
{{/ inverted2}}
{{^ stealth}}
I'm invisible.
{{/ stealth}}
)---tmplate---";

    std::string expected =
R"---expected---(
Hi I am Daniel.
I like turtles.
Hope you can see me.
me too.
)---expected---";

    Plustache::template_t t;
    std::string actual = t.render(tmplate, ctx);
    
    EXPECT_EQ(expected, actual);
}
