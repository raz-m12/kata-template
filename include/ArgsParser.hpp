#ifndef ARGSPARSER_HPP
#define ARGSPARSER_HPP

#include <iostream>
#include "include/SchemaParser.hpp"

// ==============================================
// Schema:
//  - char    - Boolean arg.
//  - char*   - String arg.
//  - char#   - Integer arg.
//  - char##  - double arg.
//  - char[*] - one element of a string array.
// Example schema: (f,s*,n#,a##,p[*])
// Corresponding example:
// -f -s Bob -n 1 -a 3.2 -p e1 -p e2 -p e3
// ==============================================

namespace argskata
{
    namespace lib
    {
        namespace impl
        {
            using std::string;

            class ArgsParser
            {
            public:
                ArgsParser(const string &bareSchema, const vector<string> &args);
                
                [[nodiscard]] static auto GetArgValue(const string &argName) -> bool;
                [[nodiscard]] auto GetSchema()                         const -> unordered_map<string, Argument>;
                static auto MapCmdLineArgsToParserInput(int argc, char *argv[]) -> vector<string>;

            private:
                SchemaParser schemaParser_;
            };
        } // namespace impl
        using impl::ArgsParser;
    } // namespace lib
} // namespace argskata

#endif
