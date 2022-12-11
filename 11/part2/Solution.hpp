#pragma once

#include "_common/ISolution.hpp"
#include <functional>
#include <queue>
#include <string>
#include <vector>
class Solution : public ISolution {
private:
    class Monkey {
    private:
        std::queue<unsigned long long> items_;
        std::function<unsigned long long(unsigned long long)> operation_;
        std::function<int(unsigned long long)> test_;
        int inspection_count_;
        int id_;

    public:
        Monkey(int id, std::function<unsigned long long(unsigned long long)> operation,
               std::function<int(unsigned long long)> test)
            : operation_{operation}, test_{test}, inspection_count_{0}, id_{id} {}
        ~Monkey() {}
        void GiveItem(unsigned long long item) { items_.emplace(item); }
        unsigned long long RemoveItem() {
            auto item = items_.front();
            items_.pop();
            inspection_count_++;
            return item;
        }
        int GetInspectionCount() const { return inspection_count_; }
        int GetID() const { return id_; }
        bool HasItems() const { return !items_.empty(); }
        unsigned long long Operate(unsigned long long item) { return operation_(item); }
        int Test(unsigned long long item) { return test_(item); }
    };

    void ParseInput(const std::vector<std::string> &input);

    std::vector<Monkey> monkeys;

public:
    Solution(/* args */);
    ~Solution();

    int ComputeResult(const std::vector<std::string> &input) override;
};
