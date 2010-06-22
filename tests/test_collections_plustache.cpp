#include "template.hpp"
#include "context.hpp"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class CollectionsTest : public ::testing::Test
{
 protected:
    string result_string;
    string result_file;
    string template_string;
    string file;

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
        template_string += "Hi {{name}}!";
        template_string += "{{/ people}}";
        file = "collections.mustache";

        ofstream myfile;
        myfile.open (file.c_str());
        myfile << template_string;
        myfile.close();

        context ctx;
        ctx.add("me", "Daniel");
        buckets b;
        bucket b1;
        b1["name"] = "Tom";
        bucket b2;
        b2["name"] = "Jerry";
        b.push_back(b1);
        b.push_back(b2);
        ctx.add("people", b);

        template_t t;
        result_string = t.render(template_string, ctx);
        result_file = t.render(file, ctx);
    }

    virtual void TearDown()
    {
        remove(file.c_str());
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(CollectionsTest, TestCollectionMustacheFromString)
{
    string expected = "Hi I am Daniel.\n";
          expected += "Hi Tom!\n";
          expected += "Hi Jerry!\n";
    EXPECT_EQ(expected, result_string);
}

TEST_F(CollectionsTest, TestCollectionMustacheFromFile)
{
    string expected = "Hi I am Daniel.\n";
          expected += "Hi Tom!\n";
          expected += "Hi Jerry!\n";
    EXPECT_EQ(expected, result_file);
}
