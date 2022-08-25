#ifndef ISCHEMA_H
#define ISCHEMA_H

#include <iostream>

#include "include/Argument.hpp"
#include "memory"
#include "unordered_map"

namespace args::libs {

using std::move;
using std::string;
using std::unique_ptr;
using std::unordered_map;
// TODO(RV) to change to an unique pointer
using schemaMap = unordered_map<string, unique_ptr<IArgument>>;

class ISchema {
 public:
  explicit ISchema(string schema) : _schema(move(schema)){};
  virtual ~ISchema() = default;

  ISchema() = delete;
  ISchema(ISchema const &) = delete;
  ISchema(ISchema &&) = delete;
  auto operator=(ISchema const &) -> ISchema & = delete;
  auto operator=(ISchema &&) -> ISchema & = delete;

  virtual auto parseSchema() -> schemaMap = 0;
  virtual auto partOfSchema(const string &param) -> bool = 0;

 private:
  string _schema;
};

}  // namespace args::libs

#endif  //! ISCHEMA_H