#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <map>
#include <set>
#include <valarray>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    std::set<std::tuple<int, int>> tail_positions;
    std::valarray<int> current_head_position{0, 0};
    std::valarray<int> previous_head_position{0, 0};
    std::valarray<int> current_tail_position{0, 0};
    std::map<std::string, std::valarray<int>> move_map{
        {"R", {1, 0}}, {"U", {0, 1}}, {"L", {-1, 0}}, {"D", {0, -1}}};
    tail_positions.emplace(
        std::tuple<int, int>{current_tail_position[0], current_tail_position[1]});
    for (auto movement : input) {
        auto instruction = SplitStringToVector(movement, " ");
        auto direction = instruction[0];
        auto steps = std::stoi(instruction[1]);

        for (int i = 0; i < steps; i++) {
            previous_head_position = current_head_position;
            current_head_position += move_map.at(direction);
            if (((current_head_position - current_tail_position).max() > 1) ||
                ((current_head_position - current_tail_position).min() < -1)) {
                current_tail_position = previous_head_position;
                tail_positions.emplace(std::tuple<int, int>{current_tail_position[0],
                                                            current_tail_position[1]});
            }
        }
    }
    return tail_positions.size();
}