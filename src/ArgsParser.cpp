#include "include/ArgsParser.hpp"

using argskata::lib::ArgsParser;
using std::string;
using std::unordered_map;

namespace argskata
{
    namespace lib
    {
        ArgsParser::ArgsParser(const string &schema, const vector<string> &args)
        {
            schemaParser_.Parse(schema, args);
        }

        auto ArgsParser::GetArgValue(const string & /*argName*/) -> bool
        {
            return false; //schemaParser_.;
        }

        auto ArgsParser::GetSchema() const -> unordered_map<string, AbstractArgument>
        {
            return schemaParser_.GetSchema();
        }

        auto ArgsParser::MapCmdLineArgsToParserInput(int argc, char *argv[]) -> vector<string>
        {
            std::vector<std::string> parserInput;

            if (argc > 1)
            {
                parserInput.assign(argv + 1, argv + argc);
            }
            return parserInput;
        }
    } // namespace lib
} // namespace argskata
