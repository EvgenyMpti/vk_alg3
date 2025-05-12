#include "gtest/gtest.h"
#include "dp.h"
#include <vector>
#include <string>
#include <algorithm>

bool compareTriangles(const std::vector<std::vector<int>>& res, const std::vector<std::vector<int>>& exp) {
    if (res.size() != exp.size()) return false;
    for (size_t i = 0; i < res.size(); ++i) {
        if (res[i].size() != exp[i].size()) return false;
        for (size_t j = 0; j < res[i].size(); ++j) {
            if (res[i][j] != exp[i][j]) return false;
        }
    }
    return true;
}

TEST(DPTest, LongestSubseq) {
    EXPECT_EQ(longestSubseqDP({ 3, 2, 8, 9, 5, 10 }), 3); // 2,8,9
    EXPECT_EQ(longestSubseqDP({ 1, 2, 7, 9, 0, 10 }), 4); // 1,2,7,9
    EXPECT_EQ(longestSubseqDP({ 8, 8, 8, 8 }), 1);
    EXPECT_EQ(longestSubseqDP({ 1, 2, 3, 4, 5 }), 5);
    EXPECT_EQ(longestSubseqDP({ 5, 4, 3, 2, 1 }), 1);
    EXPECT_EQ(longestSubseqDP({}), 0);
    EXPECT_EQ(longestSubseqDP({ 10 }), 1);

    EXPECT_EQ(longestSubseqOpt({ 3, 2, 8, 9, 5, 10 }), 3);
    EXPECT_EQ(longestSubseqOpt({ 1, 2, 7, 9, 0, 10 }), 4);
    EXPECT_EQ(longestSubseqOpt({ 8, 8, 8, 8 }), 1);
    EXPECT_EQ(longestSubseqOpt({ 1, 2, 3, 4, 5 }), 5);
    EXPECT_EQ(longestSubseqOpt({ 5, 4, 3, 2, 1 }), 1);
    EXPECT_EQ(longestSubseqOpt({}), 0);
    EXPECT_EQ(longestSubseqOpt({ 10 }), 1);
}

TEST(DPTest, Triangle) {
    std::vector<std::vector<int>> expected1 = { {1} };
    EXPECT_TRUE(compareTriangles(triangleDP(1), expected1));
    EXPECT_TRUE(compareTriangles(triangleOpt(1), expected1));

    std::vector<std::vector<int>> expected5 = {
        {1},
        {1,1},
        {1,2,1},
        {1,3,3,1},
        {1,4,6,4,1}
    };
    EXPECT_TRUE(compareTriangles(triangleDP(5), expected5));
    EXPECT_TRUE(compareTriangles(triangleOpt(5), expected5));

    EXPECT_TRUE(triangleDP(0).empty());
    EXPECT_TRUE(triangleOpt(0).empty());
}

TEST(DPTest, CountSeqTwo) {
    EXPECT_EQ(countSeqTwoDP(1), 2); // 0, 1
    EXPECT_EQ(countSeqTwoDP(2), 3); // 00, 01, 10
    EXPECT_EQ(countSeqTwoDP(3), 5); // 000, 001, 010, 100, 101
    EXPECT_EQ(countSeqTwoDP(0), 0);

    EXPECT_EQ(countSeqTwoOpt(1), 2);
    EXPECT_EQ(countSeqTwoOpt(2), 3);
    EXPECT_EQ(countSeqTwoOpt(3), 5);
    EXPECT_EQ(countSeqTwoOpt(0), 0);
}

TEST(DPTest, CountSeqThree) {
    EXPECT_EQ(countSeqThreeDP(0), 1);
    EXPECT_EQ(countSeqThreeDP(1), 2);  // 0, 1
    EXPECT_EQ(countSeqThreeDP(2), 4);  // 00, 01, 10, 11
    EXPECT_EQ(countSeqThreeDP(3), 7);  // 000, 001, 010, 011, 100, 101, 110

    EXPECT_EQ(countSeqThreeOpt(0), 1);
    EXPECT_EQ(countSeqThreeOpt(1), 2);
    EXPECT_EQ(countSeqThreeOpt(2), 4);
    EXPECT_EQ(countSeqThreeOpt(3), 7);
}

TEST(DPTest, MaxProfit) {
    EXPECT_EQ(maxProfit({ 8, 9, 3, 7, 4, 16, 12 }), 13); // 3 -> 16
    EXPECT_EQ(maxProfit({ 1, 2, 3, 4, 5, 6, 7 }), 6);   // 1 -> 7
    EXPECT_EQ(maxProfit({ 8, 7, 6, 5, 4, 3, 2 }), 0);
    EXPECT_EQ(maxProfit({ 7, 1, 5, 3, 6, 4 }), 5);    // 1 -> 6
    EXPECT_EQ(maxProfit({ 1 }), 0);
    EXPECT_EQ(maxProfit({}), 0);
}

TEST(DPTest, CoinChange) {
    EXPECT_EQ(coinChange({ 1, 2, 5 }, 11), 3); // 5+5+1
    EXPECT_EQ(coinChange({ 2 }, 3), -1);
    EXPECT_EQ(coinChange({ 1,2,5 }, 0), 0);
    EXPECT_EQ(coinChange({ 1,2,5 }, 7), 2); // 5+2
    EXPECT_EQ(coinChange({ 1 }, 100), 100);
    EXPECT_EQ(coinChange({ 1,5,10,25 }, 15), 2); // 10+5
}

TEST(DPTest, Palindrome) {
    EXPECT_EQ(palindromeDP("babad"), "bab"); // правильно еще aba, но реализация устойчива
    EXPECT_EQ(palindromeDP("cbbd"), "bb");
    EXPECT_EQ(palindromeDP("a"), "a");
    EXPECT_EQ(palindromeDP("racecar"), "racecar");
    EXPECT_EQ(palindromeDP(""), "");
    EXPECT_EQ(palindromeDP("abacaba"), "abacaba");
    EXPECT_EQ(palindromeDP("forgeeksskeegfor"), "geeksskeeg");


    // заглушка для рандомного выбора
    std::string resOpt1 = palindromeOpt("babad");
    EXPECT_TRUE(resOpt1 == "bab" || resOpt1 == "aba");

    EXPECT_EQ(palindromeOpt("cbbd"), "bb");
    EXPECT_EQ(palindromeOpt("a"), "a");
    EXPECT_EQ(palindromeOpt("racecar"), "racecar");
    EXPECT_EQ(palindromeOpt(""), "");
    EXPECT_EQ(palindromeOpt("abacaba"), "abacaba");
    EXPECT_EQ(palindromeOpt("forgeeksskeegfor"), "geeksskeeg");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
