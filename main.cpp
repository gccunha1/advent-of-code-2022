#include "solutions.h"

#include <iostream>

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        std::cout << "Input file missing as arg" << std::endl;
        exit(1);
    }

    Solution solution{};
    std::cout << "Result: " << (solution.Run(argv[1])) << std::endl;
    return 0;
}
