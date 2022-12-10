#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <functional>
#include <map>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    std::map<std::string, int> instruction_to_cycles{{"noop", 1}, {"addx", 2}};
    int cycle = 0;
    int rx = 1;
    int signal_strength = 0;
    auto increment_cycle = [&cycle, &signal_strength, &rx](int amount) {
        for (int i = 0; i < amount; i++) {
            cycle++;
            if (((cycle + 20) % 40) == 0) {
                signal_strength += (cycle * rx);
            }
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

    return signal_strength;
}