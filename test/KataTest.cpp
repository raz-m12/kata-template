#include "include/Kata.hpp"
#include "gmock/gmock.h"

using namespace testing;

TEST(ExampleTest, PassingTest) { ASSERT_THAT(1, Eq(1)); }
