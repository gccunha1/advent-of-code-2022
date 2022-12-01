#pragma once

#include <fstream>
#include <iostream>
#include <vector>

std::ifstream OpenFileToRead(const std::string &filename);
std::vector<std::string> ReadFileToVector(const std::string &filename);
