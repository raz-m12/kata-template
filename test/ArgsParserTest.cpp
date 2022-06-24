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


TEST(ArgsParser, ThrowsExceptionWhenGivenEmptySchema)
{
    ASSERT_THROW(ArgsParser parser("", {}), EmptySchemaIsDisallowedException);
}

TEST(ArgsParser, BooleanFlagDefaultsToTrueIfInArgumentList)
{
    ArgsParser parser{"f", {"-f"}};
    auto value = parser.GetArgValue("f");

    ASSERT_TRUE(value);
}
