#include "include/ArgsParser.hpp"

using argskata::lib::ArgsParser;
using std::string;
using std::unordered_map;

namespace argskata
{
    namespace lib
    {
        ArgsParser::ArgsParser(const string &schema, const vector<string>& args)
        {
            schemaParser_.Parse(schema, args);
        }

        auto ArgsParser::GetArgValue(const string & /*argName*/) -> bool
        {
            return true;
        }

        auto ArgsParser::GetSchema() const -> unordered_map<string, Argument>
        {
            return schemaParser_.GetSchema();
        }
    } // namespace lib
} // namespace argskata
