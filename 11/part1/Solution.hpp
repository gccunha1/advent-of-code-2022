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
        std::queue<int> items_;
        std::function<int(int)> operation_;
        std::function<int(int)> test_;
        int inspection_count_;
        int id_;

    public:
        Monkey(int id, std::function<int(int)> operation, std::function<int(int)> test)
            : operation_{operation}, test_{test}, inspection_count_{0}, id_{id} {}
        ~Monkey() {}
        void GiveItem(int item) { items_.emplace(item); }
        int RemoveItem() {
            auto item = items_.front();
            items_.pop();
            inspection_count_++;
            return item;
        }
        int GetInspectionCount() const { return inspection_count_; }
        int GetID() const { return id_; }
        bool HasItems() const { return !items_.empty(); }
        int Operate(int item) { return operation_(item); }
        int Test(int item) { return test_(item); }
    };

    void ParseInput(const std::vector<std::string> &input);

    std::vector<Monkey> monkeys;

public:
    Solution(/* args */);
    ~Solution();

    int ComputeResult(const std::vector<std::string> &input) override;
};
