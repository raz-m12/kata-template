#include "gmock/gmock.h"
#include "include/ArgumentParser.hpp"

using namespace testing;

namespace args {
namespace tests {
using args::libs::ArgumentParser;
using ::testing::Test;

class AnArgumentParser : public Test {
 public:
  ArgumentParser parser;
};

TEST_F(AnArgumentParser, RetrievesValueOfABoolean) {
  ASSERT_FALSE(parser.getBooleanValue("f"));
}

TEST_F(AnArgumentParser, RetrievesValueOfABoolean) {
  parser.setBooleanValue("f");
  ASSERT_FALSE(parser.getBooleanValue("f"));
}
}  // namespace tests
}  // namespace args
