//
// Created by User on 5/16/2026.
//

#include "../team/manager/TeamManager.h"
#include <stdexcept>
#include "../../match/Match.h"
#include "../../../simulation/MatchResultApplier.h"
#include "../../../utils/ExceptionMessages.h"
#include "../../../utils/StringValidator.h"
#include "../../team/validator/TeamValidator.h"

TeamManager::TeamManager(const std::string &name, const std::vector<Team>& teams) : name(name) {
    StringValidator::validate(name, toString(ExceptionMessages::COACH_NAME_CANNOT_BE_EMPTY), toString(ExceptionMessages::COACH_NAME_CANNOT_BE_BLANK));
    TeamValidator::validateTeamsCount(4, teams.size());

    for (const auto & team : teams) {
        Team* cloned;
        try {
            cloned = team.clone();
            this->teams.push_back(cloned);
        } catch (...) {
            delete cloned;
            throw;
        }
    }
}

TeamManager::TeamManager(const TeamManager& other)
    : name(other.name)
{
    for (Team* t : other.teams)
    {
        teams.push_back(t->clone());
    }
}

TeamManager& TeamManager::operator=(const TeamManager& other)
{
    if (this == &other)
        return *this;

    for (Team* t : teams)
        delete t;

    teams.clear();

    name = other.name;

    for (Team* t : other.teams)
    {
        teams.push_back(t->clone());
    }

    return *this;
}

TeamManager::~TeamManager() {
    for (Team* team : this->teams) {
        delete team;
    }
}

void TeamManager::addPlayerToTeam(const std::string& teamName, Player* player) const {
    int teamIndex = 0;
    for(const auto &currTeam : teams) {
        if(currTeam->getName() == teamName) {
            this->teams[teamIndex]->addPlayer(*player, false);
            return;
        }
        teamIndex++;
    }

    throw std::invalid_argument(toString(ExceptionMessages::THE_PLAYER_CANNOT_BE_ADDED_TO_THE_TEAM));
}

void TeamManager::transfer(Player* firstPlayer, Team& firstTeam,
        Player* secondPlayer, Team& secondTeam) const {

    TeamValidator::validateThatTeamsAreFound(this->teams, firstTeam, secondTeam);

    firstTeam.addPlayer(*secondPlayer, true);
    secondTeam.addPlayer(*firstPlayer, true);
}

void TeamManager::registerMatchResult(Team *homeTeam, unsigned homeGoals, Team *guestTeam, unsigned guestGoals) const {
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

    throw std::invalid_argument(toString(ExceptionMessages::TEAM_WITH_A_NAME_CANNOT_BE_FOUND));
}

void TeamManager::setName(const std::string &name) {
    this->name = name;
}

const std::string & TeamManager::getName() const {
    return this->name;
}

std::vector<Team*>& TeamManager::getTeams() {
    return this->teams;
}

const std::vector<Team*>& TeamManager::getTeams() const {
    return this->teams;
}