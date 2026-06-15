//
// Created by User on 5/16/2026.
//

#ifndef TEAMMANAGER_H
#define TEAMMANAGER_H
#include <vector>

#include "../Team.h"
#include "../../player/Player.h"
#include <string>

/**
*
*/
class TeamManager final {
private:
    std::string name;
    std::vector<Team*> teams;

public:
    TeamManager(const std::string& name, const std::vector<Team>& teams);
    ~TeamManager() = default;

    /**
    *
    */
    void addPlayerToTeam(const std::string& teamName, Player* player);

    void transfer(Player* firstPlayer, Team& firstTeam,
        Player* secondPlayer, Team& secondTeam);

    /**
    *
    */
    void registerMatchResult(Team* homeTeam, unsigned homeGoals, Team* guestTeam, unsigned guestGoals);

    /**
    *
    */
    void addTeam(Team* team);

    /**
    *
    */
    void removeTeam(const std::string& teamName);

    /**
    *
    */
    void setName(const std::string& name);

    /**
    *
    */
    [[nodiscard]] const std::string& getName() const;

    /**
    *
    */
    [[nodiscard]] std::vector<Team*>& getTeams();

    /**
    *
    */
    [[nodiscard]] const std::vector<Team*>& getTeams() const;
};

#endif //TEAMMANAGER_H