#include "include/ArgsParser.hpp"
#include "sstream"


ArgsParser::ArgsParser(const string& schema, const vector<string>& args) 
{
    if(schema.empty())
        throw EmptySchemaIsNotAllowedException();
    
    ParseSchema(schema);
}

void ArgsParser::ParseSchema(const string& bareSchema)
{
    if(!SchemaStartsAndEndsWithParenthesis(bareSchema))
        throw SchemaMustStartAndEndWithParenthesisException();

    PopulateSchemaWithArguments(bareSchema);
}

bool ArgsParser::SchemaStartsAndEndsWithParenthesis(const string& schema) const
{
    // TODO use a SchemaFormatter class to clean up these bits
    return schema.at(0) == '(' && schema.at(schema.length() - 1) == ')';
}

void ArgsParser::PopulateSchemaWithArguments(const string& bareSchema)
{
    istringstream ss{bareSchema};
    string token;
    ss.ignore(); // ignores first character, will always be open parenthesis

    while(getline(ss, token, ','))
    {
        if(token.at(token.length() - 1) == ')') // TODO could refactor to use
            token.pop_back();                   // a SchemaFormatter class. This line as well
        schema_.push_back({ token, boolean });           // TODO add argument type enum
        // Add a SchemmaFormatter method that returns the correct type based on the token
    }
}


bool ArgsParser::GetArgValue(const string& argName) const
{
    return true;
}

vector<Argument> ArgsParser::GetSchema() const
{
    return schema_;
}
