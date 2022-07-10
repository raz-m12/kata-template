#include "gmock/gmock.h"
#include "include/Argument.hpp"



namespace argskata_test
{
    using namespace argskata::lib;
    using std::shared_ptr;
    using std::make_shared;
    using std::string;

    class AnArgumentValueValidator: public ::testing::Test
    {
        public:
        const shared_ptr<BooleanArgument> BooleanArg = make_shared<BooleanArgument>("d");
        const shared_ptr<IntegerArgument> IntArg = make_shared<IntegerArgument>("d");
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
        IntArg->SetValue(10);

        ASSERT_THAT(IntegerArgument::Value(IntegerArgument), Eq(10));
    }
} // namespace argskata_test
