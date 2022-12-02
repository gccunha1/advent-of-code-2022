#pragma once

#include "_common/ISolution.hpp"
#include <string>
#include <vector>
class Solution : public ISolution {
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

    int ComputeResult(const std::vector<std::string> &input) override;
};
