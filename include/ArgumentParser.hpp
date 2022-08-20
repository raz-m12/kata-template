#ifndef ArgumentParser_h
#define ArgumentParser_h

#include "include/ISchema.hpp"
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

  unordered_map<string, string> keyValuePairs_;
  shared_ptr<ISchema> _schema;
};

template <class T>
auto ArgumentParser::get(const string& arg) -> T {
  if (!_schema->partOfSchema(arg)) {
    throw invalid_argument("argument not part of schema");
  }
  const auto value = keyValuePairs_[arg];

  if (is_same<T, int>::value) {
    return stoi(value);
  }
  if (is_same<T, bool>::value) {
    return boolPresentAsCmdLineArg(arg);
  }
}

}  // namespace libs
}  // namespace args

#endif
