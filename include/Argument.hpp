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

            class ArgumentHasher;

            class Argument
            {
            public:
                friend ArgumentHasher;

                Argument(string name, ArgumentType type);
                auto operator==(const Argument &other) const -> bool;
                auto operator!=(const Argument &other) const -> bool;

                [[nodiscard]] auto name() const -> string;
                [[nodiscard]] auto type() const -> ArgumentType;
            private:
                string name_;
                ArgumentType type_;
            };

            class ArgumentHasher
            {
                public:
                auto operator()(const Argument &arg) const -> size_t;
            };
        } // namespace impl

        using impl::Argument;
        using impl::ArgumentHasher;
        using impl::ArgumentType;
    } // namespace lib
} // namespace argskata

#endif