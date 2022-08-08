#include "include/ArgumentParser.hpp"

namespace args {
namespace libs {
auto ArgumentParser::getBooleanValue(const string& name) -> bool {
  if(name == "f") {
    return false;
  } else {
    return true;
  }
}

}  // namespace libs
}  // namespace args
