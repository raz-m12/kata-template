#include <utility>

#include "include/Argument.hpp"

using argskata::lib::Argument;
using std::string;
using std::hash;
using std::size_t;
using std::string;

namespace argskata
{
    namespace lib
    {

        auto ArgumentHasher::operator()(const Argument& arg) const -> size_t
        {
            // See https://stackoverflow.com/a/17017281/7883081
            
            return ((hash<string>()(arg.name_) ^
                     (hash<ArgumentType>()(arg.type_) << 1U)) >> 1U); // ^
                  // (hash<int>()(k.third) << 1);
        }

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

        auto Argument::name() const -> string
        {
            return name_;
        }

        auto Argument::type() const -> ArgumentType
        {
            return type_;
        }

    } // namespace lib
} // namespace argskata