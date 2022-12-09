#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <array>
#include <map>
#include <set>
#include <valarray>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    std::set<std::tuple<int, int>> tail_positions;

    std::array<std::valarray<int>, 10> current_knot_positions;
    std::fill(current_knot_positions.begin(), current_knot_positions.end(),
              std::valarray<int>{0, 0});
    std::map<std::string, std::valarray<int>> move_map{
        {"R", {1, 0}}, {"U", {0, 1}}, {"L", {-1, 0}}, {"D", {0, -1}}};
    tail_positions.emplace(std::tuple<int, int>{current_knot_positions.at(9)[0],
                                                current_knot_positions.at(9)[1]});

    auto get_next_knot_position = [](const std::valarray<int> &current_knot_position,
                                     const std::valarray<int> &front_knot_position) {
        std::valarray<int> next_knot_position = current_knot_position;
        auto distance = front_knot_position - current_knot_position;
        if (distance.max() <= 1 && distance.min() >= -1) {
            return current_knot_position;
        }
        if (distance[0] != 0) {
            next_knot_position[0] += distance[0] / abs(distance[0]);
        }
        if (distance[1] != 0) {
            next_knot_position[1] += distance[1] / abs(distance[1]);
        }

        return next_knot_position;
    };

    for (auto movement : input) {
        auto instruction = SplitStringToVector(movement, " ");
        auto direction = instruction[0];
        auto steps = std::stoi(instruction[1]);

        for (int i = 0; i < steps; i++) {
            current_knot_positions.at(0) += move_map.at(direction);
            for (size_t j = 0; j < current_knot_positions.size() - 1; j++) {
                current_knot_positions.at(j + 1) = get_next_knot_position(
                    current_knot_positions.at(j + 1), current_knot_positions.at(j));
            }
            tail_positions.emplace(std::tuple<int, int>{current_knot_positions.at(9)[0],
                                                        current_knot_positions.at(9)[1]});
        }
    }
    return tail_positions.size();
}