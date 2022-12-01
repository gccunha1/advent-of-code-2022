#include "Solution.hpp"
#include <numeric>
#include <set>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    std::multiset<int> calories_set{0, 0, 0};
    int current_elf_calories = 0;
    for (auto calorie : input) {
        if (calorie.length() > 0) {
            current_elf_calories += std::stoi(calorie);
        } else {
            calories_set.insert(current_elf_calories);
            calories_set.erase(calories_set.begin());
            current_elf_calories = 0;
        }
    }
    return std::accumulate(calories_set.begin(), calories_set.end(), 0);
}
