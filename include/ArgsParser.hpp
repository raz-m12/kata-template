#ifndef ArgsParser_h
#define ArgsParser_h

#include <iostream>
#include <vector>

using namespace std;


// ==============================================
// Schema:
//  - char    - Boolean arg.
//  - char*   - String arg.
//  - char#   - Integer arg.
//  - char##  - double arg.
//  - char[*] - one element of a string array.
// ==============================================

class EmptySchemaIsDisallowedException: public exception 
{ };

class ArgsParser 
{
    public:
    ArgsParser(const string& schema, const vector<string>& args);
    bool GetArgValue(const string& argName) const;
};

#endif
