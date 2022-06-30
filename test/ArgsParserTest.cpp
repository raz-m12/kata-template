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

    TEST_F(SchemaValidationFixture, VerifiesResultingSchemaParsesDoubleArguments)
    {
        const string schema{"(i##,o##)"};
        ArgsParser parser(schema, EmptyArgs);

        ASSERT_THAT(parser.GetSchema(), ElementsAre(
                                            Argument{"i", ArgumentType::_double},
                                            Argument{"o", ArgumentType::_double}));
    }

    TEST_F(SchemaValidationFixture, VerifiesResultingSchemaParsesStringArrayArguments)
    {
        const string schema{"(i[*],o[*])"};
        ArgsParser parser(schema, EmptyArgs);

        ASSERT_THAT(parser.GetSchema(), ElementsAre(
                                            Argument{"i", ArgumentType::_strArr},
                                            Argument{"o", ArgumentType::_strArr}));
    }

    TEST_F(SchemaValidationFixture, ThrowsOnInvalidSchemaCharacterDetected)
    {
        const string schema{"(fd)"};
        ASSERT_THROW(ArgsParser(schema, EmptyArgs), SchemaInvalidCharacterDetectedException);
    }

    // TODO(RV) Add fixture that describes the argument list tests
    //          Possibly add a parameterized test where needed
    TEST(ArgumentValueValidator, DISABLED_BooleanFlagDefaultsToTrueIfInArgumentList)
    {
        ArgsParser parser{"(f)", {"-f"}};
        ASSERT_TRUE(parser.GetArgValue("f"));
    }

    TEST(ArgumentValueValidator, ThrowsWhenSchemaIsEmptyAndThereAreArguments)
    {
        const string ArgumentNotInSchema{"-x"};

        ASSERT_THROW(ArgsParser parser("()", { ArgumentNotInSchema }), ArgumentNotPartOfTheSchemaException);
    }

    TEST(ArgumentValueValidator, DISABLED_ThrowsWhenArgumentIsNotPartOfSchema)
    {
        
    }

    TEST(ArgumentValueValidator, DISABLED_BooleanFlagDefaultsToFalseIfNotInArgumentList)
    {
        ArgsParser parser{"f", {}};
        auto value = ArgsParser::GetArgValue("f");

        ASSERT_FALSE(value);
    }

} // namespace argskata_test