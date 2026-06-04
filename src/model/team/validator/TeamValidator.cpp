//
// Created by User on 5/16/2026.
//

#include "../team/validator/TeamValidator.h"
#include <stdexcept>
#include "../../../utils/ExceptionMessages.h"

void TeamValidator::validateBudget(double budget) {
    if(budget < 0.0)
        throw std::invalid_argument(toString(ExceptionMessages::BUDGET_SHOULD_BE_NON_NEGATIVE));
}

void TeamValidator::validateTeamSize(unsigned teamSize, unsigned maxTeamSize) {
    if (teamSize >= maxTeamSize) {
        throw std::invalid_argument(toString(ExceptionMessages::MAX_TEAM_SIZE_IS));
    }
}

void TeamValidator::validateRemainingBudget(double remainingBudget, const std::string& playerName) {
    if (remainingBudget < 0.0) {
        throw std::invalid_argument(toString(ExceptionMessages::NOT_ENOUGH_BUDGET_FOR_PLAYER_TRANSFER));
    }
}

void TeamValidator::validatePlayerScoredGoals(Player::Position playerPosition, Player::Position targetPosition,
    unsigned scoredGoals, unsigned targetGoals, const std::string& playerName, const std::string& teamName) {
    if (playerPosition == targetPosition && scoredGoals < targetGoals) {
        throw std::invalid_argument(toString(ExceptionMessages::THE_PLAYER_CANNOT_BE_ADDED_TO_THE_TEAM));
    }
}

void TeamValidator::validatePlayersCountByPosition(std::vector<unsigned>& args, unsigned remainingPlaces, const std::string& exceptionMessage) {
    if (args[0] + args[1] + args[2] + args[3] > remainingPlaces) {
        throw std::invalid_argument(exceptionMessage);
    }
}

void TeamValidator::validateTeamsCount(unsigned minTeamsCount, unsigned currentTeamsCount) {
    if(currentTeamsCount < minTeamsCount || currentTeamsCount % 2 != 0)
        throw std::invalid_argument(toString(ExceptionMessages::INVALID_NUMBER_OF_TEAMS));
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
        throw std::invalid_argument(toString(ExceptionMessages::BOTH_TEAMS_CANNOT_BE_FOUND));
    }
    if(!firstTeamNameFound && secondTeamNameFound) {
        throw std::invalid_argument(toString(ExceptionMessages::TEAM_WITH_A_NAME_CANNOT_BE_FOUND));
    }
    if(firstTeamNameFound && !secondTeamNameFound) {
        throw std::invalid_argument(toString(ExceptionMessages::TEAM_WITH_A_NAME_CANNOT_BE_FOUND));
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
        throw std::invalid_argument(toString(ExceptionMessages::TEAM_NOT_MANAGED_BY_THIS_MANAGER));
    }
}