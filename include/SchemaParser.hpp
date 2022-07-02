#ifndef SCHEMAPARSER_HPP
#define SCHEMAPARSER_HPP

#include "iostream"
#include "vector"
#include "unordered_map"
#include "include/Argument.hpp"

namespace argskata
{
    namespace lib
    {
        namespace impl
        {
            using namespace std;

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
                [[nodiscard]] auto GetSchema() const -> unordered_map<string, Argument>;

            private:
                unordered_map<string, Argument> schema_;

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
                auto ArgumentIsValid(const std::string& /*arg*/) const                  -> bool;

            };
        } // namespace impl
        using impl::SchemaMustStartAndEndWithParenthesisException;
        using impl::SchemaInvalidCharacterDetectedException;
        using impl::ArgumentNotPartOfTheSchemaException;
        using impl::SchemaParser;
    } // namespace lib
} // namespace argskata

#endif