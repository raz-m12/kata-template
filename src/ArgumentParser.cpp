#include "include/ArgumentParser.hpp"

#include "include/ISchema.hpp"
#include "include/Schema.hpp"

namespace args {
namespace libs {
using std::make_shared;

auto ArgumentParser::getParserGivenSchema(const string& input)
    -> ArgumentParser {
  shared_ptr<ISchema> schema = make_shared<Schema>(input);  // &schema2;
  return ArgumentParser{schema};
}

ArgumentParser::ArgumentParser(shared_ptr<ISchema> schema) : _schema{schema} {}

auto ArgumentParser::getSchema() -> shared_ptr<ISchema> {
  return _schema;
}

auto ArgumentParser::getBooleanValue(const string& arg) -> bool {
  return arg != "f";
}

/** TODO(RV) is being mocked */
auto ArgumentParser::setBooleanValue(const string& arg) -> void {}

}  // namespace libs
}  // namespace args
