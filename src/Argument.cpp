#include "include/Argument.hpp"

namespace args {
namespace libs {

auto BoolArgument::getValueProected() -> any { return _value; }

auto IntArgument::getValueProected() -> any { return _value; }
}
}  // namespace args