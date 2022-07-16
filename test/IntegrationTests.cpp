#include "gmock/gmock.h"
#include "include/ArgsParser.hpp"

/**
 *  TODO(RV) Possibly add a parameterized tests
 */

namespace argskata_test {
using argskata::lib::ArgsParser;
using std::string;
using testing::ElementsAreArray;
using testing::Eq;

class AnIntegrationTest : public testing::Test {};

TEST_F(AnIntegrationTest, BooleanFlagDefaultsToTrueSinceInArgumentList) {
  ArgsParser parser{"(f)", {"-f"}};
  ASSERT_TRUE(parser.GetBooleanArgument("f"));
}

TEST_F(AnIntegrationTest, IntegerFlagIsSetToThree) {
  ArgsParser parser{"(f#)", {"-f", "3"}};
  ASSERT_THAT(parser.GetIntegerArgument("f"), Eq(3));
}

TEST_F(AnIntegrationTest, StringFlagIsSetToHelloWorldSinceIn) {
  ArgsParser parser{"(f*)", {"-f", "HelloWorld"}};
  ASSERT_THAT(parser.GetStringArgument("f"), Eq("HelloWorld"));
}

TEST_F(AnIntegrationTest, DoubleFlagIsSetThreePointFourteen) {
  ArgsParser parser{"(f##)", {"-f", "3.14"}};
  ASSERT_THAT(parser.GetDoubleArgument("f"), Eq(3.14));
}

TEST_F(AnIntegrationTest, StringArrayIsSetToTwoDistinctStrings) {
  ArgsParser parser{"(f[*])", {"-f", "Hello", "-f", "World"}};

  ASSERT_THAT(parser.GetStringArrayArgument("f"),
              ElementsAreArray({"Hello", "World"}));
}

TEST_F(AnIntegrationTest, StressTestWithAllArgumentTypes) {
  ArgsParser parser{"(f,s*,n#,a##,p[*])",
                    {"-f", "-s", "Bob", "-n", "1", "-a", "3.2", "-p", "e1",
                     "-p", "e2", "-p", "e3"}};

  ASSERT_TRUE(parser.GetBooleanArgument("f"));
  ASSERT_THAT(parser.GetStringArgument("s"), Eq("Bob"));
  ASSERT_THAT(parser.GetIntegerArgument("n"), Eq(1));
  ASSERT_THAT(parser.GetDoubleArgument("a"), Eq(3.2));
  ASSERT_THAT(parser.GetStringArrayArgument("p"),
              ElementsAreArray({"e1", "e2", "e3"}));
}
}  // namespace argskata_test
