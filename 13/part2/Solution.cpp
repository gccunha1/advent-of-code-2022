#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <functional>
#include <memory>
#include <optional>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

enum class Comparison { kHigher = 0, kLower, kNeutral };

struct Element {
    std::optional<int> value = std::nullopt;
    std::vector<std::shared_ptr<Element>> children;
    std::string raw_text = "";

    bool IsEmpty() const { return !value.has_value() && (children.size() == 0); }
    Element(){};
    Element(const int v, const std::string text) : value{v}, raw_text{text} {};
};

std::string RemoveNextElement(std::string &line) {
    std::string ret_str;
    // std::cout << "Removing element" << std::endl;
    if (line.at(0) == '[') {
        int bracket_count = 1;
        size_t i = 1;
        for (i = 1; (i < line.length()) && (bracket_count != 0); i++) {
            if (line.at(i) == '[') {
                bracket_count++;
            } else if (line.at(i) == ']') {
                bracket_count--;
            }
        }
        if (i == line.length()) {
            ret_str = line;
            line = "";
            return ret_str;
        }
        ret_str = std::string{line.begin(), line.begin() + i};
        line = std::string{line.begin() + i + 1, line.end()};
        return ret_str;
    }

    auto comma_pos = line.find(",");
    if (comma_pos == std::string::npos) {
        ret_str = line;
        line = "";
        return ret_str;
    }
    ret_str = std::string{line.begin(), line.begin() + comma_pos};
    line = std::string{line.begin() + comma_pos + 1, line.end()};
    return ret_str;
}

std::shared_ptr<Element> ParsePairElement(const std::string &line) {
    std::shared_ptr<Element> element = std::make_shared<Element>();
    element->raw_text = line;
    std::string children{line.begin() + 1, line.end() - 1};
    // std::cout << children << std::endl;
    if (children.length() == 0) {
        // std::cout << "empty element" << std::endl;
        return element;
    }
    if ((children.find(',') == std::string::npos) &&
        (children.find('[') == std::string::npos) &&
        (children.find(']') == std::string::npos)) {

        element->value.emplace(std::stoi(children));
        // std::cout << "simple nr: " << children << std::endl;
        return element;
    } else {
        // std::cout << "complex: " << children << std::endl;
        while (children.length() > 0) {
            auto str_element = RemoveNextElement(children);
            if ((str_element.find(',') == std::string::npos) &&
                (str_element.find('[') == std::string::npos) &&
                (str_element.find(']') == std::string::npos)) {
                str_element = "[" + str_element + "]";
            }
            auto child = ParsePairElement(str_element);
            element->children.push_back(child);
            // std::cout << children << std::endl;
            // std::cout << children.length() << std::endl;
        }
    }

    return element;
}

Comparison PairsInRightOrder(const std::shared_ptr<Element> element1,
                             const std::shared_ptr<Element> element2) {
    std::cout << "Comparing: " << element1->raw_text << " and " << element2->raw_text
              << std::endl;
    if (element1->IsEmpty() && !element2->IsEmpty()) {
        return Comparison::kLower;
    } else if (!element1->IsEmpty() && element2->IsEmpty()) {
        return Comparison::kHigher;
    } else if (element1->IsEmpty() && element2->IsEmpty()) {
        return Comparison::kNeutral;
    }

    if (element1->value.has_value() && element2->value.has_value()) {
        if (element1->value.value() < element2->value.value()) {
            return Comparison::kLower;
        } else if (element1->value.value() > element2->value.value()) {
            return Comparison::kHigher;
        } else {
            return Comparison::kNeutral;
        }
    }

    if (!element2->value.has_value() && element1->value.has_value()) {
        element1->children.push_back(std::make_shared<Element>(
            element1->value.value(), std::to_string(element1->value.value())));
        element1->raw_text = "[" + std::to_string(element1->value.value()) + "]";
        element1->value = std::nullopt;
    } else if (!element1->value.has_value() && element2->value.has_value()) {
        element2->children.push_back(std::make_shared<Element>(
            element2->value.value(), std::to_string(element2->value.value())));
        element2->raw_text = "[" + std::to_string(element2->value.value()) + "]";
        element2->value = std::nullopt;
    }

    auto min_size = std::min(element1->children.size(), element2->children.size());
    for (size_t i = 0; i < min_size; i++) {
        auto child1 = element1->children.at(i);
        auto child2 = element2->children.at(i);
        auto ret = PairsInRightOrder(child1, child2);
        if (ret == Comparison::kNeutral) {
            continue;
        }
        return ret;
    }
    if (element1->children.size() < element2->children.size()) {
        return Comparison::kLower;
    } else if (element1->children.size() > element2->children.size()) {
        return Comparison::kHigher;
    }

    return Comparison::kNeutral;
}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    std::vector<std::shared_ptr<Element>> elements;
    for (auto &line : input) {
        if (line.length() == 0) {
            continue;
        }
        auto element = ParsePairElement(line);
        elements.push_back(element);
        for (size_t i = 0; i < elements.size() - 1; i++) {
            if (PairsInRightOrder(elements.at(elements.size() - i - 2),
                                  elements.at(elements.size() - i - 1)) ==
                Comparison::kHigher) {
                std::swap(elements.at(elements.size() - i - 2),
                          elements.at(elements.size() - i - 1));
            } else {
                break;
            }
        }
    }
    auto element = ParsePairElement("[[2]]");
    elements.push_back(element);
    for (size_t i = 0; i < elements.size() - 1; i++) {
        if (PairsInRightOrder(elements.at(elements.size() - i - 2),
                              elements.at(elements.size() - i - 1)) ==
            Comparison::kHigher) {
            std::swap(elements.at(elements.size() - i - 2),
                      elements.at(elements.size() - i - 1));
        } else {
            break;
        }
    }
    element = ParsePairElement("[[6]]");
    elements.push_back(element);
    for (size_t i = 0; i < elements.size() - 1; i++) {
        if (PairsInRightOrder(elements.at(elements.size() - i - 2),
                              elements.at(elements.size() - i - 1)) ==
            Comparison::kHigher) {
            std::swap(elements.at(elements.size() - i - 2),
                      elements.at(elements.size() - i - 1));
        } else {
            break;
        }
    }
    int cnt = 0;
    int ret = 1;
    for (auto el : elements) {
        cnt++;
        if (el->raw_text == "[[2]]" || el->raw_text == "[[6]]") {
            ret *= cnt;
        }
        std::cout << el->raw_text << std::endl;
    }

    return ret;
}