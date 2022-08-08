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
  static auto GetParserGivenSchema(const string& schema) -> ArgumentParserStub {
    return ArgumentParserStub{};
  };
};

class AnArgumentParser : public Test {
 public:
  ArgumentParserStub parser = ArgumentParserStub::GetParserGivenSchema("");
};

TEST_F(AnArgumentParser, RetrievesBooleanFlagNotPresentAsArgument) {
  ASSERT_FALSE(parser.GetBooleanValue("f"));
}

TEST_F(AnArgumentParser, RetrievesBooleanFlagPresetAsArgument) {
  parser.setBooleanValue("g");
  ASSERT_TRUE(parser.GetBooleanValue("g"));
}
}  // namespace tests
}  // namespace args
