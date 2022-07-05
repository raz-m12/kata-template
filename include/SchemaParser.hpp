#ifndef SCHEMAPARSER_HPP
#define SCHEMAPARSER_HPP

#include "iostream"
#include "vector"
#include "unordered_map"
#include "memory"
#include "include/Argument.hpp"

namespace argskata
{
    namespace lib
    {
        namespace impl
        {
            using namespace std;
            using std::shared_ptr;


            class SchemaMustStartAndEndWithParenthesisException : public exception
            {
            };

            class SchemaInvalidCharacterDetectedException : public exception
            {
            };

            class ArgumentNotPartOfTheSchemaException : public exception
            {
            };

            class SchemaParser
            {
            public:
                void Parse(const string &bareSchema, const vector<string>& args);
                [[nodiscard]] auto GetSchema() const -> unordered_map<string, shared_ptr<AbstractArgument>>;
                // TODO(RV) [[nodiscard]] auto GetValue(const string& argName) const -> 

            private:
                unordered_map<string, shared_ptr<AbstractArgument>> schema_;

                static void AssertValidSchemaFormat(const string &bareSchema, const vector<string>& args);
                [[nodiscard]] static auto SchemaStartsAndEndsWithParenthesis(const string &schema) -> bool;
                [[nodiscard]] static auto SchemaIsEmptyAndThereAreArgumentsToParse(const string &schema, const vector<string>& args) -> bool;

                auto PopulateSchemaWithArguments(const string &schema)                  -> void;
                [[nodiscard]] static auto IsSchemaLastToken(const string &token)        -> bool;
                [[nodiscard]] static auto IsBooleanType(const string& token)            -> bool;
                [[nodiscard]] static auto IsIntegerType(const string& token)            -> bool;
                [[nodiscard]] static auto IsStringType(const string& token)             -> bool;
                [[nodiscard]] static auto IsDoubleType(const string& token)             -> bool;
                [[nodiscard]] static auto IsStringArrayType(const string& token)        -> bool;
                static auto RemoveRedundantChars(string &token, ArgumentType tokenType) -> void;

                auto PopulateArgumentsWithValues(const vector<string>& args)            -> void;
                auto ArgumentIsPartOfSchema(const std::string& arg)                     -> bool;
                auto DecideValidArgumentValue(const std::string& arg)                   -> void;
            };
        } // namespace impl
        using impl::SchemaMustStartAndEndWithParenthesisException;
        using impl::SchemaInvalidCharacterDetectedException;
        using impl::ArgumentNotPartOfTheSchemaException;
        using impl::SchemaParser;
    } // namespace lib
} // namespace argskata

#endif