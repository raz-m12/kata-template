#ifndef ArgsParser_h
#define ArgsParser_h

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

namespace argskata {
   namespace lib {
      namespace impl {
         using namespace std;

         // TODO make as many methods as possible const
         class ArgsParser 
         {
            public:
            ArgsParser(const string& bareSchema, const vector<string>& args);
            bool GetArgValue(const string& argName) const;
            vector<Argument> GetSchema() const;

            private:
            SchemaParser schemaParser_;
         };
      }
      using impl::ArgsParser;
   }
}

#endif
