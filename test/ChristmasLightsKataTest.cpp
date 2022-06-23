#include "gmock/gmock.h"

using namespace testing;

class HoldingServiceTest: public Test
{
};

TEST_F(HoldingServiceTest, SizeInitiallyZero)
{
    ASSERT_THAT(1, Eq(2));
}