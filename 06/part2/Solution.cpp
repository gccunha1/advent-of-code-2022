#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <algorithm>
#include <array>
Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    std::array<char, 14> char_buffer{'c', 'c', 'c', 'c', 'c', 'c', 'c',
                                     'c', 'c', 'c', 'c', 'c', 'c', 'c'};
    std::array<int, 26> char_count{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t oldest = 0;
    int count = 0;
    for (auto c : input[0]) {
        count++;
        auto popped_char = char_buffer.at(oldest);
        char_buffer.at(oldest) = c;
        char_count.at(popped_char - 'a')--;
        char_count.at(c - 'a')++;
        if (!std::count_if(char_count.begin(), char_count.end(),
                           [](const int n) { return n > 1; }) &&
            count >= 14) {
            return count;
        }
        oldest = (oldest + 1) % 14;
    }
    return count;
}