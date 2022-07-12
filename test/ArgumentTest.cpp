#include "gmock/gmock.h"
#include "include/Argument.hpp"



namespace argskata_test
{
    using namespace argskata::lib;
    using std::shared_ptr;
    using std::make_shared;
    using std::string;
    using testing::Eq;

    class AnArgumentValueValidator: public ::testing::Test
    {
        public:
        const shared_ptr<BooleanArgument> BooleanArg = make_shared<BooleanArgument>("b");
        const shared_ptr<IntegerArgument> IntArg = make_shared<IntegerArgument>("d");
        const shared_ptr<StringArgument> StrArg = make_shared<StringArgument>("s");
        const shared_ptr<DoubleArgument> DoubleArg = make_shared<DoubleArgument>("s");
    };
    
    TEST_F(AnArgumentValueValidator, BooleanArgumentBecomesTrueAfterSetValue)
    {
        BooleanArg->SetValue("");

        ASSERT_TRUE(BooleanArgument::Value(BooleanArg));
    }

    TEST_F(AnArgumentValueValidator, BooleanArgumentisFalseByDefault)
    {
        ASSERT_FALSE(BooleanArgument::Value(BooleanArg));
    }

    TEST_F(AnArgumentValueValidator, IntegerArgumentValueIsSet)
    {
        IntArg->SetValue("10");

        ASSERT_THAT(IntegerArgument::Value(IntArg), Eq(10));
    }

    TEST_F(AnArgumentValueValidator, IntegerArgumentDefaultsToZero)
    {
        ASSERT_THAT(IntegerArgument::Value(IntArg), Eq(0));
    }

    TEST_F(AnArgumentValueValidator, StringArgumentValueIsSet)
    {
        StrArg->SetValue("Hello World");

        ASSERT_THAT(StringArgument::Value(StrArg), Eq("Hello World"));
    }

    TEST_F(AnArgumentValueValidator, StringArgumentDefaultsToEmptyString)
    {
        ASSERT_THAT(StringArgument::Value(StrArg), Eq(""));
    }


    TEST_F(AnArgumentValueValidator, DoubleArgumentValueIsSetCorrectly)
    {
        DoubleArg->SetValue("34.5");

        ASSERT_THAT(DoubleArgument::Value(DoubleArg), Eq(34.5));
    }

    TEST_F(AnArgumentValueValidator, DoubleArgumentDefaultsToZero)
    {
        ASSERT_THAT(DoubleArgument::Value(DoubleArg), Eq(0));
    }
} // namespace argskata_test
