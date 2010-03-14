#include "template.h"
#include <gtest/gtest.h>

namespace {

// The fixture for testing class Foo.
class SimpleTest : public ::testing::Test {
 protected:
    string result;

    SimpleTest() {
    }

    virtual ~SimpleTest() {
    }

    virtual void SetUp() {
        template_t t;
        result = t.render(template_string,context);
    }

    virtual void TearDown() {
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(SimpleTest, TestSimpleMustache) {
    const string expected = "text replaced text"
    ASSERT_EQ(result, expected);
}


}  // namespace

