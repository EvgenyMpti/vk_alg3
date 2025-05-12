#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <optional>
#include <limits>

#include "prefix.h"

TEST(PrefixTest, MaxSum) {
    // {3,8,6}=17, {8,6,9}=23, {6,9,9}=24, {9,9,8}=26, {9,8,6}=23, {8,6,11}=25. Макс 26.
    EXPECT_EQ(maxSum({ 3, 8, 6, 9, 9, 8, 6, 11 }, 3).value_or(-1), 26);
    EXPECT_EQ(maxSum({ 1, 2, 3, 4, 5 }, 2).value_or(-1), 9); // 4+5
    EXPECT_EQ(maxSum({ -1, -2, -3, -4 }, 2).value_or(-1), -3); // -1 + -2
    EXPECT_EQ(maxSum({ 5 }, 1).value_or(-1), 5);
    EXPECT_EQ(maxSum({ 1, 2, 3 }, 4), std::nullopt); // k > n
    EXPECT_EQ(maxSum({ 1, 2, 3 }, 0), std::nullopt); // k <= 0
    EXPECT_EQ(maxSum({}, 1), std::nullopt); // пустой массив
}

TEST(PrefixTest, MaxLen) {
    EXPECT_EQ(maxLen({ 3, 8, 6, 9, 2, 1, 4 }, 11), 2); // {3, 8}, {9, 2} -> Да, 2.
    EXPECT_EQ(maxLen({ 1, 1, 1 }, 2), 2);
    EXPECT_EQ(maxLen({ 1, 2, 3 }, 3), 2); 
    EXPECT_EQ(maxLen({ 1 }, 0), 0);
    EXPECT_EQ(maxLen({ 1, -1, 1, -1, 1 }, 0), 6);
    EXPECT_EQ(maxLen({}, 1), 0);
    EXPECT_EQ(maxLen({ 1, 2, 3 }, 7), 0);
}

TEST(PrefixTest, MaxLenEq) {
    EXPECT_EQ(maxLenEq({ 0, 1, 0, 0, 1 }), 4); // {1, 0, 0, 1} -> [1, -1, -1, 1] sum=0 len=4
    EXPECT_EQ(maxLenEq({ 0, 1 }), 2);
    EXPECT_EQ(maxLenEq({ 0, 0, 0, 1, 1, 1 }), 6);
    EXPECT_EQ(maxLenEq({ 0, 1, 0 }), 2); // {0, 1} или {1, 0}
    EXPECT_EQ(maxLenEq({ 0, 0, 1, 1 }), 4);
    EXPECT_EQ(maxLenEq({ 0 }), 0);
    EXPECT_EQ(maxLenEq({}), 0);
    EXPECT_EQ(maxLenEq({ 1, 1, 1, 1 }), 0);
}

TEST(PrefixTest, PivotIndex) {
    EXPECT_EQ(pivotIndex({ 9, 4, 8, 7, 1, 11, 2, 6, 1 }), 3); // l=21, r=21
    EXPECT_EQ(pivotIndex({ 1, 7, 3, 6, 5, 6 }), 3); // l=11, r=11
    EXPECT_EQ(pivotIndex({ 1, 2, 3 }), -1);
    EXPECT_EQ(pivotIndex({ 2, 1, -1 }), 0); // l=0, r=0
    EXPECT_EQ(pivotIndex({ -1, -1, -1, 0, 1, 1 }), 0); // l=0, r=0
    EXPECT_EQ(pivotIndex({ -1, -1, 0, 1, 1, 0 }), 5); // l=0, r=0
    EXPECT_EQ(pivotIndex({}), -1);
    EXPECT_EQ(pivotIndex({ 10 }), 0); // l=0, r=0
}

TEST(PrefixTest, CanMakeValid) {
    EXPECT_TRUE(canMakeValid("()", 0));
    EXPECT_TRUE(canMakeValid("())", 1));
    EXPECT_FALSE(canMakeValid("())", 0));
    EXPECT_TRUE(canMakeValid("))()", 2));
    EXPECT_TRUE(canMakeValid("()))", 2));
    EXPECT_TRUE(canMakeValid("()((", 2));
    EXPECT_FALSE(canMakeValid("()((", 1));
    EXPECT_TRUE(canMakeValid("))", 2));
    EXPECT_FALSE(canMakeValid("))()(", 2));
    EXPECT_TRUE(canMakeValid("))()(", 3));
    EXPECT_TRUE(canMakeValid("", 0));
    EXPECT_TRUE(canMakeValid("", 1));
    EXPECT_FALSE(canMakeValid("(", 0));
    EXPECT_TRUE(canMakeValid("(", 1));
    EXPECT_FALSE(canMakeValid(")", 0));
    EXPECT_TRUE(canMakeValid(")", 1));
    EXPECT_TRUE(canMakeValid("()()", 0));
}

 int main(int argc, char **argv) {
     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
 }
