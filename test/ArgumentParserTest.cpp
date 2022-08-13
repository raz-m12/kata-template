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
using std::make_shared;
using std::move;
using std::shared_ptr;
using std::string;
using ::testing::Return;
using ::testing::Test;

class SchemaMock : public ISchema {
 public:
  explicit SchemaMock(const string& schema) : ISchema(schema) {}

  MOCK_METHOD(bool, partOfSchema, (const string& param), (override));
};

class ArgumentParserMock : public ArgumentParser {
 public:
  explicit ArgumentParserMock(shared_ptr<ISchema> schema)
      : ArgumentParser{move(schema)} {}
  // MOCK_METHOD(void, setBooleanValue, (const string& arg), (override));

  // TODO(RV): Am I overriding this method or just creating a new one?
  static auto getParserGivenSchema(const string& input) -> ArgumentParserMock {
    shared_ptr<SchemaMock> schema = make_shared<SchemaMock>(input);
    return ArgumentParserMock{schema};
  };
};

class AnArgumentParserFixture : public Test {
 private:
  const string input{"f"};
  ArgumentParserMock _parser = ArgumentParserMock::getParserGivenSchema(input);
  shared_ptr<SchemaMock> _schema;

 protected:
  auto getSchema() -> shared_ptr<SchemaMock> { return _schema; }
  auto getParser() -> ArgumentParserMock& { return _parser; }
  void SetUp() override {
    shared_ptr<ISchema> ischema = _parser.getSchema();
    _schema = dynamic_pointer_cast<SchemaMock>(ischema);
  }
};

TEST_F(AnArgumentParserFixture, RetrievesBooleanFlagNotPresentAsArgument) {
  ON_CALL(*getSchema(), partOfSchema("f")).WillByDefault(Return(true));

  ASSERT_FALSE(getParser().getBooleanValue("f"));
}

TEST_F(AnArgumentParserFixture, RetrievesBooleanFlagPresentAsArgument) {
  EXPECT_CALL(*getSchema(), partOfSchema("g")).Times(1).WillOnce(Return(true));

  ASSERT_TRUE(getParser().getBooleanValue("g"));
}
}  // namespace tests
}  // namespace args
