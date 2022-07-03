#include "gmock/gmock.h"
#include "include/Argument.hpp"

using namespace argskata::lib;

namespace argskata_test
{
    TEST(ArgumentValueValidator, BooleanArgumentIsTrue)
    {
        AbstractArgument arg{"d", ArgumentType::_boolean};

        //arg.SetValue(false);

        //ASSERT_FALSE(arg.Value());
    }
}