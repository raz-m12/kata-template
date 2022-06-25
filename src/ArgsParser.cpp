#include "include/ArgsParser.hpp"

using namespace argskata::lib;
using namespace std;

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
