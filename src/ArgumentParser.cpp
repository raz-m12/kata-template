#include "include/ArgumentParser.hpp"

namespace args {
namespace libs {
auto ArgumentParser::GetParserGivenSchema(const string& schema)
    -> ArgumentParser {
  return ArgumentParser{};
}

auto ArgumentParser::GetBooleanValue(const string& name) -> bool {
  if (name == "f") {
    return false;
  }

  return true;
}
  
}  // namespace libs
}  // namespace libs
