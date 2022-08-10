#ifndef ArgumentParser_h
#define ArgumentParser_h

#include "iostream"

namespace args {
namespace libs {
using std::string;
class ArgumentParser {
 public:
  static auto getParserGivenSchema(const string& schema) -> ArgumentParser;
  auto getBooleanValue(const string& arg) -> bool;
  virtual auto setBooleanValue(const string& arg) -> void;
};
}  // namespace libs
}  // namespace args

#endif
