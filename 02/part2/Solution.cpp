#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <map>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    // clang-format off
    std::map<std::string, int> score_map{{"A X", 3}, {"A Y", 4}, {"A Z", 8}, 
                                         {"B X", 1}, {"B Y", 5}, {"B Z", 9}, 
                                         {"C X", 2}, {"C Y", 6}, {"C Z", 7}};
    // clang-format on
    int score = 0;
    for (auto round : input) {
        score += score_map.at(round);
    }
    return score;
}