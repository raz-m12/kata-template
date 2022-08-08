#ifndef ArgumentParser_h
#define ArgumentParser_h

#include "iostream"

namespace args {
namespace libs {
using std::string;
class ArgumentParser {
 public:
  auto getBooleanValue(const string& name) -> bool;
};
}  // namespace libs
}  // namespace args

#endif
