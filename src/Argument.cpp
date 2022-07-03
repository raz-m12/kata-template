#include <utility>

#include "include/Argument.hpp"

using argskata::lib::AbstractArgument;
using std::string;
using std::hash;
using std::size_t;
using std::string;

namespace argskata
{
    namespace lib
    {
        AbstractArgument::AbstractArgument(string name, ArgumentType type) : name_{std::move(name)}, type_(type)
        {
        }

        auto AbstractArgument::operator==(const AbstractArgument &other) const -> bool
        {
            return name_ == other.name_ && type_ == other.type_;
        }

        auto AbstractArgument::operator!=(const AbstractArgument &other) const -> bool
        {
            return !(*this == other);
        }

        auto AbstractArgument::Name() const -> string
        {
            return name_;
        }

        auto AbstractArgument::Type() const -> ArgumentType
        {
            return type_;
        }

    } // namespace lib
} // namespace argskata