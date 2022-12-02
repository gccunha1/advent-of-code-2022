#pragma once
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <string>
#include <vector>
class ISolution {
private:
    /* data */
public:
    ISolution(/* args */) {}
    virtual ~ISolution() {}
    virtual int ComputeResult(const std::vector<std::string> &input) { return 0; };
    std::vector<std::string> GetInput(const std::string &filename) {
        auto input = ReadFileToVector(filename);
        return input;
    }
    int Run(const std::string &input_file_name) {
        auto input = GetInput(input_file_name);
        return ComputeResult(input);
    }
};
