#include "include/ArgsParser.hpp"



ArgsParser::ArgsParser(const string& schema, const vector<string>& args) 
{
    schemaParser_.Parse(schema);
}

bool ArgsParser::GetArgValue(const string& argName) const
{
    return true;
}

vector<Argument> ArgsParser::GetSchema() const
{
    return schemaParser_.GetSchema();
}
