#include "include/ArgsParser.hpp"
#include "sstream"


Argument::Argument(const string& name): name_{name}
{ }

bool Argument::operator==(const Argument& other) const
{
    return name_ == other.name_;
}

ArgsParser::ArgsParser(const string& bareSchema, const vector<string>& args) 
{
    if(bareSchema.empty())
        throw EmptySchemaIsNotAllowedException();
    
    ParseSchema(bareSchema);
}

void ArgsParser::ParseSchema(const string& bareSchema)
{
    if(bareSchema.at(0) != '(' || bareSchema.at(bareSchema.length() - 1) != ')')
        throw SchemaMustStartAndEndWithParenthesisException();
}

bool ArgsParser::GetArgValue(const string& argName) const
{
    return true;
}

vector<Argument> ArgsParser::GetSchema() const
{
    return schema_;
}
