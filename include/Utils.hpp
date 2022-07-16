#ifndef UTILS_HPP
#define UTILS_HPP

#include "include/Argument.hpp"
#include "iostream"

namespace argskata {
namespace lib {
namespace impl {
class ArgumentHasher {
public:
  auto operator()(const AbstractArgument &arg) const -> size_t;
};
} // namespace impl

using impl::ArgumentHasher;
} // namespace lib
} // namespace argskata

#endif