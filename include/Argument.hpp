#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include "iostream"
#include "memory"

namespace argskata
{
    namespace lib
    {
        namespace impl
        {
            using std::string;
            using std::size_t;
            using std::dynamic_pointer_cast;
            using std::shared_ptr;

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
                virtual ~AbstractArgument() = default;
                AbstractArgument(AbstractArgument const&) = default;
                AbstractArgument(AbstractArgument&&) = delete;
                auto operator=(AbstractArgument const&) -> AbstractArgument& = default;
                auto operator=(AbstractArgument&&) -> AbstractArgument& = delete;
                
                auto operator==(const AbstractArgument &other) const -> bool;
                auto operator!=(const AbstractArgument &other) const -> bool;

                [[nodiscard]] auto Name() const -> string;
                [[nodiscard]] virtual auto Type() const -> ArgumentType;
                virtual auto SetValue(string argValue) -> void = 0;

            private:
                string name_;
                string value_;
                ArgumentType type_;
            };

            class BooleanArgument: public AbstractArgument
            {
                public:
                BooleanArgument(const string& name, const ArgumentType& type): AbstractArgument{name, type} { }
                ~BooleanArgument() = default;
                BooleanArgument(BooleanArgument const&) = default;
                BooleanArgument(BooleanArgument&&) = delete;
                auto operator=(BooleanArgument const&) -> BooleanArgument& = default;
                auto operator=(BooleanArgument&&) -> BooleanArgument& = delete;

                // TODO(RV) to move in header file
                auto SetValue(string argValue) -> void override;

                static auto Value(const shared_ptr<AbstractArgument>& arg) -> bool;

                private:
                bool value_ = false;
            };

        } // namespace impl
        using impl::BooleanArgument;
        using impl::AbstractArgument;
        using impl::ArgumentType;
    } // namespace lib
} // namespace argskata

#endif