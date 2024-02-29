#include <gtest/gtest.h>
#include "Four.hpp"

TEST(test1, copy) {
    Four num1("13");
    Four num2(num1);
    ASSERT_TRUE(num1 == num2);
}

TEST(test2, assignment) {
    Four num1({'1', '2', '3', '0'});
    Four num2 = num1;
    ASSERT_TRUE(num1 == num2);
}

TEST(test3, equal1) {
    Four num1("1203");
    Four num2({'1', '2', '0', '3'});
    ASSERT_TRUE(num1 == num2);
}

TEST(test4, equal2) {
    Four num1("0000");
    Four num2({'1', '1', '1', '1'});
    ASSERT_FALSE(num1 == num2);
}

TEST(test5, not_equal1) {
    Four num1("1303");
    Four num2({'3', '3', '0', '1'});
    ASSERT_TRUE(num1 != num2);
}

TEST(test6, not_equal2) {
    Four num1("1222");
    Four num2({'1', '2', '2', '2'});
    ASSERT_FALSE(num1 != num2);
}

TEST(test7, less) {
    Four num1("10");
    Four num2({'1', '0', '1'});
    ASSERT_TRUE(num1 < num2);
}

TEST(test8, less_equal) {
    Four num1("3030");
    Four num2({'1', '0'});
    ASSERT_FALSE(num1 <= num2);
}

TEST(test9, more) {
    Four num1("202");
    Four num2({'2'});
    ASSERT_TRUE(num1 > num2);
}

TEST(test10, more_equal) {
    Four num1("101");
    Four num2({'1', '0', '1'});
    ASSERT_TRUE(num1 >= num2);
}

TEST(test11, addition1) {
    Four num1("1");
    Four num2({'1', '0'});
    ASSERT_TRUE((num1 + num2) == Four("11"));
}

TEST(test12, subtraction1) {
    Four num1("32");
    Four num2({'3'});
    ASSERT_TRUE((num1 - num2) == Four("23"));
}

TEST(test13, subtraction2) {
    Four num1("21");
    Four num2({'1'});
    ASSERT_TRUE((num1 - num2) == Four("20"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}