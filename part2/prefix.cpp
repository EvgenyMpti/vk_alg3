#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <optional>
#include <algorithm>
#include <limits>

#include "prefix.h"

std::optional<long long> maxSum(const std::vector<int>& arr, int k) {
    int n = arr.size();
    if (k <= 0 || k > n)
        return std::nullopt;

    long long currentSum = 0;
    for (int i = 0; i < k; ++i) { // сумма первого окна
        currentSum += arr[i];
    }

    long long maxSum = currentSum;

    for (int i = k; i < n; ++i) {
        currentSum = currentSum - arr[i - k] + arr[i]; // вычитаем вышедший элемент и добавляем новый
        maxSum = std::max(maxSum, currentSum);
    }

    return maxSum;
}

int maxLen(const std::vector<int>& nums, int k) {
    int n = nums.size();
    if (n == 0) 
        return 0;

    std::unordered_map<long long, int> prefixCnt;
    prefixCnt[0] = 1;

    long long prefixSum = 0;
    int count = 0;

    for (int num : nums) {
        prefixSum += num;

        // если встречалась ранее, то подмассив между индексом и текущим
        long long target = prefixSum - k;
        if (prefixCnt.count(target)) {
            count += prefixCnt[target]; // количество таких подмассивов
        }

        prefixCnt[prefixSum]++;
    }

    return count;
}

int maxLenEq(const std::vector<int>& nums) {
    int n = nums.size();
    if (n < 2) 
        return 0;

    std::unordered_map<int, int> indexMap;
    indexMap[0] = -1;

    int prefixSum = 0;
    int maxLen = 0;

    for (int i = 0; i < n; ++i) {
        prefixSum += (nums[i] == 0) ? -1 : 1; // Обновляем сумму

        if (indexMap.count(prefixSum))
            maxLen = std::max(maxLen, i - indexMap[prefixSum]);
        else
            indexMap[prefixSum] = i;
    }

    return maxLen;
}

// Индекс поворота массива
int pivotIndex(const std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) 
        return -1;

    long long totalSum = 0; // общая сумма
    for (int num : nums)
        totalSum += num;

    long long leftSum = 0;
    for (int i = 0; i < n; ++i) {
        long long rightSum = totalSum - leftSum - nums[i];

        if (leftSum == rightSum) {
            return i;
        }

        leftSum += nums[i];
    }

    return -1;
}

bool canMakeValid(const std::string& s, int k) {
    int n = s.length();
    int balance = 0;        // баланс +1 за '(', -1 за ')'
    int extra_closed = 0;   // счетчик лишних -1

    for (char c : s) {
        if (c == '(') {
            balance++;
        }
        else {
            if (balance > 0)
                balance--; // закрываем
            else
                extra_closed++;
        }
    }

    int min_del = balance + extra_closed; // мин кол-во удалений
    return min_del <= k;
}
