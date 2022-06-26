#ifndef SCHEMAPARSER_HPP
#define SCHEMAPARSER_HPP

#include "iostream"
#include "vector"
#include "include/Argument.hpp"

namespace argskata
{
    namespace lib
    {
        namespace impl
        {
            using namespace std;

            class EmptySchemaIsNotAllowedException : public exception
            {
            };

            class SchemaMustStartAndEndWithParenthesisException : public exception
            {
            };

            class SchemaParser
            {
            public:
                void Parse(const string &bareSchema);
                [[nodiscard]] auto GetSchema() const -> vector<Argument>;

            private:
                vector<Argument> schema_;

                static void AssertValidSchemaFormat(const string &bareSchema);
                [[nodiscard]] static auto SchemaStartsAndEndsWithParenthesis(const string &schema) -> bool;

                void PopulateSchemaWithArguments(const string &schema);
                [[nodiscard]] static auto IsSchemaLastToken(const string &token) -> bool;
                [[nodiscard]] static auto IsBooleanType(const string &token) -> bool;
                [[nodiscard]] static auto IsIntegerType(const string &token) -> bool;
                [[nodiscard]] static auto IsStringType(const string &token) -> bool;
                static void RemoveRedundantChars(string &token, ArgumentType tokenType);
            };
        } // namespace impl
        using impl::EmptySchemaIsNotAllowedException;
        using impl::SchemaMustStartAndEndWithParenthesisException;
        using impl::SchemaParser;
    } // namespace lib
} // namespace argskata

#endif