#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include "iostream"

namespace argskata
{
    namespace lib
    {
        namespace impl
        {
            using std::string;
            using std::size_t;

            enum ArgumentType
            {
                _boolean,
                _string,
                _integer,
                _double,
                _strArr
            };

            class AbstractArgument
            {
            public:

                AbstractArgument(string name, ArgumentType type);
                auto operator==(const AbstractArgument &other) const -> bool;
                auto operator!=(const AbstractArgument &other) const -> bool;

                [[nodiscard]] auto Name() const -> string;
                [[nodiscard]] auto Type() const -> ArgumentType;
            private:
                string name_;
                string value_;
                ArgumentType type_;
            };

        } // namespace impl

        using impl::AbstractArgument;
        using impl::ArgumentType;
    } // namespace lib
} // namespace argskata

#endif