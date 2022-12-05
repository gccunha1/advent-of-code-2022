#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <stack>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    auto parse_moves = [](std::string &move) -> std::vector<uint8_t> {
        std::vector<uint8_t> move_sequence(3);
        auto str_move_sequence = SplitStringToVector(move, " ");
        for (size_t i = 0; i < 3; i++) {
            move_sequence[i] =
                static_cast<uint8_t>(std::stoi(str_move_sequence[2 * i + 1]));
        }
        return move_sequence;
    };
    std::vector<std::stack<char>> stacks(9);
    auto move_crates = [&stacks](std::vector<uint8_t> move) {
        auto crate_amount = move[0];
        auto src = move[1] - 1;
        auto dst = move[2] - 1;
        std::stack<char> crate_buffer;

        for (size_t i = 0; i < crate_amount; i++) {
            crate_buffer.push(stacks.at(src).top());
            stacks.at(src).pop();
        }
        while (!crate_buffer.empty()) {
            stacks.at(dst).push(crate_buffer.top());
            crate_buffer.pop();
        }
    };

    size_t i = 0;
    for (i = 0; i < input.size(); i++) {
        if (input.at(i).find(" 1 ") != std::string::npos) {
            break;
        }
    }
    int max_stacks = 0;
    for (size_t j = 1; j < input.at(i).length(); j += 4) {
        if ((input.at(i).at(j) - '0') == (max_stacks + 1)) {
            max_stacks = input.at(i).at(j) - '0';
        } else {
            break;
        }
    }
    for (size_t j = 0; j < i; j++) {
        for (size_t k = 0; k < static_cast<size_t>(max_stacks); k++) {
            if (std::isalpha(input.at(i - j - 1).at(4 * k + 1))) {
                stacks.at(k).push(input.at(i - j - 1).at(4 * k + 1));
            }
        }
    }

    for (auto line : input) {
        if (line.find("move") != std::string::npos) {
            move_crates(parse_moves(line));
        }
    }

    return max_stacks;
}