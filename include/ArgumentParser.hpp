#ifndef ArgumentParser_h
#define ArgumentParser_h

#include "include/ISchema.hpp"
#include "include/Argument.hpp"
#include "include/Utilities.hpp"
#include "iostream"
#include "memory"
#include "unordered_map"


namespace args {
namespace libs {
using std::invalid_argument;
using std::is_integral_v;
using std::is_same;
using std::shared_ptr;
using std::stoi;
using std::string;
using std::unordered_map;
using std::unique_ptr;

/* TODO(RV). Question: is it ok not to depend on an interface? */
class ArgumentParser {
 public:
  explicit ArgumentParser(shared_ptr<ISchema> schema);
  virtual ~ArgumentParser() = default;

  ArgumentParser(ArgumentParser const&) = delete;
  ArgumentParser(ArgumentParser&&) = delete;
  auto operator=(ArgumentParser const&) -> ArgumentParser& = delete;
  auto operator=(ArgumentParser &&) -> ArgumentParser& = default;

  static auto getParserGivenSchema(const string& input) -> ArgumentParser;
  auto parseSchema() -> void;
  auto getSchema() -> shared_ptr<ISchema>;

  virtual auto setBooleanValue(const string& arg) -> void;

  template <class T>
  auto get(const string& arg) -> T;

 private:
  // TODO(RV) Could be generalized to become a template

  auto boolPresentAsCmdLineArg(const string& arg) -> bool;

  // TODO(RV) to remove this variable
  unordered_map<string, string> keyValuePairs_;
  unordered_map<string, unique_ptr<IArgument>> keyValuePairs__;
  shared_ptr<ISchema> _schema;
};

template <class T>
auto ArgumentParser::get(const string& arg) -> T {
  if (!_schema->partOfSchema(arg)) {
    throw invalid_argument("argument not part of schema");
  }
  const auto value = keyValuePairs_[arg];
  if(!keyValuePairs__[arg]) {
    return defaultValueOf<T>();
  }
  return keyValuePairs__[arg]->getValue<T>();
}

}  // namespace libs
}  // namespace args

#endif
