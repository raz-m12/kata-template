#include "gmock/gmock.h"
#include "include/ArgsParser.hpp"

/**
 *  TODO(RV) Possibly add a parameterized tests
 */

namespace argskata_test
{   
    using std::string;
    using testing::ElementsAreArray;
    using testing::Eq;
    using argskata::lib::ArgsParser;

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
}