#ifndef SCHEMA_H
#define SCHEMA_H

#include "include/ISchema.hpp"
#include "iostream"

namespace args {
namespace libs {
using std::string;

class Schema : public ISchema {
 public:
  explicit Schema(const string& schema);
  auto partOfSchema(const string& param) -> bool override;
  auto parseSchema() -> unordered_map<string, string> override;
};

}  // namespace libs
}  // namespace args

#endif  //!SCHEMA_H