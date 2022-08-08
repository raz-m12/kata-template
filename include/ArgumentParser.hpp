#ifndef ArgumentParser_h
#define ArgumentParser_h

#include "iostream"


namespace args {
namespace libs {
using std::string;
class ArgumentParser {
 public:
  auto getArgValue(string name) -> bool;
};
}  // namespace lib
}  // namespace args

#endif
