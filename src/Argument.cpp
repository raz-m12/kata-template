#include "include/Argument.hpp"

namespace args::libs {
using std::move;

BoolArgument::BoolArgument(bool value) : _value{value} {}
auto BoolArgument::getValueProected() -> any { return _value; }

IntArgument::IntArgument(int value) : _value{value} {}
auto IntArgument::getValueProected() -> any { return _value; }

StringArgument::StringArgument(string value) : _value{move(value)} {}
auto StringArgument::getValueProected() -> any { return _value; }

DoubleArgument::DoubleArgument(double value) : _value{value} {}
auto DoubleArgument::getValueProected() -> any { return _value; }
}  // namespace args::libs