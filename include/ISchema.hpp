#ifndef ISCHEMA_H
#define ISCHEMA_H

#include <iostream>

namespace args {
namespace libs {

using std::string;
using std::move;

class ISchema {
 public:
  explicit ISchema(const string& schema): _schema(move(schema)) { };
  virtual ~ISchema() = default;

  ISchema(ISchema const &) = delete;;
  ISchema(ISchema &&) = delete;
  auto operator=(ISchema const &) -> ISchema & = delete;
  auto operator=(ISchema &&) -> ISchema & = delete;

  virtual auto partOfSchema(const string& param) -> bool = 0;

 private:
  ISchema() = default;
  string _schema;
};

}  // namespace libs
}  // namespace args

#endif  //!ISCHEMA_H