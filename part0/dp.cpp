#include "dp.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <limits>

int longestSubseqDP(const std::vector<int>& nums) {
    if (nums.empty()) 
        return 0;
    int n = nums.size();
    std::vector<int> dp(n, 1);
    int maxLen = 1;
    for (int i = 1; i < n; ++i) {
        if (nums[i] > nums[i - 1])
            dp[i] = dp[i - 1] + 1;
        maxLen = std::max(maxLen, dp[i]);
    }
    return maxLen;
}

int longestSubseqOpt(const std::vector<int>& nums) {
    if (nums.empty()) 
        return 0;
    int maxLen = 1, currentLen = 1;
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] > nums[i - 1]) {
            currentLen++;
        }
        else {
            currentLen = 1; // Сброс
        }
        maxLen = std::max(maxLen, currentLen);
    }
    return maxLen;
}

std::vector<std::vector<int>> triangleDP(int numRows) {
    if (numRows <= 0) 
        return {};
    std::vector<std::vector<int>> triangle(numRows);
    for (int i = 0; i < numRows; ++i) {
        triangle[i].resize(i + 1);
        triangle[i][0] = 1; // первый
        triangle[i][i] = 1; // последний
        for (int j = 1; j < i; ++j) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }
    return triangle;
}

std::vector<std::vector<int>> triangleOpt(int numRows) {
    if (numRows <= 0) 
        return {};
    std::vector<std::vector<int>> triangle;
    triangle.push_back({ 1 });
    if (numRows == 1) 
        return triangle;

    for (int i = 1; i < numRows; ++i) {
        std::vector<int> prevRow = triangle.back();
        std::vector<int> currentRow(i + 1);
        currentRow[0] = 1;
        currentRow[i] = 1;
        for (int j = 1; j < i; ++j) {
            currentRow[j] = prevRow[j - 1] + prevRow[j];
        }
        triangle.push_back(currentRow);
    }
    return triangle;
}

int countSeqTwoDP(int n) {
    if (n <= 0) 
        return 0;
    if (n == 1) 
        return 2;

    std::vector<int> dp0(n + 1); // счетчик с 0
    std::vector<int> dp1(n + 1); // счетчик с 1

    dp0[1] = dp1[1] = 1;

    for (int i = 2; i <= n; ++i) {
        dp0[i] = dp0[i - 1] + dp1[i - 1];
        dp1[i] = dp0[i - 1];
    }
    return dp0[n] + dp1[n];
}

int countSeqTwoOpt(int n) {
    if (n <= 0) 
        return 0;
    if (n == 1) 
        return 2;

    int endsZero = 1, endsOne = 1;

    for (int i = 2; i <= n; ++i) {
        int prevEndsZero = endsZero;
        endsZero = endsZero + endsOne;
        endsOne = prevEndsZero;
    }
    return endsZero + endsOne;
}

int countSeqThreeDP(int n) {
    if (n < 0) 
        return 0;
    if (n == 0) 
        return 1;
    if (n == 1) 
        return 2;
    if (n == 2) 
        return 4;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(3, 0)); // j = 0, 1, or 2

    dp[0][0] = dp[1][0] = dp[1][1] = 1;

    dp[2][0] = dp[1][0] + dp[1][1]; // 00, 10
    dp[2][1] = dp[1][0];            // 01
    dp[2][2] = dp[1][1];            // 11

    for (int i = 3; i <= n; ++i) {
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2];
        dp[i][1] = dp[i - 1][0];
        dp[i][2] = dp[i - 1][1];
    }
    return dp[n][0] + dp[n][1] + dp[n][2];
}

int countSeqThreeOpt(int n) {
    if (n < 0) 
        return 0;
    if (n == 0) 
        return 1;
    if (n == 1) 
        return 2;
    if (n == 2) 
        return 4;

    int ends0 = 2;
    int ends1 = 1;
    int ends11 = 1;

    for (int i = 3; i <= n; ++i) {
        int prevEnds0 = ends0;
        int prevEnds1 = ends1;
        int prevEnds11 = ends11;

        ends0 = prevEnds0 + prevEnds1 + prevEnds11;
        ends1 = prevEnds0;
        ends11 = prevEnds1;
    }
    return ends0 + ends1 + ends11;
}

int maxProfit(const std::vector<int>& prices) {
    if (prices.size() < 2) 
        return 0;
    int minPrice = prices[0];
    int maxProf = 0;
    for (size_t i = 1; i < prices.size(); ++i) {
        maxProf = std::max(maxProf, prices[i] - minPrice);
        minPrice = std::min(minPrice, prices[i]);
    }
    return maxProf;
}

int coinChange(const std::vector<int>& coins, int amount) {
    if (amount < 0) 
        return -1;
    if (amount == 0) 
        return 0;

    std::vector<int> dp(amount + 1, amount + 1); // amount + 1  - макс инициализация
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (i - coin >= 0) {
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return (dp[amount] > amount) ? -1 : dp[amount];
}

std::string palindromeDP(const std::string& s) {
    if (s.empty()) return "";
    int n = s.length();
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
    int start = 0, maxLen = 1;

    // диагональ - 1 символ
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }

    // 2 символа
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLen = 2;
        }
    }

    // 3 и более
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                if (len > maxLen) {
                    start = i;
                    maxLen = len;
                }
            }
        }
    }
    return s.substr(start, maxLen);
}

std::string palindromeOpt(const std::string& s) {
    if (s.empty()) 
        return "";
    int n = s.length();
    if (n < 2) 
        return s;

    int start = 0, maxLen = 1;

    auto expandCenter = [&](int left, int right) {
        while (left >= 0 && right < n && s[left] == s[right]) {
            if (right - left + 1 > maxLen) {
                maxLen = right - left + 1;
                start = left;
            }
            left--;
            right++;
        }
    };

    for (int i = 0; i < n; ++i) {
        expandCenter(i, i);     // не четные
        expandCenter(i, i + 1); // четные
    }
    return s.substr(start, maxLen);
}

