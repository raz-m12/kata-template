#include <utility>

#include "include/Argument.hpp"

using argskata::lib::Argument;
using std::string;

namespace argskata
{
    namespace lib
    {

        Argument::Argument(string name, ArgumentType type) : name_{std::move(name)}, type_(type)
        {
        }

        auto Argument::operator==(const Argument &other) const -> bool
        {
            return name_ == other.name_ && type_ == other.type_;
        }

        auto Argument::operator!=(const Argument &other) const -> bool
        {
            return !(*this == other);
        }
    } // namespace lib
} // namespace argskata