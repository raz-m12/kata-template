#include "include/Schema.hpp"
#include "include/ISchema.hpp"

namespace args::libs {

Schema::Schema(const string& schema) : ISchema(schema) {}

auto Schema::partOfSchema(const string & /*param*/) -> bool {
  // TODO(RV)
  return false;
}

auto Schema::parseSchema() -> void {
  // TODO(RV)
}

auto Schema::getKeyValuePairs(const string& /* values */) -> schemaMap {
  return {};
}

}  // namespace args::libs
