#include <utility>

#include "include/Argument.hpp"

using argskata::lib::AbstractArgument;
using std::size_t;
using std::string;


namespace argskata
{
    namespace lib
    {
        AbstractArgument::AbstractArgument(string name) : name_{std::move(name)}
        {
        }

        /* TODO(RV) extend this operator to test values */
        auto AbstractArgument::operator==(const AbstractArgument &other) const -> bool
        {
            return name_ == other.name_;
        }

        auto AbstractArgument::operator!=(const AbstractArgument &other) const -> bool
        {
            return !(*this == other);
        }

        auto AbstractArgument::Name() const -> string
        {
            return name_;
        }

        auto BooleanArgument::SetValue(string) -> void
        {
            value_ = true;
        }

        auto BooleanArgument::Value(const shared_ptr<AbstractArgument> &arg) -> bool
        {
            auto ptr = dynamic_pointer_cast<BooleanArgument>(arg);
            if (ptr != nullptr)
            {
                return ptr->value_;
            }
            return false;
        }

        auto BooleanArgument::Type() -> ArgumentType 
        {
            return ArgumentType::_boolean;
        }

        auto IntegerArgument::SetValue(string value) -> void
        {
            try
            {
                value_ = stoi(value);
            }
            catch (const std::exception& e)
            {
                throw InvalidArgumentValueException(e.what());
            }
        }

        auto IntegerArgument::Value(const shared_ptr<AbstractArgument> &arg) -> int
        {
            auto ptr = dynamic_pointer_cast<IntegerArgument>(arg);
            if (ptr != nullptr)
            {
                return ptr->value_;
            }
            return 0;
        }

        auto IntegerArgument::Type() -> ArgumentType 
        {
            return ArgumentType::_integer;
        }

        auto StringArgument::SetValue(string value) -> void
        {
            value_ = value;
        }

        auto StringArgument::Value(const shared_ptr<AbstractArgument> &arg) -> string
        {
            auto ptr = dynamic_pointer_cast<StringArgument>(arg);
            if (ptr != nullptr)
            {
                return ptr->value_;
            }
            // TODO(RV)
            return "";
        }

        auto StringArgument::Type() -> ArgumentType 
        {
            return ArgumentType::_string;
        }

    } // namespace lib
} // namespace argskata