#include "include/ArgsParser.hpp"

using argskata::lib::ArgsParser;
using std::string;

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

        auto ArgsParser::GetSchema() const -> vector<Argument>
        {
            return schemaParser_.GetSchema();
        }
    } // namespace lib
} // namespace argskata
