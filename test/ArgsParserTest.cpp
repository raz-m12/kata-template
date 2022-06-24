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
// - BooleanFlagDefaultsToFalseWhenNotInArgumentList
// ============================================================

class AnArgsParser: public testing::Test {
public:
    static const string DefaultSchema;
};
const string AnArgsParser::DefaultSchema = "(f)";


TEST(ArgsParser, ThrowsWhenGivenEmptySchema)
{
    ASSERT_THROW(ArgsParser parser("", {}), EmptySchemaIsNotAllowedException);
}

TEST(ArgsParser, ThrowsWhenSchemaDoesNotStartWithOpenParanthesis)
{
    ASSERT_THROW(ArgsParser parser("f)", {}), SchemaMustStartAndEndWithParenthesisException);
}

TEST(ArgsParser, ThrowsWhenSchemaDoesNotEndWithCloseParanthesis)
{
    ASSERT_THROW(ArgsParser parser("(f", {}), SchemaMustStartAndEndWithParenthesisException);
}

TEST(ArgsParser, VerifiesResultingSchemaParsedArguments)
{
    ArgsParser parser{"(f,d)", {}};

    ASSERT_THAT(parser.GetSchema(), ElementsAre(
        Argument{"f", boolean}, Argument{"d", boolean}
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
