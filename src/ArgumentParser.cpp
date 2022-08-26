#include "include/ArgumentParser.hpp"

#include <stdexcept>

#include "include/ISchema.hpp"
#include "include/Schema.hpp"

namespace args::libs {
using std::make_shared;

auto ArgumentParser::getParserGivenSchema(const string& input)
    -> ArgumentParser {
  shared_ptr<ISchema> schema = make_shared<Schema>(input);
  return ArgumentParser{schema};
}

ArgumentParser::ArgumentParser(shared_ptr<ISchema> schema)
    : _schema{move(schema)} {
  _schema->parseSchema();
}

auto ArgumentParser::parseArguments(const string & argValues) -> void {
  keyValuePairs_ = _schema->getKeyValuePairs(argValues);
}

auto ArgumentParser::getSchema() -> shared_ptr<ISchema> { return _schema; }

/** TODO(RV). Idea: will be transformed in a template */
auto ArgumentParser::setBooleanValue(const string & /* arg */) -> void {}

}  // namespace args::libs
