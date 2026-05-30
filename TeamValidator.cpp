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

void TeamValidator::validateTeamsCount(unsigned minTeamsCount, unsigned currentTeamsCount) {
    if(currentTeamsCount < minTeamsCount || currentTeamsCount % 2 != 0)
        throw std::invalid_argument("Invalid number of teams. Teams should be minimum 4 and their count should be an even number.");
}

void TeamValidator::validateThatTeamsAreFound(const std::vector<Team*>& teams, const Team &firstTeam, const Team &secondTeam) {
    bool firstTeamNameFound = false, secondTeamNameFound = false;
    for(const auto &currTeam : teams) {
        if(firstTeamNameFound && secondTeamNameFound) {
            break;
        }
        if(currTeam->getName() == firstTeam.getName()) {
            firstTeamNameFound = true;
            continue;
        }
        if(currTeam->getName() == secondTeam.getName()) {
            secondTeamNameFound = true;
        }
    }

    if(!firstTeamNameFound && !secondTeamNameFound) {
        throw std::invalid_argument("Both teams " + firstTeam.getName() + " and " + secondTeam.getName() + " cannot be found.");
    }
    if(!firstTeamNameFound && secondTeamNameFound) {
        throw std::invalid_argument("A team with a name " + firstTeam.getName() + " cannot be found.");
    }
    if(firstTeamNameFound && !secondTeamNameFound) {
        throw std::invalid_argument("A team with a name " + secondTeam.getName() + " cannot be found.");
    }
}

void TeamValidator::validateThatTeamsAreMangedByAManager(const std::vector<Team *> &teams,
    Team *homeTeam, Team *guestTeam) {

    auto isManaged = [&](Team* t) {
        bool isManaged = false;

        for (const auto& managed : teams) {
            if (managed->getName() == t->getName()) {
                isManaged = true;
                break;
            }
        }
        return isManaged;
    };

    if (!isManaged(homeTeam) || !isManaged(guestTeam)) {
        throw std::invalid_argument("Team not managed by this manager.");
    }
}