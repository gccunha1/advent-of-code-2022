#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <algorithm>
#include <array>
#include <climits>
#include <memory>
#include <queue>
#include <tuple>
#include <vector>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

struct Node {
    char height;
    int distance = INT_MAX;
    int line;
    int col;
    bool visited = false;
    std::shared_ptr<Node> prev = nullptr;

    bool operator<(const Node &node) const { return distance < node.distance; }
    bool operator>(const Node &node) const { return distance > node.distance; }
    bool operator==(const Node &node) const { return distance == node.distance; }
};

std::shared_ptr<Node>
GetMinDistanceNode(const std::vector<std::vector<std::shared_ptr<Node>>> nodes) {
    int min_d = INT_MAX;
    std::shared_ptr<Node> return_node = nullptr;
    for (auto &line : nodes) {
        for (auto &node : line) {
            if (!node->visited && node->distance < min_d) {
                min_d = node->distance;
                return_node = node;
            }
        }
    }
    return return_node;
}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    std::vector<std::vector<std::shared_ptr<Node>>> distances(input.size());

    auto cmp = [](std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
        return left->distance > right->distance;
    };
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>,
                        decltype(cmp)>
        distances_queue(cmp);
    std::array<std::tuple<int, int>, 4> possible_neighbors{
        std::tuple<int, int>{-1, 0}, std::tuple<int, int>{0, -1},
        std::tuple<int, int>{1, 0}, std::tuple<int, int>{0, 1}};

    int dest_line = 0;
    int dest_column = 0;

    for (int i = 0; i < distances.size(); i++) {
        distances.at(i).resize(input.at(0).length());
        for (int j = 0; j < distances.at(i).size(); j++) {
            distances.at(i).at(j) = std::make_shared<Node>();
            distances.at(i).at(j)->line = i;
            distances.at(i).at(j)->col = j;
            if (input.at(i).at(j) == 'S') {
                distances.at(i).at(j)->height = 'a';
                distances.at(i).at(j)->distance = 0;
                distances.at(i).at(j)->prev = nullptr;
                continue;
            } else if (input.at(i).at(j) == 'E') {
                distances.at(i).at(j)->height = 'z';
                dest_line = i;
                dest_column = j;
                continue;
            }
            distances.at(i).at(j)->height = input.at(i).at(j);
        }
    }

    for (auto &line : distances) {
        for (auto &node : line) {
            distances_queue.emplace(node);
        }
    }
    // distances.at(0).at(0)->distance = 2;
    while (true) {
        auto node = GetMinDistanceNode(distances);
        if (node == nullptr)
            break;
        node->visited = true;

        for (auto neighbor_direction : possible_neighbors) {
            int neighbor_line = std::get<0>(neighbor_direction) + node->line;
            int neighbor_column = std::get<1>(neighbor_direction) + node->col;
            if ((neighbor_line < 0) || (neighbor_column < 0) ||
                (neighbor_line >= distances.size()) ||
                (neighbor_column >= distances.at(0).size())) {
                continue;
            }
            auto neighbor_node = distances.at(neighbor_line).at(neighbor_column);
            if (neighbor_node->height - node->height > 1) {
                continue;
            }

            int dist = node->distance + 1;
            if (dist < neighbor_node->distance) {
                neighbor_node->distance = dist;
                neighbor_node->prev = node;
            }
        }
    }

    int cnt = 0;
    std::shared_ptr<Node> current_node = distances.at(dest_line).at(dest_column);
    while (current_node != nullptr) {
        if (current_node->height == 'a') {
            break;
        }
        // std::cout << current_node->height << std::endl;

        current_node = current_node->prev;
        cnt++;
    }
    return cnt;
}