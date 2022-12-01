#include "FileUtils.h"

std::ifstream OpenFileToRead(const std::string &filename) {
    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cout << filename << " does't exist!" << std::endl;
        exit(1);
    }
    return file;
}

std::vector<std::string> ReadFileToVector(const std::string &filename) {
    auto file = OpenFileToRead(filename);
    std::vector<std::string> lines{};
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}