#include "include/Schema.hpp"

namespace args {
namespace libs {

Schema::Schema(const string& schema) : ISchema(schema) {}

auto Schema::partOfSchema(const string&  /*param*/) -> bool {
  // TODO(RV)
  return false;
}

}  // namespace libs
}  // namespace args
