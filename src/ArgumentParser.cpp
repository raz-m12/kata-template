#include "include/ArgumentParser.hpp"

#include <stdexcept>

#include "include/ISchema.hpp"
#include "include/Schema.hpp"

namespace args {
namespace libs {
using std::make_shared;

auto ArgumentParser::getParserGivenSchema(const string& input)
    -> ArgumentParser {
  shared_ptr<ISchema> schema = make_shared<Schema>(input);
  return ArgumentParser{schema};
}

ArgumentParser::ArgumentParser(shared_ptr<ISchema> schema)
    : _schema{move(schema)} {}

auto ArgumentParser::parseSchema() -> void {
  keyValuePairs__ = _schema->parseSchema();
}

auto ArgumentParser::getSchema() -> shared_ptr<ISchema> { return _schema; }

auto ArgumentParser::boolPresentAsCmdLineArg(const string& arg) -> bool {
  return keyValuePairs_.contains(arg) && keyValuePairs_.at(arg) == "true";
}

/** TODO(RV). Idea: will be transformed in a template */
auto ArgumentParser::setBooleanValue(const string& arg) -> void {
  keyValuePairs_[arg] = "true";
}

}  // namespace libs
}  // namespace args
