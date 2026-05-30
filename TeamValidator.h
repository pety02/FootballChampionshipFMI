//
// Created by User on 5/16/2026.
//

#ifndef TEAMVALIDATOR_H
#define TEAMVALIDATOR_H

#include <vector>
#include "Player.h"

/**
*
*/
class TeamValidator final {
public:
    TeamValidator() = default;

    /**
    *
    */
    static void validateBudget(double budget);

    /**
    *
    */
    static void validateTeamSize(unsigned teamSize, unsigned maxTeamSize);

    /**
    *
    */
    static void validateRemainingBudget(double remainingBudget, const std::string& playerName);

    /**
    *
    */
    static void validatePlayerScoredGoals(Player::Position playerPosition, Player::Position targetPosition,
        unsigned scoredGoals, unsigned targetGoals, const std::string& playerName, const std::string& teamName);

    /**
    *
    */
    static void validatePlayersCountByPosition(std::vector<unsigned>& args, unsigned remainingPlaces, const std::string& exceptionMessage);
};

#endif //TEAMVALIDATOR_H