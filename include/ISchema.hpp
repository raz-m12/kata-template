#ifndef ISCHEMA_H
#define ISCHEMA_H

#include <iostream>

namespace args {
namespace libs {

using std::string;

class ISchema {
 public:
  ISchema() = default;
  virtual ~ISchema() = default;

  ISchema(ISchema const &) = delete;;
  ISchema(ISchema &&) = delete;
  auto operator=(ISchema const &) -> ISchema & = delete;
  auto operator=(ISchema &&) -> ISchema & = delete;

  virtual auto partOfSchema(const string& param) -> bool = 0;
};

}  // namespace libs
}  // namespace args

#endif  //!__ISCHEMA__H__