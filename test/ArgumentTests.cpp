#include "gmock/gmock.h"
#include "include/Argument.hpp"



namespace argskata_test
{
    using namespace argskata::lib;
    using std::shared_ptr;
    using std::make_shared;
    using std::string;
    using std::vector;
    using testing::Eq;
    using testing::ElementsAre;
    using testing::ElementsAreArray;

    class AnArgumentValueValidator: public ::testing::Test
    {
        public:
        const shared_ptr<BooleanArgument> BooleanArg = make_shared<BooleanArgument>("b");
        const shared_ptr<IntegerArgument> IntArg = make_shared<IntegerArgument>("d");
        const shared_ptr<StringArgument> StrArg = make_shared<StringArgument>("s");
        const shared_ptr<DoubleArgument> DoubleArg = make_shared<DoubleArgument>("s");
        const shared_ptr<StringArrayArgument> StrArrArg = make_shared<StringArrayArgument>("a");
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

    TEST_F(AnArgumentValueValidator, IntegerArgumentValueIsTen)
    {
        IntArg->SetValue("10");

        ASSERT_THAT(IntegerArgument::Value(IntArg), Eq(10));
    }

    TEST_F(AnArgumentValueValidator, IntegerArgumentDefaultsToZero)
    {
        ASSERT_THAT(IntegerArgument::Value(IntArg), Eq(0));
    }

    TEST_F(AnArgumentValueValidator, StringArgumentValueIsHelloWorld)
    {
        StrArg->SetValue("Hello World");

        ASSERT_THAT(StringArgument::Value(StrArg), Eq("Hello World"));
    }

    TEST_F(AnArgumentValueValidator, StringArgumentDefaultsToEmptyString)
    {
        ASSERT_THAT(StringArgument::Value(StrArg), Eq(""));
    }


    TEST_F(AnArgumentValueValidator, DoubleArgumentValueIsThirtyFourPointFive)
    {
        DoubleArg->SetValue("34.5");

        ASSERT_THAT(DoubleArgument::Value(DoubleArg), Eq(34.5));
    }

    TEST_F(AnArgumentValueValidator, VerifiesNegativeArgumentValue)
    {
        DoubleArg->SetValue("-34.5");

        ASSERT_THAT(DoubleArgument::Value(DoubleArg), Eq(-34.5));
    }

    TEST_F(AnArgumentValueValidator, DoubleArgumentDefaultsToZero)
    {
        ASSERT_THAT(DoubleArgument::Value(DoubleArg), Eq(0));
    }

    TEST_F(AnArgumentValueValidator, StringArrayArgumentIsArrayWithTwoValues)
    {
        StrArrArg->SetValue("argument1");
        StrArrArg->SetValue("argument2");
        vector<string> expected{"argument1", "argument2"};

        ASSERT_THAT(StringArrayArgument::Value(StrArrArg), ElementsAreArray(expected));
    }

    TEST_F(AnArgumentValueValidator, StringArrayArgumentDefaultsToEmptyArray)
    {
        ASSERT_THAT(StringArrayArgument::Value(StrArrArg), ElementsAre());
    }
} // namespace argskata_test
