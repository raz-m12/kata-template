#include "include/Argument.hpp"

namespace args::libs {

BoolArgument::BoolArgument(bool value) : _value{value} {}
auto BoolArgument::getValueProected() -> any { return _value; }

IntArgument::IntArgument(int value) : _value{value} {}
auto IntArgument::getValueProected() -> any { return _value; }
}  // namespace args::libs