#ifndef ArgumentParser_h
#define ArgumentParser_h

#include "include/Argument.hpp"
#include "include/ISchema.hpp"
#include "include/Utilities.hpp"
#include "iostream"
#include "memory"
#include "unordered_map"

namespace args::libs {
using std::invalid_argument;
using std::is_integral_v;
using std::shared_ptr;
using std::string;

/* TODO(RV). Question: is it ok not to depend on an interface? */
class ArgumentParser {
 public:
  explicit ArgumentParser(shared_ptr<ISchema> schema);
  virtual ~ArgumentParser() = default;

  ArgumentParser(ArgumentParser const&) = delete;
  ArgumentParser(ArgumentParser&&) = delete;
  auto operator=(ArgumentParser const&) -> ArgumentParser& = delete;
  auto operator=(ArgumentParser&&) -> ArgumentParser& = default;

  static auto getParserGivenSchema(const string& input) -> ArgumentParser;
  auto parseArguments(const string& values) -> void;
  auto getSchema() -> shared_ptr<ISchema>;

  virtual auto setBooleanValue(const string& arg) -> void;

  template <class T>
  auto get(const string& arg) -> T;

 private:
  // TODO(RV) Could be generalized to become a template

  auto boolPresentAsCmdLineArg(const string& arg) -> bool;

  // TODO(RV) to remove this variable
  schemaMap keyValuePairs_;
  shared_ptr<ISchema> _schema;
};

template <class T>
auto ArgumentParser::get(const string& arg) -> T {
  if (!_schema->partOfSchema(arg)) {
    throw invalid_argument("argument not part of schema");
  }
  if (!keyValuePairs_[arg]) {
    return defaultValueOf<T>();
  }
  return keyValuePairs_[arg]->getValue<T>();
}

}  // namespace args::libs

#endif
