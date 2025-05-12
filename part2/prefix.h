#pragma once

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <optional>

// Максимальная сумма подмассива длины k
std::optional<long long> maxSum(const std::vector<int>& arr, int k); // T: O(N), M: O(1)

// Количество подмассивов с суммой K
int maxLen(const std::vector<int>& nums, int k); // T: O(N), M: O(N)

// Максимальная длина подмассива с равным количеством нулей и единиц
int maxLenEq(const std::vector<int>& nums); // T: O(N), M: O(N)

// Индекс поворота массива
int pivotIndex(const std::vector<int>& nums); // T: O(N), M: O(1)

// Баланс скобок
bool canMakeValid(const std::string& s, int k); // T: O(N), M: O(1)
