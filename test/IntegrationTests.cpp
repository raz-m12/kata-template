#include "gmock/gmock.h"
#include "include/ArgsParser.hpp"

/**
 *  TODO(RV) Possibly add a parameterized tests
 */

namespace argskata_test
{
    using argskata::lib::ArgsParser;
    using std::string;
    using testing::ElementsAreArray;
    using testing::Eq;

    class AnIntegrationTest : public testing::Test
    {
    };

    TEST_F(AnIntegrationTest, BooleanFlagDefaultsToTrueSinceInArgumentList)
    {
        ArgsParser parser{"(f)", {"-f"}};
        ASSERT_TRUE(parser.GetBooleanArgument("f"));
    }

    TEST_F(AnIntegrationTest, IntegerFlagIsSetToThree)
    {
        ArgsParser parser{"(f#)", {"-f", "3"}};
        ASSERT_THAT(parser.GetIntegerArgument("f"), Eq(3));
    }

    TEST_F(AnIntegrationTest, StringFlagIsSetToHelloWorldSinceIn)
    {
        ArgsParser parser{"(f*)", {"-f", "HelloWorld"}};
        ASSERT_THAT(parser.GetStringArgument("f"), Eq("HelloWorld"));
    }

    TEST_F(AnIntegrationTest, DoubleFlagIsSetThreePointFourteen)
    {
        ArgsParser parser{"(f##)", {"-f", "3.14"}};
        ASSERT_THAT(parser.GetDoubleArgument("f"), Eq(3.14));
    }

    TEST_F(AnIntegrationTest, StringArrayIsSetToTwoDistinctStrings)
    {
        ArgsParser parser{"(f[*])", {"-f", "Hello", "-f", "World"}};

        ASSERT_THAT(parser.GetStringArrayArgument("f"), ElementsAreArray({"Hello", "World"}));
    }

    TEST_F(AnIntegrationTest, TestsAnArgumentParserWithABooleanAndAStringArray)
    {
        ArgsParser parser{"(s[*],b)", {"-s", "Hi", "-s", "Hello", "-s", "There", "-b"}};

        ASSERT_THAT(parser.GetStringArrayArgument("s"), ElementsAreArray({"Hi", "Hello", "There"}));
        ASSERT_TRUE(parser.GetBooleanArgument("-b"));
    }
} // namespace argskata_test
