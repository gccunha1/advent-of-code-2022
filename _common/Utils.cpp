#include "Utils.h"

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

std::vector<std::string> SplitStringToVector(const std::string &str,
                                             const std::string delimiter) {
    std::string s = str;
    size_t pos = 0;
    std::string token;
    std::vector<std::string> return_vector{};
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        return_vector.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    return_vector.push_back(s);
    return return_vector;
}
