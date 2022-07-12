#include "sstream"
#include "algorithm"
#include "include/Argument.hpp"
#include "include/SchemaParser.hpp"


namespace argskata
{
    namespace lib
    {
        auto SchemaParser::Parse(const string &bareSchema, const vector<string> &args) -> void
        {
            // TODO(RV) store the arguments in class variables
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
                throw ArgumentNotPartOfSchemaException();
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

            #pragma unroll 1
            while (getline(iss, token, ','))
            {
                if (IsSchemaLastToken(token))
                {
                    token.pop_back(); // remove token last character ')'
                }

                if (IsBooleanType(token))
                {
                    schema_.insert(make_pair(token, make_shared<BooleanArgument>(token)));
                    continue;
                }

                if (IsIntegerType(token))
                {
                    StripChars(token, _integer);
                    schema_.insert(make_pair(token, make_shared<IntegerArgument>(token)));
                    continue;
                }

                if (IsStringType(token))
                {
                    StripChars(token, _string);
                    schema_.insert(make_pair(token, make_shared<StringArgument>(token)));
                    continue;
                }

                if (IsDoubleType(token))
                {
                    StripChars(token, _double);
                    schema_.insert(make_pair(token, make_shared<DoubleArgument>(token)));
                    continue;
                }

                if (IsStringArrayType(token))
                {
                    // TODO(RV) change name
                    StripChars(token, _strArr);
                    schema_.insert(make_pair(token, make_shared<BooleanArgument>(token)));
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

        void SchemaParser::StripChars(string &token, ArgumentType tokenType)
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
                throw invalid_argument("Unhandled token type");
            }
        }

        auto SchemaParser::PopulateArgumentsWithValues(const vector<string> &args) -> void
        {
            auto cleanArgs = StripNonAlphaChars(args);
            size_t curParsePos = 0;

            #pragma unroll 1
            while(curParsePos < args.size())
            {
                auto arg = GetAbstractArg(cleanArgs[curParsePos++]);
                if(arg->Type() == ArgumentType::_boolean) 
                {
                    arg->SetValue({});
                } else 
                {
                    if(curParsePos == args.size()) 
                    {
                        throw MissingArgumentValueException();
                    }

                    arg->SetValue(cleanArgs[curParsePos++]);
                }
            }
        }

        auto SchemaParser::StripNonAlphaChars(const vector<string>& args) -> vector<string>
        {
            vector<string> result;
            std::for_each(args.begin(), args.end(), [&result](string arg) { // modify in-place
                if(arg.starts_with('-')) {
                    arg.erase(remove_if(begin(arg), end(arg), [](char _char){
                        return isalpha(_char) == 0;
                    }), arg.end());
                }
                
                result.emplace_back(arg);
            });
            return result;
        }

        auto SchemaParser::GetAbstractArg(const string & argName) -> shared_ptr<AbstractArgument>&
        {
            auto _it = schema_.find(argName);

            if(_it == schema_.end()) {
                throw ArgumentNotPartOfSchemaException();
            }

            return (*_it).second;
        }

        auto SchemaParser::GetSchema() const -> unordered_map<string, shared_ptr<AbstractArgument>>
        {
            return schema_;
        }

        auto SchemaParser::GetBooleanArgument(const string& argName) const -> bool 
        {
            return BooleanArgument::Value(schema_.at(argName));
        }

        auto SchemaParser::GetIntegerArgument(const string& argName) const -> int 
        {
            return IntegerArgument::Value(schema_.at(argName));
        }

        auto SchemaParser::GetStringArgument(const string& argName) const -> string
        {
            return StringArgument::Value(schema_.at(argName));
        }

        auto SchemaParser::GetDoubleArgument(const string& argName) const -> double
        {
            return DoubleArgument::Value(schema_.at(argName));
        }

        auto SchemaParser::GetStringArrayArgument(const string& argName) const -> vector<string>
        {
            return StringArrayArgument::Value(schema_.at(argName));
        }
  
    } // namespace lib
} // namespace argskata