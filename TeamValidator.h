//
// Created by User on 5/16/2026.
//

#ifndef TEAMVALIDATOR_H
#define TEAMVALIDATOR_H

#include <vector>
#include "Player.h"
#include "Team.h"

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

    static void validateTeamsCount(unsigned minTeamsCount, unsigned currentTeamsCount);

    static void validateThatTeamsAreFound(const std::vector<Team*>& teams, const Team& firstTeam, const Team& secondTeam);

    static void validateThatTeamsAreMangedByAManager(const std::vector<Team*>& teams, Team *homeTeam, Team *guestTeam);
};

#endif //TEAMVALIDATOR_H