#include "include/ArgumentParser.hpp"

namespace args {
namespace libs {
auto ArgumentParser::getParserGivenSchema(const string& schema)
    -> ArgumentParser {
  return ArgumentParser{};
}

auto ArgumentParser::getBooleanValue(const string& arg) -> bool {
  if (arg == "f") {
    return false;
  }

  return true;
}

/** TODO(RV) is being mocked */
auto ArgumentParser::setBooleanValue(const string& arg) -> void {
}

}  // namespace libs
}  // namespace args
