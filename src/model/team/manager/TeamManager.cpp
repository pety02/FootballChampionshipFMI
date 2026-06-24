#include "../team/manager/TeamManager.h"
#include <stdexcept>
#include "../../match/Match.h"
#include "../../utils/Utils.h"
#include "../../../utils/ExceptionMessages.h"
#include "../../../utils/validator/StringValidator.h"
#include "../../team/validator/TeamValidator.h"

TeamManager::TeamManager(const std::string &name, const std::vector<Team*>& teams)
    : name(name)
{
    StringValidator::validate(
        name,
        toString(ExceptionMessages::COACH_NAME_CANNOT_BE_EMPTY),
        toString(ExceptionMessages::COACH_NAME_CANNOT_BE_BLANK)
    );

    TeamValidator::validateTeamsCount(4, teams.size());

    for (Team* team : teams)
    {
        Team* cloned = nullptr;
        try
        {
            cloned = team->clone();
            this->teams.push_back(cloned);
        }
        catch (...)
        {
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

    std::vector<Team*> newTeams;

    try
    {
        for (Team* t : other.teams)
            newTeams.push_back(t->clone());
    }
    catch (...)
    {
        for (Team* t : newTeams)
            delete t;
        throw;
    }

    for (Team* t : teams)
        delete t;

    teams = std::move(newTeams);
    name = other.name;

    return *this;
}

TeamManager::TeamManager(TeamManager&& other) noexcept
    : name(std::move(other.name)),
      teams(std::move(other.teams))
{
    other.teams.clear();
}

TeamManager& TeamManager::operator=(TeamManager&& other) noexcept
{
    if (this == &other)
        return *this;

    for (Team* t : teams)
        delete t;

    teams = std::move(other.teams);
    name = std::move(other.name);

    other.teams.clear();

    return *this;
}

TeamManager::~TeamManager() noexcept
{
    for (Team* team : teams)
        delete team;
}

void TeamManager::addTeam(Team* team) {
    this->teams.push_back(team);
}

void TeamManager::removeTeam(const std::string& teamName)
{
    for (std::vector<Team*>::iterator it = teams.begin(); it != teams.end(); ++it)
    {
        if ((*it)->getName() == teamName)
        {
            delete *it;
            teams.erase(it);
            return;
        }
    }

    throw std::invalid_argument(
        toString(ExceptionMessages::TEAM_WITH_A_NAME_CANNOT_BE_FOUND)
    );
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

std::ostream& operator<<(std::ostream& os, const TeamManager& teamManager)
{
    os << teamManager.getName() << '\n' << teamManager.getTeams().size() << '\n';
    for(const Team* team : teamManager.getTeams()) {
        os << team << '\n';
    }

    return os;
}

std::istream& operator>>(std::istream& is, TeamManager& tm)
{
    std::string managerName;
    size_t teamCount;

    is >> std::ws;
    char ch = is.peek();
    if(ch == EOF) {
        throw std::invalid_argument(toString(ExceptionMessages::CANNOT_READ_TEAM_MANAGER));
    }
    while(ch != '\n' || ch != EOF) {
        ch = is.peek();
        if(ch == EOF) {
            throw std::invalid_argument(toString(ExceptionMessages::CANNOT_READ_TEAM_MANAGER));
        }
    }
    std::getline(is, managerName);
    is >> teamCount;

    std::vector<Team*> tempTeams;

    for(size_t i=0;i<teamCount;i++)
    {
        std::string typeStr;
        std::getline(is >> std::ws, typeStr);

        TeamType type =
            Utils::parseTeamType(typeStr);

        Team* team =
            TeamFactory::createEmptyTeam(type);

        is >> *team;

        tempTeams.push_back(team);
    }

    try {
        TeamManager temp = TeamManager(managerName, tempTeams);
        tm = temp;
    } catch (...) {
        throw;
    }

    return is;
}