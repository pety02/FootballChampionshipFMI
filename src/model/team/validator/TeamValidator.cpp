//
// Created by User on 5/16/2026.
//

#include "../team/validator/TeamValidator.h"
#include <stdexcept>
#include "../../../utils/ExceptionMessages.h"

bool TeamValidator::isManaged(const Team* t, const std::vector<Team*>& teams)
{
    for (const Team* team : teams)
    {
        if (team->getName() == t->getName())
            return true;
    }

    return false;
}

void TeamValidator::validateBudget(double budget) {
    if(budget < 0.0)
        throw std::invalid_argument(toString(ExceptionMessages::BUDGET_SHOULD_BE_NON_NEGATIVE));
}

void TeamValidator::validateTeamSize(unsigned teamSize, unsigned maxTeamSize) {
    if (teamSize >= maxTeamSize) {
        throw std::invalid_argument(toString(ExceptionMessages::MAX_TEAM_SIZE_IS));
    }
}

void TeamValidator::validateRemainingBudget(double remainingBudget) {
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

void TeamValidator::validatePlayersCountByPosition(const std::vector<unsigned>& args, unsigned remainingPlaces, const std::string& exceptionMessage) {
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
    for(const Team* currTeam : teams) {
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
                                                         const Team *homeTeam, const Team *guestTeam) {

    if (!TeamValidator::isManaged(homeTeam, teams) || !TeamValidator::isManaged(guestTeam, teams)) {
        throw std::invalid_argument(toString(ExceptionMessages::TEAM_NOT_MANAGED_BY_THIS_MANAGER));
    }
}

void TeamValidator::validateUniquePlayerNumber(const Team& team, unsigned number) {
    for(const Player& player : team.getPlayers()) {
        if(player.getNumber() == number) {
            throw std::invalid_argument(toString(ExceptionMessages::NOT_UNIQUE_PLAYER_NUMBER));
        }
    }
}

void TeamValidator::validateUniquePlayerName(const Team& team, const std::string& name) {
    for(const Player& player : team.getPlayers()) {
        if(player.getName() == name) {
            throw std::invalid_argument(toString(ExceptionMessages::NOT_UNIQUE_PLAYER_NAME));
        }
    }
}