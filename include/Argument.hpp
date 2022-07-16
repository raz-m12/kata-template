#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include "iostream"
#include "memory"
#include "vector"

namespace argskata {
namespace lib {
namespace impl {
using std::dynamic_pointer_cast;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

class InvalidArgumentValueException : public runtime_error {
 public:
  explicit InvalidArgumentValueException(const string &msg)
      : runtime_error(msg) {}
};

enum ArgumentType { _boolean, _string, _integer, _double, _strArr };

class AbstractArgument {
 public:
  explicit AbstractArgument(string name);
  virtual ~AbstractArgument() = default;
  AbstractArgument(AbstractArgument const &) = default;
  AbstractArgument(AbstractArgument &&) = delete;
  auto operator=(AbstractArgument const &) -> AbstractArgument & = default;
  auto operator=(AbstractArgument &&) -> AbstractArgument & = delete;

  auto operator==(const AbstractArgument &other) const -> bool;
  auto operator!=(const AbstractArgument &other) const -> bool;

  [[nodiscard]] auto Name() const -> string;
  virtual auto SetValue(const string &argValue) -> void = 0;
  virtual auto Type() -> ArgumentType = 0;

 private:
  string name_;
};

class BooleanArgument : public AbstractArgument {
 public:
  explicit BooleanArgument(const string &name) : AbstractArgument{name} {}
  ~BooleanArgument() override = default;
  BooleanArgument(BooleanArgument const &) = default;
  BooleanArgument(BooleanArgument &&) = delete;
  auto operator=(BooleanArgument const &) -> BooleanArgument & = default;
  auto operator=(BooleanArgument &&) -> BooleanArgument & = delete;

  auto SetValue(const string &argValue) -> void override;
  static auto Value(const shared_ptr<AbstractArgument> &arg) -> bool;
  auto Type() -> ArgumentType override;

 private:
  inline static const bool DEFAULT_VALUE = false;
  bool value_ = BooleanArgument::DEFAULT_VALUE;
};

class IntegerArgument : public AbstractArgument {
 public:
  explicit IntegerArgument(const string &name) : AbstractArgument{name} {}
  ~IntegerArgument() override = default;
  IntegerArgument(IntegerArgument const &) = default;
  IntegerArgument(IntegerArgument &&) = delete;
  auto operator=(IntegerArgument const &) -> IntegerArgument & = default;
  auto operator=(IntegerArgument &&) -> IntegerArgument & = delete;

  auto SetValue(const string &argValue) -> void override;
  static auto Value(const shared_ptr<AbstractArgument> &arg) -> int;
  auto Type() -> ArgumentType override;

 private:
  inline static const int DEFAULT_VALUE{0};
  int value_ = IntegerArgument::DEFAULT_VALUE;
};

class StringArgument : public AbstractArgument {
 public:
  explicit StringArgument(const string &name) : AbstractArgument{name} {}
  ~StringArgument() override = default;
  StringArgument(StringArgument const &) = default;
  StringArgument(StringArgument &&) = delete;
  auto operator=(StringArgument const &) -> StringArgument & = default;
  auto operator=(StringArgument &&) -> StringArgument & = delete;

  auto SetValue(const string &argValue) -> void override;
  static auto Value(const shared_ptr<AbstractArgument> &arg) -> string;
  auto Type() -> ArgumentType override;

 private:
  inline static const string DEFAULT_VALUE = std::string();
  string value_ = StringArgument::DEFAULT_VALUE;
};

class DoubleArgument : public AbstractArgument {
 public:
  explicit DoubleArgument(const string &name) : AbstractArgument{name} {}
  ~DoubleArgument() override = default;
  DoubleArgument(DoubleArgument const &) = default;
  DoubleArgument(DoubleArgument &&) = delete;
  auto operator=(DoubleArgument const &) -> DoubleArgument & = default;
  auto operator=(DoubleArgument &&) -> DoubleArgument & = delete;

  auto SetValue(const string &argValue) -> void override;
  static auto Value(const shared_ptr<AbstractArgument> &arg) -> double;
  auto Type() -> ArgumentType override;

 private:
  inline static const double DEFAULT_VALUE{0.0};
  double value_ = DoubleArgument::DEFAULT_VALUE;
};

class StringArrayArgument : public AbstractArgument {
 public:
  explicit StringArrayArgument(const string &name) : AbstractArgument{name} {}
  ~StringArrayArgument() override = default;
  StringArrayArgument(StringArrayArgument const &) = default;
  StringArrayArgument(StringArrayArgument &&) = delete;
  auto operator=(StringArrayArgument const &)
      -> StringArrayArgument & = default;
  auto operator=(StringArrayArgument &&) -> StringArrayArgument & = delete;

  auto SetValue(const string &argValue) -> void override;
  static auto Value(const shared_ptr<AbstractArgument> &arg) -> vector<string>;
  auto Type() -> ArgumentType override;

 private:
  inline static const vector<string> DEFAULT_VALUE{};
  vector<string> value_ = StringArrayArgument::DEFAULT_VALUE;
};

}  // namespace impl
using impl::AbstractArgument;
using impl::ArgumentType;
using impl::BooleanArgument;
using impl::DoubleArgument;
using impl::IntegerArgument;
using impl::InvalidArgumentValueException;
using impl::StringArgument;
using impl::StringArrayArgument;
}  // namespace lib
}  // namespace argskata

#endif