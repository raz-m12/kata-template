// NOLINTBEGIN(*-non-private-member-variables-*)

#include <gmock/gmock-matchers.h>
#include <vector>

#include "gmock/gmock.h"
#include "include/Argument.hpp"
#include "include/ArgumentParser.hpp"
#include "include/ISchema.hpp"
#include "iostream"

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

namespace args::tests {
using libs::ArgumentParser;
using libs::BoolArgument;
using libs::DoubleArgument;
using libs::IntArgument;
using libs::StringArrayArgument;
using libs::ISchema;
using libs::schemaMap;
using libs::StringArgument;
using std::invalid_argument;
using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;
using ::testing::_;
using ::testing::Eq;
using ::testing::Return;
using ::testing::Test;
using ::testing::ElementsAreArray;

class SchemaStub : public ISchema {
 public:
  explicit SchemaStub(const string& schema) : ISchema(schema) {}

  auto getKeyValuePairs(const string& /* values */) -> schemaMap override {
    auto arg = make_unique<BoolArgument>(true);
    schemaMap map{};
    map.emplace("g", make_unique<BoolArgument>(true));
    map.emplace("i", make_unique<IntArgument>(3));
    map.emplace("s", make_unique<StringArgument>("abcde"));
    map.emplace("d", make_unique<DoubleArgument>(doubleValue));
    map.emplace("a", make_unique<StringArrayArgument>(strArrValue));
    return map;
  }

  MOCK_METHOD(void, parseSchema, (), (override));                      // NOLINT
  MOCK_METHOD(bool, partOfSchema, (const string& param), (override));  // NOLINT

 private:
  const double doubleValue = 34.5;
  const vector<string> strArrValue = { "Hello", "World" };
};

class SchemaMock : public ISchema {
 public:
  explicit SchemaMock(const string& schema) : ISchema(schema) {}

  MOCK_METHOD(bool, partOfSchema, (const string& param), (override));  // NOLINT
  MOCK_METHOD(void, parseSchema, (), (override));                      // NOLINT
  MOCK_METHOD(schemaMap, getKeyValuePairs, (const string& param),      // NOLINT
              (override));  

  void delegateToStub() {
    ON_CALL(*this, getKeyValuePairs).WillByDefault([this]() -> schemaMap {
      return stub_.getKeyValuePairs("");
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

TEST_F(AnArgumentParserFixture, MockSchemaBooleanNotPresent) {
  // Arrange
  initParserUsingSchema("f");
  ON_CALL(*_schema, partOfSchema("f")).WillByDefault(Return(true));

  // Act
  _parser->parseArguments("-f");

  // Assert
  ASSERT_FALSE(_parser->get<bool>("f"));
}

TEST_F(AnArgumentParserFixture, MockSchemaGetsBoolean) {
  // Arrange
  initParserUsingSchema("g");
  EXPECT_CALL(*_schema, partOfSchema("g")).Times(1).WillOnce(Return(true));

  // Act
  _parser->parseArguments("-g");

  // Assert
  ASSERT_TRUE(_parser->get<bool>("g"));
}

TEST_F(AnArgumentParserFixture, MockSchemaThrowsWhenArgumentNotPartOf) {
  initParserUsingSchema("");
  EXPECT_CALL(*_schema, partOfSchema(_)).Times(1).WillOnce(Return(false));

  ASSERT_THROW(_parser->get<bool>("f"), invalid_argument);
}

TEST_F(AnArgumentParserFixture, MockSchemaGetsInteger) {
  // Arrange
  initParserUsingSchema("i#");
  EXPECT_CALL(*_schema, partOfSchema("i")).Times(1).WillOnce(Return(true));

  // Act
  _parser->parseArguments("-i 3");

  // Assert
  auto result = _parser->get<int>("i");
  ASSERT_THAT(result, Eq(3));
}

TEST_F(AnArgumentParserFixture, MockSchemaGetsString) {
  // Arrange
  initParserUsingSchema("s*");
  EXPECT_CALL(*_schema, partOfSchema("s")).Times(1).WillOnce(Return(true));

  // Act
  _parser->parseArguments("-s abcde");

  // Assert
  auto result = _parser->get<string>("s");
  ASSERT_THAT(result, Eq("abcde"));
}

TEST_F(AnArgumentParserFixture, MockSchemaGetsDouble) {
  // Arrange
  initParserUsingSchema("d##");
  EXPECT_CALL(*_schema, partOfSchema("d")).Times(1).WillOnce(Return(true));

  // Act
  _parser->parseArguments("-d 34.5");

  // Assert
  auto result = _parser->get<double>("d");
  ASSERT_THAT(result, Eq(34.5));
}

TEST_F(AnArgumentParserFixture, MockSchemaGetsStringArray) {
  // Arrange
  initParserUsingSchema("a[*]");
  EXPECT_CALL(*_schema, partOfSchema("a")).Times(1).WillOnce(Return(true));

  // Act
  _parser->parseArguments("-a Hello -a World");

  // Assert
  auto result = _parser->get<vector<string>>("a");
  ASSERT_THAT(result, ElementsAreArray(result));
}


}  // namespace args::tests
