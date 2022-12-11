#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <algorithm>
#include <vector>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

void Solution::ParseInput(const std::vector<std::string> &input) {
    int current_monkey = -1;
    std::vector<std::string> current_items;
    std::function<unsigned long long(unsigned long long)> current_operation;
    std::function<unsigned long long(unsigned long long)> current_test;
    char current_operation_operator;
    int current_operation_operand2;
    int current_test_val;
    int current_test_monkey1;
    int current_test_monkey2;
    auto test_template = [](unsigned long long item, unsigned long long test_val,
                            int monkey1, int monkey2) -> int {
        if (item % test_val == 0) {
            return monkey1;
        }
        return monkey2;
    };
    auto operation_template = [](unsigned long long item, char operator_,
                                 unsigned long long operand2) -> unsigned long long {
        switch (operator_) {
        case '*':
            return item * operand2;
            break;
        case '+':
            return item + operand2;
            break;
        case '*' + 2:
            return item * item;
            break;
        case '+' + 2:
            return item + item;
            break;
        default:
            return 0;
            break;
        }
    };

    for (auto line : input) {
        if (line.find("Monkey ") != std::string::npos) {
            if (current_monkey > -1) {
                current_test = [test_template, current_test_val, current_test_monkey1,
                                current_test_monkey2](int item) {
                    return test_template(item, current_test_val, current_test_monkey1,
                                         current_test_monkey2);
                };
                current_operation = [operation_template, current_operation_operator,
                                     current_operation_operand2](int item) {
                    return operation_template(item, current_operation_operator,
                                              current_operation_operand2);
                };
                monkeys.push_back(
                    Monkey(current_monkey, current_operation, current_test));
                for (auto item : current_items) {
                    monkeys.at(monkeys.size() - 1).GiveItem(std::stoi(item));
                }
            }

            current_monkey = line.at(7) - '0';
            continue;
        }
        auto info = SplitStringToVector(line, ": ");
        if (info.at(0).find("Starting items") != std::string::npos) {
            current_items = SplitStringToVector(info.at(1), ", ");
        } else if (info.at(0).find("Operation") !=
                   std::string::npos) { // E.G: "Operation: new = old * 19"
            std::string substr = "";
            if (info.at(1).find("+") != std::string::npos) {
                current_operation_operator = '+';
                substr = " + ";
            } else {
                current_operation_operator = '*';
                substr = " * ";
            }
            auto split_operation = SplitStringToVector(info.at(1), substr);
            if (split_operation.at(1) != "old") {
                current_operation_operand2 = std::stoi(split_operation.at(1));
            } else {
                current_operation_operator += 2;
            }
        } else if (info.at(0).find("Test") !=
                   std::string::npos) // E.G: "Test: divisible by 17"
        {
            auto words = SplitStringToVector(info.at(1), " ");
            current_test_val = std::stoi(words.at(2));
        } else if (info.at(0).find("If true") !=
                   std::string::npos) { // E.G: "If true: throw to monkey 0"
            current_test_monkey1 = info.at(1).at(16) - '0';
        } else if (info.at(0).find("If false") !=
                   std::string::npos) { // E.G: "If false: throw to monkey 1"
            current_test_monkey2 = info.at(1).at(16) - '0';
        }
    }

    if (current_monkey > -1) {
        current_test = [test_template, current_test_val, current_test_monkey1,
                        current_test_monkey2](int item) {
            return test_template(item, current_test_val, current_test_monkey1,
                                 current_test_monkey2);
        };
        current_operation = [operation_template, current_operation_operator,
                             current_operation_operand2](int item) {
            return operation_template(item, current_operation_operator,
                                      current_operation_operand2);
        };
        monkeys.push_back(Monkey(current_monkey, current_operation, current_test));
        for (auto item : current_items) {
            monkeys.at(monkeys.size() - 1).GiveItem(std::stoi(item));
        }
    }
}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    ParseInput(input);
    for (size_t i = 0; i < 10000; i++) {
        for (size_t j = 0; j < monkeys.size(); j++) {
            while (monkeys.at(j).HasItems()) {
                unsigned long long item = monkeys.at(j).RemoveItem();

                item = monkeys.at(j).Operate(item);
                item %= 9699690;
                auto dst_monkey = monkeys.at(j).Test(item);
                std::find_if(monkeys.begin(), monkeys.end(),
                             [&dst_monkey](Monkey &monkey) {
                                 return monkey.GetID() == dst_monkey;
                             })
                    ->GiveItem(item);
            }
        }
    }

    for (auto monkey : monkeys) {
        std::cout << monkey.GetInspectionCount() << std::endl;
    }
    return monkeys.at(0).GetInspectionCount();
}