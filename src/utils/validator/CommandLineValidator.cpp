//
// Created by User on 6/15/2026.
//

#include "CommandLineValidator.h"

#include "../ExceptionMessages.h"
#include <stdexcept>

void CommandLineValidator::validateGoalsCount(unsigned scoredGals, int totalScoredGoals) {
    if(scoredGals > totalScoredGoals) throw std::invalid_argument(toString(ExceptionMessages::SCORED_GOALS_CANNOT_BE_MORE_THAN_TOTAL_SCORED_GOALS));
}

bool CommandLineValidator::validateIsHomePlayer(const std::string& playerName, const Team& team) {
    for(const auto& player : team.getPlayers()) {
        if(player.getName() == playerName) {
            return true;
        }
    }

    return false;
}

bool CommandLineValidator::validateIsGuestPlayer(const std::string& playerName, const Team& team) {
    for(const auto& player : team.getPlayers()) {
        if(player.getName() == playerName) {
            return true;
        }
    }

    return false;
}

void CommandLineValidator::validateUniquePlayerName(const std::string& playerName, const Team& team) {
    for(const auto& player : team.getPlayers()) {
        if(player.getName() == playerName) {
            throw std::invalid_argument(toString(ExceptionMessages::THERE_IS_PLAYER_WITH_SAME_NAME));
        }
    }
}