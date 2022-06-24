#include "include/Argument.hpp"

Argument::Argument(const string& name, ArgumentType type): name_{name}, type_(type)
{ }

bool Argument::operator==(const Argument& other) const
{
    return name_ == other.name_ && type_ == other.type_;
}

bool Argument::operator!=(const Argument& other) const
{
    return !(*this == other);
}