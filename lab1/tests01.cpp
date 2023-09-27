#include <gtest/gtest.h>
#include <string>
#include "logic.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(logic(12, "monday")==true);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(logic(13, "monday")==false);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(logic(100, "tuesday")==true);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(logic(80, "tuesday")==false);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(logic(34, "wednesday")==true);
}

TEST(test_06, basic_test_set)
{
    ASSERT_TRUE(logic(0, "wednesday")==false);
}

TEST(test_07, basic_test_set)
{
    ASSERT_TRUE(logic(0, "thursday")==true);
}

TEST(test_08, basic_test_set)
{
    ASSERT_TRUE(logic(77777, "thursday")==false);
}

TEST(test_09, basic_test_set)
{
    ASSERT_TRUE(logic(2, "friday")==true);
}

TEST(test_10, basic_test_set)
{
    ASSERT_TRUE(logic(1, "friday")==false);
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}