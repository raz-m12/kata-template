#include <gmock/gmock-matchers.h>

#include <vector>

#include "gmock/gmock.h"
#include "include/Argument.hpp"
#include "include/ArgumentParser.hpp"
#include "include/ISchema.hpp"
#include "iostream"

namespace args::tests {
using libs::ArgumentParser;
using libs::BoolArgument;
using libs::DoubleArgument;
using libs::IntArgument;
using libs::ISchema;
using libs::schemaMap;
using libs::StringArgument;
using libs::StringArrayArgument;
using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;
using ::testing::Test;

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
  const vector<string> strArrValue = {"Hello", "World"};
};

class SchemaMock : public ISchema {
 public:
  explicit SchemaMock(const string& schema) : ISchema(schema) {}

  MOCK_METHOD(bool, partOfSchema, (const string& param), (override));  // NOLINT
  MOCK_METHOD(void, parseSchema, (), (override));                      // NOLINT
  MOCK_METHOD(schemaMap, getKeyValuePairs, (const string& param),      // NOLINT
              (override));

  void delegateToStub(bool useStub) {
    ON_CALL(*this, getKeyValuePairs).WillByDefault([this, useStub]() -> schemaMap {
      if(useStub) {
        return stub_.getKeyValuePairs("");
      }
      return {};
    });
  }

 private:
  SchemaStub stub_{""};
  // Schema
};
}  // namespace args::tests
