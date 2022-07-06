#include "gmock/gmock.h"
#include "include/Argument.hpp"

using namespace argskata::lib;

namespace argskata_test
{
    using std::shared_ptr;
    using std::make_shared;

    TEST(ArgumentValueValidator, BooleanArgumentIsTrue)
    {
        shared_ptr<BooleanArgument> arg = make_shared<BooleanArgument>("d");

        arg->SetValue("");

        ASSERT_TRUE(BooleanArgument::Value(arg));
    }
} // namespace argskata_test
