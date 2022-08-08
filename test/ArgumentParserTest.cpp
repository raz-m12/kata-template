#include "gmock/gmock.h"
#include "include/ArgumentParser.hpp"

using namespace testing;

namespace Tests {
using ::testing::Test;

class AnArgumentParser : public Test {
  ArgumentParser parser;
};

TEST_F(AnArgumentParser, RetrievesValueOfABoolean) {
  ASSERT_FALSE(parser.getArgValue('f'));
}
}  // namespace Tests