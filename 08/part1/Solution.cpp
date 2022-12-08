#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <stack>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    const size_t columns = input[0].length();
    const size_t lines = input.size();
    std::vector<std::vector<bool>> visible(lines);

    for (size_t i = 0; i < lines; i++) {
        visible.at(i).resize(columns);
        std::fill(visible.at(i).begin(), visible.at(i).end(), false);
    }

    for (size_t i = 0; i < lines; i++) {
        int max_left_tree = -1;
        for (size_t j = 0; j < columns; j++) {
            const auto tree_height = static_cast<int>(input.at(i).at(j) - '0');
            if (tree_height > max_left_tree) {
                visible.at(i).at(j) = true;
                max_left_tree = tree_height;
                if (max_left_tree == 9) {
                    break;
                }
            }
        }
    }

    for (size_t i = 0; i < lines; i++) {
        int max_right_tree = -1;
        for (size_t j = 0; j < columns; j++) {
            const auto tree_height =
                static_cast<int>(input.at(i).at(columns - j - 1) - '0');
            if (tree_height > max_right_tree) {
                visible.at(i).at(columns - j - 1) = true;
                max_right_tree = tree_height;
                if (max_right_tree == 9) {
                    break;
                }
            }
        }
    }
    for (size_t j = 0; j < columns; j++) {
        int max_top_tree = -1;
        for (size_t i = 0; i < lines; i++) {
            const auto tree_height = static_cast<int>(input.at(i).at(j) - '0');
            if (tree_height > max_top_tree) {
                visible.at(i).at(j) = true;
                max_top_tree = tree_height;
                if (max_top_tree == 9) {
                    break;
                }
            }
        }
    }
    for (size_t j = 0; j < columns; j++) {
        int max_bottom_tree = -1;
        for (size_t i = 0; i < lines; i++) {
            const auto tree_height =
                static_cast<int>(input.at(lines - i - 1).at(j) - '0');
            if (tree_height > max_bottom_tree) {
                visible.at(lines - i - 1).at(j) = true;
                max_bottom_tree = tree_height;
                if (max_bottom_tree == 9) {
                    break;
                }
            }
        }
    }

    int count = 0;
    for (size_t i = 0; i < lines; i++) {
        for (size_t j = 0; j < columns; j++) {
            count += static_cast<int>(visible.at(i).at(j));
        }
    }

    return count;
}