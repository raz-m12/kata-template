#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include "iostream"
#include "memory"
#include "vector"
               
// TODO(RV) refactor format document
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
            using std::runtime_error;
            using std::vector;


            class InvalidArgumentValueException : public runtime_error
            {
                public:
                explicit InvalidArgumentValueException(const string& msg): runtime_error(msg) { }
            };

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

                explicit AbstractArgument(string name);
                virtual ~AbstractArgument() = default;
                AbstractArgument(AbstractArgument const&) = default;
                AbstractArgument(AbstractArgument&&) = delete;
                auto operator=(AbstractArgument const&) -> AbstractArgument& = default;
                auto operator=(AbstractArgument&&) -> AbstractArgument& = delete;
                
                auto operator==(const AbstractArgument &other) const -> bool;
                auto operator!=(const AbstractArgument &other) const -> bool;

                [[nodiscard]] auto Name() const -> string;
                // TODO(RV) Refactor: make string constant
                virtual auto SetValue(string argValue) -> void = 0;
                virtual auto Type() -> ArgumentType = 0;

            private:
                string name_;
            };

            class BooleanArgument: public AbstractArgument
            {
                public:
                explicit BooleanArgument(const string& name): AbstractArgument{name} { }
                ~BooleanArgument() override = default;
                BooleanArgument(BooleanArgument const&) = default;
                BooleanArgument(BooleanArgument&&) = delete;
                auto operator=(BooleanArgument const&) -> BooleanArgument& = default;
                auto operator=(BooleanArgument&&) -> BooleanArgument& = delete;

                auto SetValue(string argValue) -> void override;
                static auto Value(const shared_ptr<AbstractArgument>& arg) -> bool;
                auto Type() -> ArgumentType override;

                private:
                bool value_ = false;
            };

            class IntegerArgument: public AbstractArgument
            {
                public:
                explicit IntegerArgument(const string& name): AbstractArgument{name} { }
                ~IntegerArgument() override = default;
                IntegerArgument(IntegerArgument const&) = default;
                IntegerArgument(IntegerArgument&&) = delete;
                auto operator=(IntegerArgument const&) -> IntegerArgument& = default;
                auto operator=(IntegerArgument&&) -> IntegerArgument& = delete;

                auto SetValue(string argValue) -> void override;
                static auto Value(const shared_ptr<AbstractArgument>& arg) -> int;
                auto Type() -> ArgumentType override;

                private:
                int value_ = 0;
            };

            class StringArgument: public AbstractArgument
            {
                public:
                explicit StringArgument(const string& name): AbstractArgument{name} { }
                ~StringArgument() override = default;
                StringArgument(StringArgument const&) = default;
                StringArgument(StringArgument&&) = delete;
                auto operator=(StringArgument const&) -> StringArgument& = default;
                auto operator=(StringArgument&&) -> StringArgument& = delete;

                auto SetValue(string argValue) -> void override;
                static auto Value(const shared_ptr<AbstractArgument>& arg) -> string;
                auto Type() -> ArgumentType override;

                private:
                // TODO(RV)
                //const static string DEFAULT_STRING_VALUE{""};
                string value_;
            };

            class DoubleArgument: public AbstractArgument
            {
                public:
                explicit DoubleArgument(const string& name): AbstractArgument{name} { }
                ~DoubleArgument() override = default;
                DoubleArgument(DoubleArgument const&) = default;
                DoubleArgument(DoubleArgument&&) = delete;
                auto operator=(DoubleArgument const&) -> DoubleArgument& = default;
                auto operator=(DoubleArgument&&) -> DoubleArgument& = delete;

                auto SetValue(string argValue) -> void override;
                static auto Value(const shared_ptr<AbstractArgument>& arg) -> double;
                auto Type() -> ArgumentType override;

                private:
                double value_ = 0;
            };

            class StringArrayArgument: public AbstractArgument
            {
                public:
                explicit StringArrayArgument(const string& name): AbstractArgument{name} { }
                ~StringArrayArgument() override = default;
                StringArrayArgument(StringArrayArgument const&) = default;
                StringArrayArgument(StringArrayArgument&&) = delete;
                auto operator=(StringArrayArgument const&) -> StringArrayArgument& = default;
                auto operator=(StringArrayArgument&&) -> StringArrayArgument& = delete;

                auto SetValue(string argValue) -> void override;
                static auto Value(const shared_ptr<AbstractArgument>& arg) -> vector<string>;
                auto Type() -> ArgumentType override;

                private:
                vector<string> value_{};
            };

        } // namespace impl
        using impl::InvalidArgumentValueException;
        using impl::BooleanArgument;
        using impl::IntegerArgument;
        using impl::DoubleArgument;
        using impl::StringArgument;
        using impl::StringArrayArgument;
        using impl::ArgumentType;
        using impl::AbstractArgument;
    } // namespace lib
} // namespace argskata

#endif