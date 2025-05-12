#pragma once

#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <map>
#include <limits>

// Последовательность без двух единиц подряд
int countSeqTwoDP(int n); // T: O(N), M: O(N)
int countSeqTwoOpt(int n); // T: O(N), M: O(1)

// Последовательность без трех единиц подряд
int countSeqThreeDP(int n); // T: O(N), M: O(N)
int countSeqThreeOpt(int n); // T: O(N), M: O(1)

// Наибольшая непрерывная возрастающая последовательность
int longestSubseqDP(const std::vector<int>& nums); //T: O(N), M: O(N)
int longestSubseqOpt(const std::vector<int>& nums); //T: O(N), M: O(1)

// Треугольник Паскаля
std::vector<std::vector<int>> triangleDP(int numRows); // T: O(N^2), M: O(N^2)
std::vector<std::vector<int>> triangleOpt(int numRows); // T: O(N^2), M: O(N) - храним тек и пред строки

// Максимальная выгода (использование матрицы не разумно)
int maxProfit(const std::vector<int>& prices); // T: O(N), M: O(1)

// Размен монет
int coinChange(const std::vector<int>& coins, int amount); // T: O(amount * num_coins), M: O(amount)

// Максимальный палиндром в строке
std::string palindromeDP(const std::string& s); // T: O(N^2), M: O(N^2)
std::string palindromeOpt(const std::string& s); // T: O(N^2), M: O(1)

