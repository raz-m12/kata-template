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
  MOCK_METHOD(void, setBooleanValue, (const string& arg), (override));

  static auto getParserGivenSchema(const string& schema) -> ArgumentParserStub {
    return ArgumentParserStub{};
  };
};

class AnArgumentParser : public Test {
 public:
  ArgumentParserStub mock = ArgumentParserStub::getParserGivenSchema("");
};

TEST_F(AnArgumentParser, RetrievesBooleanFlagNotPresentAsArgument) {
  ASSERT_FALSE(mock.getBooleanValue("f"));
}

TEST_F(AnArgumentParser, RetrievesBooleanFlagPresentAsArgument) {
  EXPECT_CALL(mock, setBooleanValue("g")).Times(1);

  mock.setBooleanValue("g");
  ASSERT_TRUE(mock.getBooleanValue("g"));
}
}  // namespace tests
}  // namespace args
