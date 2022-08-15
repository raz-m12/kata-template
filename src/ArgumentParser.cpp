#include "include/ArgumentParser.hpp"

#include <stdexcept>

#include "include/ISchema.hpp"
#include "include/Schema.hpp"

namespace args {
namespace libs {
using std::invalid_argument;
using std::make_shared;

auto ArgumentParser::getParserGivenSchema(const string& input)
    -> ArgumentParser {
  shared_ptr<ISchema> schema = make_shared<Schema>(input);
  return ArgumentParser{schema};
}

ArgumentParser::ArgumentParser(shared_ptr<ISchema> schema)
    : _schema{move(schema)} {
  keyValuePairs_ = _schema->parseSchema();
}

auto ArgumentParser::getSchema() -> shared_ptr<ISchema> { return _schema; }

auto ArgumentParser::getBooleanValue(const string& arg) -> bool {
  if (!_schema->partOfSchema(arg)) {
    throw invalid_argument("argument not part of schema");
  }
  return boolPresentAsCmdLineArg(arg);
}

auto ArgumentParser::boolPresentAsCmdLineArg(const string& arg) -> bool {
  return keyValuePairs_.contains(arg);
}

/** TODO(RV) will be transformed in a template */
auto ArgumentParser::setBooleanValue(const string& arg) -> void {
  keyValuePairs_[arg] = "true";
}

}  // namespace libs
}  // namespace args
