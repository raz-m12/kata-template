#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <string>
#include <vector>

#include "any"
#include "utility"


/* Schema structure
 * DONE f - boolean
 * DONE d# - integer
 * DONE d## - double
 * DONE s* - string
 * s[*] - string array
 */


namespace args::libs {
using std::any;
using std::any_cast;
using std::string;
using std::vector;

class IArgument {
 protected:
  virtual auto getValueProected() -> any = 0;

 public:
  IArgument() = default;
  virtual ~IArgument() = default;
  IArgument(IArgument const&) = delete;
  IArgument(IArgument&&) = delete;
  auto operator=(IArgument const&) -> IArgument& = delete;
  auto operator=(IArgument&&) -> IArgument& = default;

  template <class T>
  auto getValue() -> T;
};

template <class T>
auto IArgument::getValue() -> T {
  return any_cast<T>(getValueProected());
}

class IntArgument : public IArgument {
 public:
  explicit IntArgument(int value);
  ~IntArgument() override = default;
  IntArgument(IntArgument const&) = delete;
  IntArgument(IntArgument&&) = delete;
  auto operator=(IntArgument const&) -> IntArgument& = delete;
  auto operator=(IntArgument&&) -> IntArgument& = default;

 protected:
  auto getValueProected() -> any override;

 private:
  int _value = 0;
};

class BoolArgument : public IArgument {
 public:
  explicit BoolArgument(bool value);
  ~BoolArgument() override = default;
  BoolArgument(BoolArgument const&) = delete;
  BoolArgument(BoolArgument&&) = delete;
  auto operator=(BoolArgument const&) -> BoolArgument& = delete;
  auto operator=(BoolArgument&&) -> BoolArgument& = default;

 protected:
  auto getValueProected() -> any override;

 private:
  bool _value = false;
};

class StringArgument : public IArgument {
 public:
  explicit StringArgument(string value);
  ~StringArgument() override = default;
  StringArgument(StringArgument const&) = delete;
  StringArgument(StringArgument&&) = delete;
  auto operator=(StringArgument const&) -> StringArgument& = delete;
  auto operator=(StringArgument&&) -> StringArgument& = default;

 protected:
  auto getValueProected() -> any override;

 private:
  string _value;
};

class StringArrayArgument : public IArgument {
 public:
  explicit StringArrayArgument(const vector<string>& value);
  ~StringArrayArgument() override = default;
  StringArrayArgument(StringArrayArgument const&) = delete;
  StringArrayArgument(StringArrayArgument&&) = delete;
  auto operator=(StringArrayArgument const&) -> StringArrayArgument& = delete;
  auto operator=(StringArrayArgument&&) -> StringArrayArgument& = default;

 protected:
  auto getValueProected() -> any override;

 private:
  vector<string> _value;
};

class DoubleArgument : public IArgument {
 public:
  explicit DoubleArgument(double value);
  ~DoubleArgument() override = default;
  DoubleArgument(DoubleArgument const&) = delete;
  DoubleArgument(DoubleArgument&&) = delete;
  auto operator=(DoubleArgument const&) -> DoubleArgument& = delete;
  auto operator=(DoubleArgument&&) -> DoubleArgument& = default;

 protected:
  auto getValueProected() -> any override;

 private:
  double _value;
};

}  // namespace args::libs

#endif  //! ARGUMENT_H