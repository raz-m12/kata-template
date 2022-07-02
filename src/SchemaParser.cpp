#include "sstream"
#include "include/SchemaParser.hpp"
#include "include/Argument.hpp"

namespace argskata
{
    namespace lib
    {
        using std::make_pair;

        auto SchemaParser::Parse(const string &bareSchema, const vector<string> &args) -> void
        {
            AssertValidSchemaFormat(bareSchema, args);
            PopulateSchemaWithArguments(bareSchema);
            PopulateArgumentsWithValues(args);
        }

        auto SchemaParser::AssertValidSchemaFormat(const string &bareSchema, const vector<string> &args) -> void
        {
            if (!SchemaStartsAndEndsWithParenthesis(bareSchema))
            {
                throw SchemaMustStartAndEndWithParenthesisException();
            }

            if (SchemaIsEmptyAndThereAreArgumentsToParse(bareSchema, args))
            {
                throw ArgumentNotPartOfTheSchemaException();
            }
        }

        auto SchemaParser::SchemaStartsAndEndsWithParenthesis(const string &schema) -> bool
        {
            return schema.at(0) == '(' && schema.at(schema.length() - 1) == ')';
        }

        auto SchemaParser::SchemaIsEmptyAndThereAreArgumentsToParse(const string &schema, const vector<string> &args) -> bool
        {
            return schema.length() == 2 && !args.empty();
        }

        auto SchemaParser::PopulateSchemaWithArguments(const string &bareSchema) -> void
        {
            istringstream iss{bareSchema};
            string token;
            iss.ignore(); // ignore first character '('

#pragma unroll 2
            while (getline(iss, token, ','))
            {
                if (IsSchemaLastToken(token))
                {
                    token.pop_back(); // remove token last character ')'
                }

                if (IsBooleanType(token))
                {
                    schema_.insert(Argument{token, _boolean});
                    continue;
                }

                if (IsIntegerType(token))
                {
                    RemoveRedundantChars(token, _integer);
                    schema_.insert(Argument{token, _integer});
                    continue;
                }

                if (IsStringType(token))
                {
                    RemoveRedundantChars(token, _string);
                    schema_.insert(Argument{token, _string});
                    continue;
                }

                if (IsDoubleType(token))
                {
                    RemoveRedundantChars(token, _double);
                    schema_.insert(Argument{token, _double});
                    continue;
                }

                if (IsStringArrayType(token))
                {
                    RemoveRedundantChars(token, _strArr);
                    schema_.insert(Argument{token, _strArr});
                    continue;
                }

                throw SchemaInvalidCharacterDetectedException();
            }
        }

        auto SchemaParser::IsSchemaLastToken(const string &token) -> bool
        {
            return token.at(token.length() - 1) == ')';
        }

        auto SchemaParser::IsBooleanType(const string &token) -> bool
        {
            return token.length() == 1;
        }

        auto SchemaParser::IsIntegerType(const string &token) -> bool
        {
            return token.length() == 2 && token.at(1) == '#';
        }

        auto SchemaParser::IsStringType(const string &token) -> bool
        {
            return token.length() == 2 && token.at(1) == '*';
        }

        auto SchemaParser::IsDoubleType(const string &token) -> bool
        {
            return token.length() == 3 && token.at(1) == '#' && token.at(2) == '#';
        }

        auto SchemaParser::IsStringArrayType(const string &token) -> bool
        {
            return token.length() == 4 && token.at(1) == '[' && token.at(2) == '*' && token.at(3) == ']';
        }

        void SchemaParser::RemoveRedundantChars(string &token, ArgumentType tokenType)
        {

            switch (tokenType)
            {
            case _boolean:
                // nothing to remove when token is a boolean
                break;

            case _integer:
            case _string:
                token.pop_back();
                break;

            case _double:
                token.pop_back();
                token.pop_back();
                break;

            case _strArr:
                token.pop_back();
                token.pop_back();
                token.pop_back();
                break;

            default:
                throw std::invalid_argument("Unhandled token type");
            }
        }

        auto SchemaParser::PopulateArgumentsWithValues(const std::vector<std::string> &args) -> void
        {
            for (const auto &arg : args)
            {
                if (!ArgumentIsValid(arg))
                {
                    throw ArgumentNotPartOfTheSchemaException();
                }
            }
        }

        auto SchemaParser::ArgumentIsValid(const std::string & /*arg*/) const -> bool
        {
            return false;
        }

        auto SchemaParser::GetSchema() const -> std::unordered_set<Argument, ArgumentHasher>
        {
            return schema_;
        }

  
    } // namespace lib
} // namespace argskata