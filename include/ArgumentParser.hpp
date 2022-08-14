#ifndef ArgumentParser_h
#define ArgumentParser_h

#include "include/ISchema.hpp"
#include "iostream"
#include "memory"
#include "unordered_map"

namespace args {
namespace libs {
using std::shared_ptr;
using std::string;
using std::unordered_map;

class ArgumentParser {
 public:
  explicit ArgumentParser(shared_ptr<ISchema> schema);
  virtual ~ArgumentParser() = default;

  ArgumentParser(ArgumentParser const&) = delete;
  ArgumentParser(ArgumentParser&&) = delete;
  auto operator=(ArgumentParser const&) -> ArgumentParser& = delete;
  auto operator=(ArgumentParser &&) -> ArgumentParser& = delete;

  static auto getParserGivenSchema(const string& input) -> ArgumentParser;
  auto getSchema() -> shared_ptr<ISchema>;

  auto getBooleanValue(const string& arg) -> bool;
  virtual auto setBooleanValue(const string& arg) -> void;

 private:
  // TODO(RV) Could be generalized to become a template
  auto boolPresentAsCmdLineArg(const string& arg) -> bool;

  unordered_map<string, string> keyValuePairs;
  shared_ptr<ISchema> _schema;
};
}  // namespace libs
}  // namespace args

#endif
