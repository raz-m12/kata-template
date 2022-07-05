#include <utility>

#include "include/Argument.hpp"

using argskata::lib::AbstractArgument;
using std::string;
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

        auto BooleanArgument::SetValue(string /* argValue */) -> void
        {
            value_ = true;
        }

        auto BooleanArgument::Value(const shared_ptr<AbstractArgument>& arg) -> bool
        {
            auto ptr = dynamic_pointer_cast<BooleanArgument>(arg);
            if(ptr != nullptr)
            {
                return ptr->value_;
            }
            return false;
        }

    } // namespace lib
} // namespace argskata