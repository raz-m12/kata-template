#include "gmock/gmock.h"
#include "include/ArgumentParser.hpp"
#include "iostream"

using namespace testing;

namespace args {
namespace tests {
using args::libs::ArgumentParser;
using std::string;
using ::testing::Test;

class ArgumentParserStub : public ArgumentParser {
 public:
  MOCK_METHOD(bool, setBooleanValue, (const string& name));
};

class AnArgumentParser : public Test {
 public:
  ArgumentParserStub parser;
};

TEST_F(AnArgumentParser, RetrievesBooleanFlagNotPresentAsArgument) {
  ASSERT_FALSE(parser.getBooleanValue("f"));
}

TEST_F(AnArgumentParser, RetrievesBooleanFlagPresetAsArgument) {
  parser.setBooleanValue("g");
  ASSERT_TRUE(parser.getBooleanValue("g"));
}
}  // namespace tests
}  // namespace args
