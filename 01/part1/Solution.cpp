#include "Solution.hpp"

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    int max_calories = 0;
    int current_elf_calories = 0;
    for (auto calorie : input) {
        if (calorie.length() > 0) {
            current_elf_calories += std::stoi(calorie);
        } else {
            if (current_elf_calories > max_calories) {
                max_calories = current_elf_calories;
            }
            current_elf_calories = 0;
        }
    }
    return max_calories;
}