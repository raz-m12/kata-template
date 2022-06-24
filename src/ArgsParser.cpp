#include "include/ArgsParser.hpp"

ArgsParser::ArgsParser(const string& schema, const vector<string>& args) 
{
    if(schema.empty())
        throw EmptySchemaIsDisallowedException();
}

bool ArgsParser::GetArgValue(const string& argName) const
{
    return false;
}