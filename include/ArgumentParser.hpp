#ifndef ArgumentParser_h
#define ArgumentParser_h

#include "iostream"
#include "include/ISchema.hpp"

namespace args {
namespace libs {
using std::string;

class ArgumentParser {
 public:
  explicit ArgumentParser(ISchema* schema);
  virtual ~ArgumentParser() = default;

  ArgumentParser(ArgumentParser const &) = delete;
  ArgumentParser(ArgumentParser &&) = delete;
  auto operator=(ArgumentParser const &) -> ArgumentParser & = delete;
  auto operator=(ArgumentParser &&) -> ArgumentParser & = delete;

  static auto getParserGivenSchema(const string& schema) -> ArgumentParser;

  auto getBooleanValue(const string& arg) -> bool;
  virtual auto setBooleanValue(const string& arg) -> void;

 private:
  ISchema* _schema;
};
}  // namespace libs
}  // namespace args

#endif
