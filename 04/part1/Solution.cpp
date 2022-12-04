#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <tuple>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    auto interval_contains_interval = [](std::tuple<int, int> a,
                                         std::tuple<int, int> b) -> bool {
        return (std::get<0>(a) <= std::get<0>(b)) && (std::get<1>(a) >= std::get<1>(b));
    };

    int count = 0;
    for (auto whole_pair_limits : input) {
        auto pair_limits_vector = SplitStringToVector(whole_pair_limits, ",");

        auto elf0_limits = SplitStringToVector(pair_limits_vector[0], "-");
        auto elf1_limits = SplitStringToVector(pair_limits_vector[1], "-");

        std::tuple<int, int> elf0_limits_integers{std::stoi(elf0_limits[0]),
                                                  std::stoi(elf0_limits[1])};

        std::tuple<int, int> elf1_limits_integers{std::stoi(elf1_limits[0]),
                                                  std::stoi(elf1_limits[1])};

        if (interval_contains_interval(elf0_limits_integers, elf1_limits_integers) ||
            interval_contains_interval(elf1_limits_integers, elf0_limits_integers)) {
            count++;
        }
    }

    return count;
}