#include <string>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include <plustache/template.hpp>
#include <plustache/context.hpp>
#include <plustache/plustache_types.hpp>

// The fixture for testing class Foo.
class CollectionsTest : public ::testing::Test
{
 protected:
    std::string result_single;
    std::string result_multiple;
    std::string result_multiple_fields;
    std::string template_string;
    std::string template_single_string;

    CollectionsTest()
    {
    }

    virtual ~CollectionsTest()
    {
    }

    virtual void SetUp()
    {
        template_string = "Hi I am {{me}}.\n";
        template_string += "{{# people}}";
        template_string += "Hi {{me}}, I am {{name}}, I do {{work}}.";
        template_string += "{{/ people}}";
        template_single_string = "Hi I am {{me}}.\n";
        template_single_string += "{{# people}}";
        template_single_string += "Hi {{name}}!";
        template_single_string += "{{/ people}}";

        // single entry
        PlustacheTypes::ObjectType tom;
        PlustacheTypes::ObjectType jerry;
        tom["name"] = "Tom";
        Plustache::Context ctx_single;
        ctx_single.add("me", "Daniel");
        ctx_single.add("people",tom);

        // multiple entries
        jerry["name"] = "Jerry";
        PlustacheTypes::CollectionType b_multiple;
        b_multiple.push_back(tom);
        b_multiple.push_back(jerry);
        Plustache::Context ctx_multiple;
        ctx_multiple.add("me", "Daniel");
        ctx_multiple.add("people", b_multiple);

        // multiple fields
        tom["work"] = "Accounting";
        jerry["work"] = "Magic";
        PlustacheTypes::CollectionType b_multiple_fields;
        b_multiple_fields.push_back(tom);
        Plustache::Context ctx;
        ctx.add("me", "Daniel");
        ctx.add("people", b_multiple_fields);
        ctx.add("people", jerry);



        Plustache::template_t t;
        result_single = t.render(template_single_string, ctx_single);
        result_multiple = t.render(template_single_string, ctx_multiple);
        result_multiple_fields = t.render(template_string, ctx);
    }

    virtual void TearDown()
    {
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(CollectionsTest, TestCollectionsSingle)
{
    std::string expected = "Hi I am Daniel.\n";
          expected += "Hi Tom!";
    EXPECT_EQ(expected, result_single);
}

TEST_F(CollectionsTest, TestCollectionsMultiple)
{
    std::string expected = "Hi I am Daniel.\n";
          expected += "Hi Tom!";
          expected += "Hi Jerry!";
    EXPECT_EQ(expected, result_multiple);
}

TEST_F(CollectionsTest, TestCollectionMultipleWithMultipleFields)
{
    std::string expected = "Hi I am Daniel.\n";
        expected += "Hi Daniel, I am Tom, I do Accounting.";
        expected += "Hi Daniel, I am Jerry, I do Magic.";
    EXPECT_EQ(expected, result_multiple_fields);
}
TEST_F(CollectionsTest, TestCollectionMultiLine)
{
    Plustache::Context ctx;
    ctx.add("me", "Daniel");
    
    PlustacheTypes::ObjectType tom;
    tom["name"] = "Tom";
    tom["work"] = "Accounting";
    ctx.add("people", tom);
    
    PlustacheTypes::ObjectType jerry;
    jerry["name"] = "Jerry";
    jerry["work"] = "Magic";
    ctx.add("people", jerry);

    std::string tmplate =
R"---tmplate---(
Hi! I am {{me}}.
{{#people}}
Hello, {{me}}; I am {{name}}, and I do {{work}}.
{{/people}}

*crickets*
)---tmplate---";

    std::string expected =
R"---expected---(
Hi! I am Daniel.
Hello, Daniel; I am Tom, and I do Accounting.
Hello, Daniel; I am Jerry, and I do Magic.

*crickets*
)---expected---";

    Plustache::template_t t;
    std::string actual = t.render(tmplate, ctx);
    
    EXPECT_EQ(expected, actual);
}

TEST_F(CollectionsTest, TestCollectionMultiLineConditionals)
{
    Plustache::Context ctx;
    ctx.add("me", "Daniel");
    
    PlustacheTypes::ObjectType tom;
    tom["name"] = "Tom";
    tom["work"] = "Accounting";
    tom["surprise"] = "false";
    ctx.add("people", tom);
    
    PlustacheTypes::ObjectType jerry;
    jerry["name"] = "Jerry";
    jerry["work"] = "Magic";
    jerry["surprise"] = "true";
    ctx.add("people", jerry);

    std::string tmplate =
R"---tmplate---(
Hi! I am {{me}}.
{{#people}}
Hello, {{me}}; I am {{name}}, and I do {{work}}.
{{#surprise}}
*{{name}} disappears in a flash of light and smoke*
{{/surprise}}
{{/people}}

*crickets*
)---tmplate---";

    std::string expected =
R"---expected---(
Hi! I am Daniel.
Hello, Daniel; I am Tom, and I do Accounting.
Hello, Daniel; I am Jerry, and I do Magic.
*Jerry disappears in a flash of light and smoke*

*crickets*
)---expected---";

    Plustache::template_t t;
    std::string actual = t.render(tmplate, ctx);
    
    EXPECT_EQ(expected, actual);
}
