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
            schema_.push_back({ token, _boolean });
            continue;
        }

        if(IsIntegerType(token)) 
        {
            RemoveRedundantChars(token, _integer);
            schema_.push_back({ token, _integer });
            continue;
        }

        if(IsStringType(token))
        {
            RemoveRedundantChars(token, _string);
            schema_.push_back({ token, _string });
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

bool SchemaParser::IsStringType(const string& token) const
{
    return token.length() == 2 && token.at(1) == '*';
}

void SchemaParser::RemoveRedundantChars(string& token, ArgumentType tokenType)
{

    switch(tokenType)
    {
        case _boolean:
            // nothing to remove when token is a boolean
            break;

        case _integer:
        case _string:
            token.pop_back();
            break;

        default:
            throw std::invalid_argument("Unhandled token type");
    }
}

vector<Argument> SchemaParser::GetSchema() const
{
    return schema_;
}