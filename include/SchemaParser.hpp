#ifndef SCHEMAPARSER_HPP
#define SCHEMAPARSER_HPP

#include "include/Argument.hpp"
#include "iostream"
#include "memory"
#include "unordered_map"
#include "vector"

namespace argskata {
namespace lib {
namespace impl {
using namespace std;
using std::shared_ptr;

class SchemaMustStartAndEndWithParenthesisException : public exception {};

class SchemaInvalidCharacterDetectedException : public exception {};

class ArgumentNotPartOfSchemaException : public exception {};

class MissingArgumentValueException : public exception {};

class SchemaParser {
 public:
  void Parse(const string &bareSchema, const vector<string> &args);
  [[nodiscard]] auto GetSchema() const
      -> unordered_map<string, shared_ptr<AbstractArgument> >;
  [[nodiscard]] auto GetBooleanArgument(const string &argName) const -> bool;
  [[nodiscard]] auto GetStringArgument(const string &argName) const -> string;
  [[nodiscard]] auto GetIntegerArgument(const string &argName) const -> int;
  [[nodiscard]] auto GetDoubleArgument(const string &argName) const -> double;
  [[nodiscard]] auto GetStringArrayArgument(const string &argName) const
      -> vector<string>;

 private:
  unordered_map<string, shared_ptr<AbstractArgument> > schema_;

  static void AssertValidSchemaFormat(const string &bareSchema,
                                      const vector<string> &args);
  [[nodiscard]] static auto SchemaStartsAndEndsWithParenthesis(
      const string &schema) -> bool;
  [[nodiscard]] static auto SchemaIsEmptyAndThereAreArgumentsToParse(
      const string &schema, const vector<string> &args) -> bool;

  auto PopulateSchemaWithArguments(const string &schema) -> void;
  [[nodiscard]] static auto IsSchemaLastToken(const string &token) -> bool;
  [[nodiscard]] static auto IsBooleanType(const string &token) -> bool;
  [[nodiscard]] static auto IsIntegerType(const string &token) -> bool;
  [[nodiscard]] static auto IsStringType(const string &token) -> bool;
  [[nodiscard]] static auto IsDoubleType(const string &token) -> bool;
  [[nodiscard]] static auto IsStringArrayType(const string &token) -> bool;
  static auto StripChars(string &token, ArgumentType tokenType) -> void;

  auto PopulateArgumentsWithValues(const vector<string> &args) -> void;
  static auto StripNonAlphaChars(const vector<string> &args) -> vector<string>;
  auto GetAbstractArg(const std::string &arg) -> shared_ptr<AbstractArgument> &;
};
}  // namespace impl
using impl::ArgumentNotPartOfSchemaException;
using impl::MissingArgumentValueException;
using impl::SchemaInvalidCharacterDetectedException;
using impl::SchemaMustStartAndEndWithParenthesisException;
using impl::SchemaParser;
}  // namespace lib
}  // namespace argskata

#endif