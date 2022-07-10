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

        auto ArgsParser::GetBooleanArgument(const string & argName) -> bool
        {
            return schemaParser_.GetBooleanArgument(argName);
        }

        auto ArgsParser::GetSchema() const -> unordered_map<string, shared_ptr<AbstractArgument>>
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
