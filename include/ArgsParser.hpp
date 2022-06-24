#ifndef ArgsParser_h
#define ArgsParser_h

#include <iostream>
#include <vector>
#include "include/Argument.hpp"

using namespace std;


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

class EmptySchemaIsNotAllowedException: public exception 
{ };

class SchemaMustStartAndEndWithParenthesisException: public exception
{ };

class ArgsParser 
{
    public:
    ArgsParser(const string& bareSchema, const vector<string>& args);
    bool GetArgValue(const string& argName) const;
    vector<Argument> GetSchema() const;

    private:
    void ParseSchema(const string& bareSchema);
    void PopulateSchemaWithArguments(const string& bareSchema);
    bool SchemaStartsAndEndsWithParenthesis(const string& bareSchema) const;
    vector<Argument> schema_;
};

#endif
