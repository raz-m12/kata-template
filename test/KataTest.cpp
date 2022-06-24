#include "gmock/gmock.h"
#include "include/Kata.hpp"

using namespace testing;


TEST(ExampleTest, PassingTest)
{
    ASSERT_THAT(1, Eq(1));
}
