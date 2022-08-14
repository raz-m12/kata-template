#ifndef ISCHEMA_H
#define ISCHEMA_H

#include <iostream>
#include "unordered_map"

namespace args {
namespace libs {

using std::move;
using std::string;
using std::unordered_map;
using schemaMap = unordered_map<string, string>;

class ISchema {
 public:
  explicit ISchema(string schema) : _schema(move(schema)){};
  virtual ~ISchema() = default;
  
  ISchema() = delete;
  ISchema(ISchema const &) = delete;
  ISchema(ISchema &&) = delete;
  auto operator=(ISchema const &) -> ISchema & = delete;
  auto operator=(ISchema &&) -> ISchema & = delete;

  virtual auto parseSchema(const string &param) -> schemaMap = 0;
  virtual auto partOfSchema(const string &param) -> bool = 0;

 private:
  string _schema;
};

}  // namespace libs
}  // namespace args

#endif  //! ISCHEMA_H