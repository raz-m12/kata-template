#include "gmock/gmock.h"
#include "include/ArgsParser.hpp"

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
// 5. Adds schema support for: boolean, string, integer, double
//    arrays

// Tests:
// - VerifiesResultingSchemaParsedBooleanArguments
// - BooleanFlagDefaultsToFalseWhenNotInArgumentList
// ============================================================

class AnArgsParser: public testing::Test {
public:
    static const string DefaultSchema;
    static const vector<string> EmptyArgs;
};
const string AnArgsParser::DefaultSchema = "(f)";
const vector<string> AnArgsParser::EmptyArgs = {};

TEST_F(AnArgsParser, ThrowsWhenGivenEmptySchema)
{
    // TODO pass as argument "()"
    ASSERT_THROW(ArgsParser parser("()", EmptyArgs), EmptySchemaIsNotAllowedException);
}

TEST_F(AnArgsParser, ThrowsWhenSchemaDoesNotStartWithOpenParanthesis)
{
    ASSERT_THROW(ArgsParser parser("f)", EmptyArgs), SchemaMustStartAndEndWithParenthesisException);
}

TEST_F(AnArgsParser, ThrowsWhenSchemaDoesNotEndWithCloseParanthesis)
{
    ASSERT_THROW(ArgsParser parser("(f", EmptyArgs), SchemaMustStartAndEndWithParenthesisException);
}

TEST_F(AnArgsParser, VerifiesResultingSchemaParsedBooleanArguments)
{
    const string schema{"(f,d)"};
    ArgsParser parser{schema, EmptyArgs};

    ASSERT_THAT(parser.GetSchema(), ElementsAre(
        Argument{"f", boolean}, Argument{"d", boolean}
    ));
}

TEST_F(AnArgsParser, VerifiesResultingSchemaParsedIntegerArguments)
{
    const string schema{"(i#,o#)"};
    ArgsParser parser(schema, EmptyArgs);

    ASSERT_THAT(parser.GetSchema(), ElementsAre(
        Argument{"i", integer},
        Argument{"o", integer}
    ));
}

TEST(ArgsParser, BooleanFlagDefaultsToTrueIfInArgumentList)
{
    ArgsParser parser{"(f)", {"-f"}};
    ASSERT_TRUE(parser.GetArgValue("f"));
}


TEST(ArgsParser, DISABLED_BooleanFlagDefaultsToFalseIfNotInArgumentList)
{
    ArgsParser parser{"f", {}};
    auto value = parser.GetArgValue("f");

    ASSERT_FALSE(value);
}
