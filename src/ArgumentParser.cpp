#include "include/ArgumentParser.hpp"

#include "include/ISchema.hpp"
#include "include/Schema.hpp"

namespace args {
namespace libs {
auto ArgumentParser::getParserGivenSchema(const string& schema)
    -> ArgumentParser {
  Schema schema2;
  ISchema* ischema = &schema2;  // &schema2;
  return ArgumentParser{ischema};
}

ArgumentParser::ArgumentParser(ISchema* schema) : _schema(schema) {}

auto ArgumentParser::getBooleanValue(const string& arg) -> bool {
  if (arg == "f") {
    return false;
  }

  return true;
}

/** TODO(RV) is being mocked */
auto ArgumentParser::setBooleanValue(const string& arg) -> void {}

}  // namespace libs
}  // namespace args
