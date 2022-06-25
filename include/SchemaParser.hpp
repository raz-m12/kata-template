#ifndef SchemaParser_hpp
#define SchemaParser_hpp

#include "iostream"
#include "vector"
#include "include/Argument.hpp"

using namespace std;

class EmptySchemaIsNotAllowedException: public exception 
{ };

class SchemaMustStartAndEndWithParenthesisException: public exception
{ };

class SchemaParser
{
    public:
    void Parse(const string& bareSchema);
    vector<Argument> GetSchema() const;

    private:
    vector<Argument> schema_;

    void AssertValidSchemaFormat(const string& bareSchema);
    bool SchemaStartsAndEndsWithParenthesis(const string& schema) const;

    void PopulateSchemaWithArguments(const string& schema);
    bool IsSchemaLastToken(const string& token) const;
    bool IsBooleanType(const string& token) const;
    bool IsIntegerType(const string& token) const;
    bool IsStringType(const string& token) const;
    void RemoveRedundantChars(string& token, ArgumentType tokenType);
};


#endif