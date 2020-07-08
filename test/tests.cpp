#include "gtest/gtest.h"

TEST(poker_test, nothingtest)
{
    EXPECT_EQ(1, 1);
}

TEST(poker_test, nothingtest2)
{
    EXPECT_EQ(1, 2);
}

int main (int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}