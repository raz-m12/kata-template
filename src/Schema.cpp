#include "include/Schema.hpp"

namespace args::libs {

Schema::Schema(const string& schema) : ISchema(schema) {}

auto Schema::partOfSchema(const string & /*param*/) -> bool {
  // TODO(RV)
  return false;
}

auto Schema::parseSchema() -> schemaMap {
  // TODO(RV)
  return {};
}

}  // namespace args::libs
