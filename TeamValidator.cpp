//
// Created by User on 5/16/2026.
//

#include "TeamValidator.h"
#include <stdexcept>

void TeamValidator::validateBudget(double budget) {
    if(budget < 0.0)
        throw std::invalid_argument("Budget should be non-negative.");
}

void TeamValidator::validateTeamSize(unsigned teamSize, unsigned maxTeamSize) {
    if (teamSize >= maxTeamSize) {
        throw std::invalid_argument("Max team size is " + std::to_string(maxTeamSize) + ".");
    }
}

void TeamValidator::validateRemainingBudget(double remainingBudget, const std::string& playerName) {
    if (remainingBudget < 0.0) {
        throw std::invalid_argument("Not enough budget for player " + playerName + "' transfer.");
    }
}

void TeamValidator::validatePlayerScoredGoals(Player::Position playerPosition, Player::Position targetPosition,
    unsigned scoredGoals, unsigned targetGoals, const std::string& playerName, const std::string& teamName) {
    if (playerPosition == targetPosition && scoredGoals < targetGoals) {
        throw std::invalid_argument("Player " + playerName + " cannot be added in the " + teamName +
                                    " team because he/she has less than " + std::to_string(targetGoals) + " scored goals.");
    }
}

void TeamValidator::validatePlayersCountByPosition(std::vector<unsigned>& args, unsigned remainingPlaces, const std::string& exceptionMessage) {
    if (args[0] + args[1] + args[2] + args[3] > remainingPlaces) {
        throw std::invalid_argument(exceptionMessage);
    }
}
