#include "sstream"
#include "include/SchemaParser.hpp"
#include "include/Argument.hpp"

void SchemaParser::Parse(const string& bareSchema)
{    
    AssertValidSchemaFormat(bareSchema);
    PopulateSchemaWithArguments(bareSchema);
}

void SchemaParser::AssertValidSchemaFormat(const string& bareSchema)
{
    if(!SchemaStartsAndEndsWithParenthesis(bareSchema))
        throw SchemaMustStartAndEndWithParenthesisException();

    bool emptySchema = bareSchema.length() <= 2;
    if(emptySchema)
        throw EmptySchemaIsNotAllowedException();
}


bool SchemaParser::SchemaStartsAndEndsWithParenthesis(const string& schema) const
{
    return schema.at(0) == '(' && schema.at(schema.length() - 1) == ')';
}

void SchemaParser::PopulateSchemaWithArguments(const string& bareSchema)
{
    istringstream ss{bareSchema};
    string token;
    ss.ignore(); // ignore first character '('

    while(getline(ss, token, ','))
    {
        if(IsSchemaLastToken(token)) 
            token.pop_back(); // remove token last character ')'
        
        if(IsBooleanType(token))
        {
            schema_.push_back({ token, boolean });
            continue;
        }

        if(IsIntegerType(token)) {
            RemoveRedundantChars(token, integer);
            schema_.push_back({ token, integer });
            continue;
        }

        // TODO do a test in which the schema contains invalid characters
    }
}

bool SchemaParser::IsSchemaLastToken(const string& token) const
{
    return token.at(token.length() - 1) == ')';
}

bool SchemaParser::IsBooleanType(const string& token) const
{
    return token.length() == 1;
}

bool SchemaParser::IsIntegerType(const string& token) const
{
    return token.length() == 2 && token.at(1) == '#';
}

void SchemaParser::RemoveRedundantChars(string& token, ArgumentType tokenType)
{
    // nothing to remove when token is a boolean

    if(tokenType == integer)
        token.pop_back();
}

vector<Argument> SchemaParser::GetSchema() const
{
    return schema_;
}