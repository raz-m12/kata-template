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
        // TODO could refactor to use a SchemaParser class.
        if(token.at(token.length() - 1) == ')') 
            token.pop_back();
        
        if(token.length() == 1) {
            schema_.push_back({ token, boolean });
            continue;
        }

        if(token.length() == 2 && token.at(1) == '#') {
            token.pop_back();
            schema_.push_back({ token, integer });
            continue;
        }
        
        // TODO do a test in which the schema contains invalid characters
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
