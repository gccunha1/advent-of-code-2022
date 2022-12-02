#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <map>

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    std::map<std::string, std::string> winning_moves{{"X", "C"}, {"Y", "A"}, {"Z", "B"}};
    std::map<std::string, std::string> draw_moves{{"X", "A"}, {"Y", "B"}, {"Z", "C"}};
    std::map<std::string, int> move_scores{{"X", 1}, {"Y", 2}, {"Z", 3}};
    int score = 0;
    for (auto round : input) {
        auto player_moves = SplitStringToVector(round, " ");
        score += move_scores.at(player_moves[1]);
        if (player_moves[0] == draw_moves.at(player_moves[1])) {
            score += 3;
        } else if (player_moves[0] == winning_moves.at(player_moves[1])) {
            score += 6;
        }
    }
    return score;
}