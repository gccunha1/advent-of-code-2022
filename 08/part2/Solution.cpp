#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <algorithm>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    const size_t columns = input[0].length();
    const size_t lines = input.size();
    std::vector<std::vector<int>> right_visibility(lines);
    std::vector<std::vector<int>> left_visibility(lines);
    std::vector<std::vector<int>> up_visibility(lines);
    std::vector<std::vector<int>> down_visibility(lines);
    std::vector<int> last_tree_heights_index(10, 0);

    for (size_t i = 0; i < lines; i++) {
        right_visibility.at(i).resize(columns);
        left_visibility.at(i).resize(columns);
        up_visibility.at(i).resize(columns);
        down_visibility.at(i).resize(columns);
        std::fill(right_visibility.at(i).begin(), right_visibility.at(i).end(), 0);
        std::fill(left_visibility.at(i).begin(), left_visibility.at(i).end(), 0);
        std::fill(up_visibility.at(i).begin(), up_visibility.at(i).end(), 0);
        std::fill(down_visibility.at(i).begin(), down_visibility.at(i).end(), 0);
        std::fill(last_tree_heights_index.begin(), last_tree_heights_index.end(), 0);
    }

    for (size_t i = 0; i < lines; i++) {
        std::fill(last_tree_heights_index.begin(), last_tree_heights_index.end(), 0);
        for (size_t j = 0; j < columns; j++) {
            const auto tree_height = static_cast<int>(input.at(i).at(j) - '0');
            if (j == 0) {
                left_visibility.at(i).at(j) = 0;
            } else {
                auto last_equal_or_greater_tree =
                    std::max_element(last_tree_heights_index.begin() + tree_height,
                                     last_tree_heights_index.end());
                left_visibility.at(i).at(j) = j - *last_equal_or_greater_tree;
            }
            last_tree_heights_index.at(tree_height) = j;
        }
    }

    for (size_t i = 0; i < lines; i++) {
        std::fill(last_tree_heights_index.begin(), last_tree_heights_index.end(), 0);
        for (size_t j = 0; j < columns; j++) {
            const auto tree_height =
                static_cast<int>(input.at(i).at(columns - j - 1) - '0');
            if (j == 0) {
                right_visibility.at(i).at(columns - j - 1) = 0;
            } else {
                auto last_equal_or_greater_tree =
                    std::max_element(last_tree_heights_index.begin() + tree_height,
                                     last_tree_heights_index.end());
                right_visibility.at(i).at(columns - j - 1) =
                    j - *last_equal_or_greater_tree;
            }
            last_tree_heights_index.at(tree_height) = j;
        }
    }

    for (size_t j = 0; j < columns; j++) {
        std::fill(last_tree_heights_index.begin(), last_tree_heights_index.end(), 0);
        for (size_t i = 0; i < lines; i++) {
            const auto tree_height = static_cast<int>(input.at(i).at(j) - '0');
            if (i == 0) {
                up_visibility.at(i).at(j) = 0;
            } else {
                auto last_equal_or_greater_tree =
                    std::max_element(last_tree_heights_index.begin() + tree_height,
                                     last_tree_heights_index.end());
                up_visibility.at(i).at(j) = i - *last_equal_or_greater_tree;
            }
            last_tree_heights_index.at(tree_height) = i;
        }
    }

    for (size_t j = 0; j < columns; j++) {
        std::fill(last_tree_heights_index.begin(), last_tree_heights_index.end(), 0);
        for (size_t i = 0; i < lines; i++) {
            const auto tree_height =
                static_cast<int>(input.at(lines - i - 1).at(j) - '0');
            if (i == 0) {
                down_visibility.at(lines - i - 1).at(j) = 0;
            } else {
                auto last_equal_or_greater_tree =
                    std::max_element(last_tree_heights_index.begin() + tree_height,
                                     last_tree_heights_index.end());
                down_visibility.at(lines - i - 1).at(j) = i - *last_equal_or_greater_tree;
            }
            last_tree_heights_index.at(tree_height) = i;
        }
    }

    int max_count = 0;
    for (size_t i = 0; i < lines; i++) {
        for (size_t j = 0; j < columns; j++) {
            auto count = right_visibility.at(i).at(j) * left_visibility.at(i).at(j) *
                         up_visibility.at(i).at(j) * down_visibility.at(i).at(j);
            std::cout << right_visibility.at(i).at(j) << left_visibility.at(i).at(j)
                      << up_visibility.at(i).at(j) << down_visibility.at(i).at(j)
                      << std::endl;
            if (count > max_count) {
                max_count = count;
            }
        }
    }

    return max_count;
}