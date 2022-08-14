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
using std::dynamic_pointer_cast;
using std::invalid_argument;
using std::make_shared;
using std::move;
using std::shared_ptr;
using std::string;
using ::testing::Return;
using ::testing::Test;

class SchemaMock : public ISchema {
 public:
  explicit SchemaMock(const string& schema) : ISchema(schema) {}

  MOCK_METHOD(bool, partOfSchema, (const string& param), (override));  // NOLINT
};

class ArgumentParserStub : public ArgumentParser {
 public:
  explicit ArgumentParserStub(shared_ptr<ISchema> schema)
      : ArgumentParser{move(schema)} {}
  // MOCK_METHOD(void, setBooleanValue, (const string& arg), (override));

  static auto getParserGivenSchema(const string& input) -> ArgumentParserStub {
    shared_ptr<SchemaMock> schema = make_shared<SchemaMock>(input);
    return ArgumentParserStub{schema};
  };
};

class AnArgumentParserFixture : public Test {
 protected:
  // NOLINTBEGIN(*-non-private-member-variables-in-classes)
  const string input{"f"};
  ArgumentParserStub _parser = ArgumentParserStub::getParserGivenSchema(input);
  shared_ptr<SchemaMock> _schema;
  // NOLINTEND(*-non-private-member-variables-in-classes)

  void SetUp() override {
    shared_ptr<ISchema> ischema = _parser.getSchema();
    _schema = dynamic_pointer_cast<SchemaMock>(ischema);
  }
};

TEST_F(AnArgumentParserFixture, RetrievesBooleanFlagNotPresentAsArgument) {
  ON_CALL(*_schema, partOfSchema("f")).WillByDefault(Return(true));

  ASSERT_FALSE(_parser.getBooleanValue("f"));
}

TEST_F(AnArgumentParserFixture, RetrievesBooleanFlagPresentAsArgument) {
  EXPECT_CALL(*_schema, partOfSchema("g")).Times(1).WillOnce(Return(true));

  ASSERT_TRUE(_parser.getBooleanValue("g"));
}

TEST_F(AnArgumentParserFixture, ThrowsWhenArgumentNotPartOfSchema) {
  EXPECT_CALL(*_schema, partOfSchema(_)).Times(1).WillOnce(Return(false));

  ASSERT_THROW(_parser.getBooleanValue("f"), invalid_argument);
}
}  // namespace tests
}  // namespace args
