#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <map>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int ComputePriority(const char c) {
    if (std::islower(c)) {
        return static_cast<int>(c - 'a' + 1);
    }
    return static_cast<int>(c - 'A' + 27);
}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    std::vector<int> first_item_check(52);
    std::vector<int> second_item_check(52);
    int result = 0;
    for (auto rucksack : input) {
        std::fill(first_item_check.begin(), first_item_check.end(), 0);
        std::fill(second_item_check.begin(), second_item_check.end(), 0);
        for (size_t i = 0; i < rucksack.length() / 2; i++) {
            first_item_check[ComputePriority(rucksack.at(i)) - 1] = 1;
            second_item_check[ComputePriority(rucksack.at(rucksack.length() / 2 + i)) -
                              1] = 1;
        }

        for (size_t i = 0; i < first_item_check.size(); i++) {
            result += first_item_check[i] * second_item_check[i] * (i + 1);
        }
    }
    return result;
}