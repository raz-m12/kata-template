#include "gmock/gmock.h"
#include "include/ArgsParser.hpp"

using namespace testing;
using namespace std;


// ============================================================
// ======================== Back log ==========================
// 1. Feed the parser with 0 arguments
// 2. Parses a one argument boolean attribute without a schema
// 3. Parses one argument based on a schema with support for 
//    one boolean
// 4. Gives as input arguments that do not adhere to the schema
//    which throws an exception
// 5. Adds schema support for: boolean, string, integer, double
//    arrays
// ============================================================


TEST(ArgsParser, ZeroArgumentsGiven)
{
    ArgsParser{};
}
