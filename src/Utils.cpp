#include "include/Utils.hpp"

using std::hash;

namespace argskata {
namespace lib {
auto ArgumentHasher::operator()(const AbstractArgument &arg) const -> size_t {
  // See https://stackoverflow.com/a/17017281/7883081

  return ((hash<string>()(arg.Name()))); // ^
                                         //  (hash<ArgumentType>()(arg.Type())
                                         //  << 1U)) >> 1U); // ^
                                         // (hash<int>()(k.third) << 1);
}
} // namespace lib
} // namespace argskata
