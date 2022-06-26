#include "gmock/gmock.h"
#include "include/ArgsParser.hpp"

using namespace argskata::lib;
using namespace ::testing;
using namespace std;

// ============================================================
// ======================== Back log ==========================
// 1. Feeds parser with empty schema and throws exception
// 2. Parses one argument based on a schema with support for
//    one boolean
// 3. Throws exception when given argument not defined in the
//    schema
// 4. Gives as input arguments that do not adhere to the schema
//    which throws an exception
// [DOING] Adds schema support for: boolean, string, integer,
//    double, arrays

// Tests:
// - BooleanFlagDefaultsToFalseWhenNotInArgumentList
// ============================================================
namespace argskata_test
{
    class SchemaValidationFixture : public testing::Test
    {
    public:
        static const vector<string> EmptyArgs;
    };
    const vector<string> SchemaValidationFixture::EmptyArgs = {};

    TEST_F(SchemaValidationFixture, ThrowsWhenGivenEmptySchema)
    {
        // TODO(RV) pass as argument "()"
        ASSERT_THROW(ArgsParser parser("()", EmptyArgs), EmptySchemaIsNotAllowedException);
    }

    TEST_F(SchemaValidationFixture, ThrowsWhenSchemaDoesNotStartWithOpenParanthesis)
    {
        ASSERT_THROW(ArgsParser parser("f)", EmptyArgs), SchemaMustStartAndEndWithParenthesisException);
    }

    TEST_F(SchemaValidationFixture, ThrowsWhenSchemaDoesNotEndWithCloseParanthesis)
    {
        ASSERT_THROW(ArgsParser parser("(f", EmptyArgs), SchemaMustStartAndEndWithParenthesisException);
    }

    TEST_F(SchemaValidationFixture, VerifiesResultingSchemaParsedBooleanArguments)
    {
        const string schema{"(f,d)"};
        ArgsParser parser{schema, EmptyArgs};

        ASSERT_THAT(parser.GetSchema(), ElementsAre(
                                            Argument{"f", ArgumentType::_boolean},
                                            Argument{"d", ArgumentType::_boolean}));
    }

    TEST_F(SchemaValidationFixture, VerifiesResultingSchemaParsedIntegerArguments)
    {
        const string schema{"(i#,o#)"};
        ArgsParser parser(schema, EmptyArgs);

        ASSERT_THAT(parser.GetSchema(), ElementsAre(
                                            Argument{"i", ArgumentType::_integer},
                                            Argument{"o", ArgumentType::_integer}));
    }

    TEST_F(SchemaValidationFixture, VerifiesResultingSchemaParsesStringArguments)
    {
        const string schema{"(i*,o*)"};
        ArgsParser parser(schema, EmptyArgs);

        ASSERT_THAT(parser.GetSchema(), ElementsAre(
                                            Argument{"i", ArgumentType::_string},
                                            Argument{"o", ArgumentType::_string}));
    }

    // TODO(RV) Add fixture that describes the argument list tests
    //          Possibly add a parameterized test where needed
    TEST(ArgsParser, BooleanFlagDefaultsToTrueIfInArgumentList)
    {
        ArgsParser parser{"(f)", {"-f"}};
        ASSERT_TRUE(parser.GetArgValue("f"));
    }

    TEST(ArgsParser, DISABLED_BooleanFlagDefaultsToFalseIfNotInArgumentList)
    {
        ArgsParser parser{"f", {}};
        auto value = ArgsParser::GetArgValue("f");

        ASSERT_FALSE(value);
    }

} // namespace argskata_test