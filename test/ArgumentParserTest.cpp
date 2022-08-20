#include "gmock/gmock.h"
#include "include/Argument.hpp"
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
using libs::BoolArgument;
using libs::IntArgument;
using libs::ISchema;
using libs::schemaMap;
using std::invalid_argument;
using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using ::testing::Return;
using ::testing::Test;

class SchemaStub : public ISchema {
 public:
  explicit SchemaStub(const string& schema) : ISchema(schema) {}

  auto parseSchema() -> schemaMap override {
    auto arg = make_unique<BoolArgument>(true);
    schemaMap map{};
    map.emplace("g", make_unique<BoolArgument>(true));
    map.emplace("d", make_unique<IntArgument>(3));
    return map;
  }

  MOCK_METHOD(bool, partOfSchema, (const string& param), (override));  // NOLINT
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

class AnArgumentParserFixture : public Test {
 protected:
  auto initParserUsingSchema(const string& input) -> void {
    _schema = make_shared<SchemaMock>(input);
    _schema->delegateToStub();

    _parser = make_unique<ArgumentParser>(_schema);
  };

  unique_ptr<ArgumentParser>
      _parser;                     // NOLINT(*-non-private-member-variables-*)
  shared_ptr<SchemaMock> _schema;  // NOLINT(*-non-private-member-variables-*)
};

TEST_F(AnArgumentParserFixture, GetsBooleanFlagNotPresentInSchema) {
  // Arrange
  initParserUsingSchema("f");
  ON_CALL(*_schema, partOfSchema("f")).WillByDefault(Return(true));

  // Act
  _parser->parseSchema();

  // Assert
  ASSERT_FALSE(_parser->get<bool>("f"));
}

TEST_F(AnArgumentParserFixture, GetsBooleanFlagPresentInSchema) {
  // Arrange
  initParserUsingSchema("g");
  EXPECT_CALL(*_schema, partOfSchema("g")).Times(1).WillOnce(Return(true));

  // Act
  _parser->parseSchema();

  // Assert
  ASSERT_TRUE(_parser->get<bool>("g"));
}

TEST_F(AnArgumentParserFixture, ThrowsWhenArgumentNotPartOfSchema) {
  initParserUsingSchema("");
  EXPECT_CALL(*_schema, partOfSchema(_)).Times(1).WillOnce(Return(false));

  ASSERT_THROW(_parser->get<bool>("f"), invalid_argument);
}

TEST_F(AnArgumentParserFixture, GetsIntegerFlagPresentInSchema) {
  // Arrange
  initParserUsingSchema("d#");
  EXPECT_CALL(*_schema, partOfSchema("d")).Times(1).WillOnce(Return(true));

  // Act
  _parser->parseSchema();

  // Assert
  auto result = _parser->get<int>("d");
  ASSERT_THAT(result, Eq(3));
}
}  // namespace tests
}  // namespace args
