#ifndef ArgumentParser_h
#define ArgumentParser_h

#include "iostream"

namespace args {
namespace libs {
using std::string;
class ArgumentParser {
 public:
  static auto GetParserGivenSchema(const string& schema) -> ArgumentParser;
  auto GetBooleanValue(const string& name) -> bool;
};
}  // namespace libs
}  // namespace args

#endif
