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
 * https://chromium.googlesource.com/external/github.com/google/googletest/+/refs/heads/77A9B20B4C1E02FAC90D1D942E1D4C18/googlemock/docs/cheat_sheet.md
 * EXPECT_CALL(testobject, testfunction(_, _, _))
 *   .WillOnce(DoAll(SetArgReferee<0>(v), SetArgReferee<1>(i), Return(true)));
 *
 * Using Predicates as Matchers
 * int IsEven(int n) { return (n % 2) == 0 ? 1 : 0; }
 * ...
 * // Bar() must be called with an even number.
 * EXPECT_CALL(foo, Bar(Truly(IsEven)));
 */

namespace args {
namespace tests {
using libs::ArgumentParser;
using libs::ISchema;
using libs::schemaMap;
using std::dynamic_pointer_cast;
using std::invalid_argument;
using std::make_shared;
using std::move;
using std::shared_ptr;
using std::string;
using ::testing::Return;
using ::testing::Test;

class SchemaStub : public ISchema {
 public:
  explicit SchemaStub(const string& schema) : ISchema(schema) {}

  auto parseSchema() -> schemaMap override { return {{"g", "true"}}; }

  MOCK_METHOD(bool, partOfSchema, (const string& param), (override)); // NOLINT
};

class SchemaMock : public ISchema {
 public:
  explicit SchemaMock(const string& schema) : ISchema(schema) {}

  MOCK_METHOD(bool, partOfSchema, (const string& param), (override));  // NOLINT
  MOCK_METHOD(schemaMap, parseSchema, (), (override));                 // NOLINT

  void delegateToStub() {
    ON_CALL(*this, parseSchema).WillByDefault([this]() -> schemaMap {
      return stub_.parseSchema();
    });
  }

 private:
  SchemaStub stub_{""};
};

class ArgumentParserStub : public ArgumentParser {
 public:
  explicit ArgumentParserStub(shared_ptr<ISchema> schema)
      : ArgumentParser{move(schema)} {}
  // MOCK_METHOD(void, setBooleanValue, (const string& arg), (override));

  static auto getParserGivenSchema(const string& input) -> ArgumentParserStub {
    shared_ptr<SchemaMock> schema = make_shared<SchemaMock>(input);
    schema->delegateToStub();
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
