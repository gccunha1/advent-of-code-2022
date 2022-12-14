#pragma once

#include "_common/ISolution.hpp"
#include <functional>
#include <queue>
#include <string>
#include <vector>
class Solution : public ISolution {
private:
public:
    Solution(/* args */);
    ~Solution();

    int ComputeResult(const std::vector<std::string> &input) override;
};
