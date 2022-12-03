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
    std::vector<int> third_item_check(52);
    int result = 0;

    auto check_bag_items = [](std::vector<int> &count_vector,
                              const std::string &bag_contents) {
        for (size_t i = 0; i < bag_contents.length(); i++) {
            count_vector[ComputePriority(bag_contents.at(i)) - 1] = 1;
        }
    };

    for (size_t i = 0; i < input.size() / 3; i++) {
        std::fill(first_item_check.begin(), first_item_check.end(), 0);
        std::fill(second_item_check.begin(), second_item_check.end(), 0);
        std::fill(third_item_check.begin(), third_item_check.end(), 0);
        const auto first_elf_sack = input.at(3 * i);
        const auto second_elf_sack = input.at(3 * i + 1);
        const auto third_elf_sack = input.at(3 * i + 2);
        check_bag_items(first_item_check, first_elf_sack);
        check_bag_items(second_item_check, second_elf_sack);
        check_bag_items(third_item_check, third_elf_sack);
        for (size_t i = 0; i < first_item_check.size(); i++) {
            result += first_item_check.at(i) * second_item_check.at(i) *
                      third_item_check.at(i) * (i + 1);
        }
    }

    return result;
}