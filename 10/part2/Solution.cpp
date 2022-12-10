#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <array>
#include <functional>
#include <map>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    int cycle = 1;
    int rx = 1;
    std::array<char, 240> output = {
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};
    auto increment_cycle = [&cycle, &rx, &output](int amount) {
        for (int i = 0; i < amount; i++) {
            std::cout << cycle << ": " << rx << std::endl;
            if (((cycle % 40) == (rx + 2) % 40) || ((cycle % 40) == rx % 40) ||
                ((cycle % 40) == (rx + 1) % 40)) {
                output.at(cycle - 1) = '#';
            }
            cycle++;
        }
    };
    std::map<std::string, std::function<void(int)>> instruction_to_action{
        {"noop", [&increment_cycle](int add = 0) { increment_cycle(1); }},
        {"addx", [&increment_cycle, &rx](int add) {
             increment_cycle(2);
             rx += add;
         }}};

    for (auto instruction : input) {
        auto assembly = SplitStringToVector(instruction, " ");
        assembly.push_back("0");
        auto cmd = assembly.at(0);
        instruction_to_action.at(cmd)(std::stoi(assembly.at(1)));
    }

    for (size_t i = 0; i < output.size(); i++) {
        if (i % 40 == 0) {
            std::cout << std::endl;
        }
        std::cout << output.at(i);
    }
    std::cout << std::endl;

    return 0;
}