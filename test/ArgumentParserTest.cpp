#include "gmock/gmock.h"
#include "include/ArgumentParser.hpp"
#include "include/ISchema.hpp"
#include "iostream"

using namespace testing;

/**
 * Selecting Between Overloaded Functions (Cookbook)
 * EXPECT_CALL(printer, Print(An<int>()));            // void Print(int);
 * EXPECT_CALL(printer, Print(Matcher<int>(Lt(5))));  // void Print(int);
 * EXPECT_CALL(printer, Print(TypedEq<char>('a')));   // void Print(char);
 */

namespace args {
namespace tests {
using libs::ArgumentParser;
using libs::ISchema;
using std::make_shared;
using std::shared_ptr;
using std::unique_ptr;
using std::string;
using ::testing::Test;

class SchemaMock : public ISchema {
 public:
  SchemaMock(const string& schema) : ISchema(schema) {}

  MOCK_METHOD(bool, partOfSchema, (const string& param), (override));
};


class ArgumentParserMock : public ArgumentParser {
 public:
  explicit ArgumentParserMock(shared_ptr<ISchema> schema)
      : ArgumentParser{schema} {}
  // MOCK_METHOD(void, setBooleanValue, (const string& arg), (override));

  // TODO: Am I overriding this method or just creating a new one?
  static auto getParserGivenSchema(const string& input) -> ArgumentParserMock {
    shared_ptr<SchemaMock> schema = make_shared<SchemaMock>(input);
    return ArgumentParserMock{schema};
  };
};


class AnArgumentParserFixture : public Test {
 public:
  const string schema{"f"};
  const shared_ptr<SchemaMock> schemaMock = make_shared<SchemaMock>(schema);
  const unique_ptr<ArgumentParserMock> parser = nullptr;
};


TEST_F(AnArgumentParserFixture, RetrievesBooleanFlagNotPresentAsArgument) {
  ArgumentParserMock mock = ArgumentParserMock::getParserGivenSchema(schema);

  // ASSERT_FALSE(mock.getBooleanValue("f"));
}

TEST_F(AnArgumentParserFixture, RetrievesBooleanFlagPresentAsArgument) {
  shared_ptr<ISchema> ischema = parser->getSchema();

  // EXPECT_CALL(*ischema, partOfSchema("g")).Times(1);

  ArgumentParserMock mock = ArgumentParserMock::getParserGivenSchema(schema);

  ASSERT_TRUE(mock.getBooleanValue("g"));
}
}  // namespace tests
}  // namespace args
