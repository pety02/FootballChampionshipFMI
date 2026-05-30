//
// Created by User on 5/16/2026.
//

#include "TeamManager.h"
#include <stdexcept>

#include "Match.h"
#include "MatchResultApplier.h"
#include "StringValidator.h"
#include "TeamValidator.h"

TeamManager::TeamManager(const std::string &name, const std::vector<Team>& teams) : name(name) {
    StringValidator::validate(name, "Coach name cannot be empty.", "Coach name cannot be blank.");
    TeamValidator::validateTeamsCount(4, teams.size());

    for (const auto & team : teams) {
        this->teams.push_back(team.clone());
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

    TeamValidator::validateThatTeamsAreFound(this->teams, firstTeam, secondTeam);

    firstTeam.addPlayer(secondPlayer, true);
    secondTeam.addPlayer(firstPlayer, true);
}

void TeamManager::registerMatchResult(Team *homeTeam, unsigned homeGoals, Team *guestTeam, unsigned guestGoals) {
    TeamValidator::validateThatTeamsAreMangedByAManager(this->teams, homeTeam, guestTeam);

    Match::MatchResult result;
    result.home = homeTeam;
    result.guest = guestTeam;
    result.homeGoals = homeGoals;
    result.guestGoals = guestGoals;

    MatchResultApplier::apply(result);
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