#ifndef SCHEMA_H
#define SCHEMA_H

#include "include/ISchema.hpp"
#include "iostream"

namespace args::libs {
using std::string;

class Schema : public ISchema {
 public:
  explicit Schema(const string& schema);
  auto partOfSchema(const string& param) -> bool override;
  auto parseSchema() -> void override;
  auto getKeyValuePairs(const string& values) -> schemaMap override;
};

}  // namespace args::libs

#endif  //! SCHEMA_H