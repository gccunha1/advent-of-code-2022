#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <array>
Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    std::array<char, 4> char_buffer{'c', 'c', 'c', 'c'};
    uint8_t oldest = 0;
    int count = 0;
    for (auto c : input[0]) {
        count++;
        char_buffer.at(oldest) = c;
        if ((char_buffer.at(0) != char_buffer.at(1)) &&
            (char_buffer.at(0) != char_buffer.at(2)) &&
            (char_buffer.at(0) != char_buffer.at(3)) &&
            (char_buffer.at(1) != char_buffer.at(2)) &&
            (char_buffer.at(1) != char_buffer.at(3)) &&
            (char_buffer.at(2) != char_buffer.at(3)) && count >= 4) {
            return count;
        }
        oldest = (oldest + 1) % 4;
    }
    return count;
}