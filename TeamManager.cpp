//
// Created by User on 5/16/2026.
//

#include "TeamManager.h"
#include <stdexcept>
#include "StringValidator.h"
#include "TeamValidator.h"

TeamManager::TeamManager(const std::string &name, const std::vector<Team>& teams) : name(name) {
    StringValidator::validate(name, "Coach name cannot be empty.", "Coach name cannot be blank.");
    if(teams.size() < 4 || teams.size() % 2 != 0) throw std::invalid_argument("Invalid number of teams. Teams should be minimum 4 and their count should be an even number.");

    for (int i = 0; i < teams.size(); ++i) {
        this->teams.push_back(teams[i].clone());
    }
}

void TeamManager::addPlayerToTeam(const std::string& teamName, Player* player) {
    int teamIndex = 0;
    for(const auto &currTeam : teams) {
        if(currTeam->getName() == teamName) {
            this->teams[teamIndex]->addPlayer(player, false);
            return;
        }
        teamIndex++;
    }

    throw std::invalid_argument("The player with the name " + player->getName() + " cannot be added to a team with name "
        + teamName + " because the current manager does not manages such a team.");
}

void TeamManager::transfer(Player* firstPlayer, Team& firstTeam,
        Player* secondPlayer, Team& secondTeam) {

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

    firstTeam.addPlayer(secondPlayer, true);
    secondTeam.addPlayer(firstPlayer, true);
}

// TODO: think how to represent a transfer of players between teams.
void TeamManager::removePlayerFromTeam(const std::string& firstTeamName, const std::string& firstPlayerName,
        const std::string& secondTeamName, const std::string& secondPlayerName) {

}

void TeamManager::registerMatchResult(Team *homeTeam, unsigned homeGoals, Team *guestTeam, unsigned guestGoals) {
    // TODO: export the validation in a helper validation method
    int toBeDeletedIndex = 0;
    bool isHomeTeamManagedByCurrentTeamManager = false, isGuestTeamManagedByCurrentTeamManager = false;

    for(const auto &currTeam : teams) {
        if(isHomeTeamManagedByCurrentTeamManager && isGuestTeamManagedByCurrentTeamManager) {
            break;
        }

        if(currTeam->getName() == homeTeam->getName()) {
            isHomeTeamManagedByCurrentTeamManager = true;
        } else if(currTeam->getName() == guestTeam->getName()) {
            isGuestTeamManagedByCurrentTeamManager = true;
        }
        toBeDeletedIndex++;
    }
    if(!isHomeTeamManagedByCurrentTeamManager || !isGuestTeamManagedByCurrentTeamManager) {
        throw std::invalid_argument("Any of the home and guest teams are not managed by the current team manager.");
    }


    Team::Statistics homeStats = homeTeam->getStats();
    Team::Statistics guestStats = guestTeam->getStats();

    homeStats.scoredGoals += homeGoals;
    homeStats.concededGoals += guestGoals;

    guestStats.scoredGoals += guestGoals;
    guestStats.concededGoals += homeGoals;

    if(homeGoals == guestGoals) {
        homeStats.drawsCount += 1;
        guestStats.drawsCount += 1;
    } else if (homeGoals < guestGoals) {
        homeStats.lossesCount += 1;
    } else {
        guestStats.lossesCount += 1;
    }
}

void TeamManager::addTeam(Team* team) {
    this->teams.push_back(team);
}

void TeamManager::removeTeam(const std::string& teamName) {
    int toBeDeletedIndex = 0;
    for(const auto &currTeam : teams) {
        if(currTeam->getName() == teamName) {
            this->teams.erase(this->teams.begin() + toBeDeletedIndex);
            return;
        }
        toBeDeletedIndex++;
    }

    throw std::invalid_argument("Team with a name " + teamName + " is not found.");
}

void TeamManager::setName(const std::string &name) {
    this->name = name;
}

const std::string & TeamManager::getName() const {
    return this->name;
}