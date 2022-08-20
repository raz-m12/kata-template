#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "any"
#include "utility"

namespace args {
namespace libs {
using std::any;
using std::any_cast;

class IArgument {
 protected:
  virtual auto getValueProected() -> any = 0;

 public:
  virtual ~IArgument() = default;
  IArgument(IArgument const&) = delete;
  IArgument(IArgument&&) = delete;
  auto operator=(IArgument const&) -> IArgument& = delete;
  auto operator=(IArgument &&) -> IArgument& = default;

  template <class T>
  auto getValue() -> T;
};

template <class T>
auto IArgument::getValue() -> T {
  return any_cast<T>(getValueProected());
}

class IntArgument : public IArgument {
 public:
  ~IntArgument() override = default;
  IntArgument(IntArgument const&) = delete;
  IntArgument(IntArgument&&) = delete;
  auto operator=(IntArgument const&) -> IntArgument& = delete;
  auto operator=(IntArgument &&) -> IntArgument& = default;

 protected:
  auto getValueProected() -> any override;

 private:
  int _value = 0;
};


class BoolArgument : public IArgument {
 public:
  ~BoolArgument() override = default;
  BoolArgument(BoolArgument const&) = delete;
  BoolArgument(BoolArgument&&) = delete;
  auto operator=(BoolArgument const&) -> BoolArgument& = delete;
  auto operator=(BoolArgument &&) -> BoolArgument& = default;

 protected:
  auto getValueProected() -> any override;

 private:
  bool _value = false;
};

}  // namespace libs
}  // namespace args

#endif  //! ARGUMENT_H