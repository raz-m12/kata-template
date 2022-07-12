#include "gmock/gmock.h"
#include "include/ArgsParser.hpp"

namespace argskata_test
{   
    using argskata::lib::ArgsParser;
    using testing::Eq;

    class AnIntegrationTest : public testing::Test
    {
    };
    

    // TODO(RV) Add fixture that describes the argument list tests
    //          Possibly add a parameterized test where needed

    TEST_F(AnIntegrationTest, BooleanFlagDefaultsToTrueIfInArgumentList)
    {
        ArgsParser parser{"(f)", {"-f"}};
        ASSERT_TRUE(parser.GetBooleanArgument("f"));
    }

    TEST_F(AnIntegrationTest, IntegerValueIsSetToThreeSinceInArgumentList)
    {
        ArgsParser parser{"(f#)", {"-f", "3"}};
        ASSERT_THAT(parser.GetIntegerArgument("f"), Eq(3));
    }
}