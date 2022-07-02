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

            enum ArgumentType
            {
                _boolean,
                _string,
                _integer,
                _double,
                _strArr
            };

            class Argument
            {
            public:

                Argument(string name, ArgumentType type);
                auto operator==(const Argument &other) const -> bool;
                auto operator!=(const Argument &other) const -> bool;

            private:
                string name_;
                ArgumentType type_;
            };
        } // namespace impl
        using impl::Argument;
        using impl::ArgumentType;
    } // namespace lib
} // namespace argskata

#endif