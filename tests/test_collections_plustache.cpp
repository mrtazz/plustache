#include "template.hpp"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class CollectionsTest : public ::testing::Test
{
 protected:
    string result_single;
    string result_multiple;
    string result_multiple_fields;
    string template_string;
    string template_single_string;

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
        bucket tom;
        bucket jerry;
        tom["name"] = "Tom";
        buckets b_single;
        b_single.push_back(tom);
        context ctx_single;
        ctx_single.add("me", "Daniel");
        ctx_single.add("people",b_single);

        // multiple entries
        jerry["name"] = "Jerry";
        buckets b_multiple;
        b_multiple.push_back(tom);
        b_multiple.push_back(jerry);
        context ctx_multiple;
        ctx_multiple.add("me", "Daniel");
        ctx_multiple.add("people", b_multiple);

        // multiple fields
        tom["work"] = "Accounting";
        jerry["work"] = "Magic";
        buckets b_multiple_fields;
        b_multiple_fields.push_back(tom);
        b_multiple_fields.push_back(jerry);
        context ctx;
        ctx.add("me", "Daniel");
        ctx.add("people", b_multiple_fields);



        template_t t;
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
    string expected = "Hi I am Daniel.\n";
          expected += "Hi Tom!";
    EXPECT_EQ(expected, result_single);
}

TEST_F(CollectionsTest, TestCollectionsMultiple)
{
    string expected = "Hi I am Daniel.\n";
          expected += "Hi Tom!";
          expected += "Hi Jerry!";
    EXPECT_EQ(expected, result_multiple);
}

TEST_F(CollectionsTest, TestCollectionMultipleWithMultipleFields)
{
    string expected = "Hi I am Daniel.\n";
        expected += "Hi Daniel, I am Tom, I do Accounting.";
        expected += "Hi Daniel, I am Jerry, I do Magic.";
    EXPECT_EQ(expected, result_multiple_fields);
}
