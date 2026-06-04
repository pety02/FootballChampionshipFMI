//
// Created by User on 5/14/2026.
//

#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "../player/Player.h"

class TeamManager;

/**
*
*/
class Team {
public:
    /**
    *
    */
    struct Statistics {
        unsigned winsCount;
        unsigned drawsCount;
        unsigned lossesCount;
        unsigned scoredGoals;
        unsigned concededGoals;

        Statistics();

        /**
        *
        */
        void increaseWinsCount(unsigned wins);

        /**
        *
        */
        void increaseDrawsCount(unsigned draws);

        /**
        *
        */
        void increaseLossesCount(unsigned losses);

        /**
        *
        */
        void increaseScoredGoals(unsigned scoredGoals);

        /**
        *
        */
        void increaseConcededGoals(unsigned concededGoals);
    };

    static constexpr unsigned MAX_TEAM_SIZE = 20;

protected:
    std::string name;
    std::string stadiumName;
    std::vector<Player*> players;
    double budget = 0.0;
    Statistics stats;
    TeamManager* teamManager;
    unsigned forwardersCount;
    unsigned midfieldersCount;
    unsigned goalkeepersCount;
    unsigned defendersCount;
    unsigned wingersCount;

    /**
    *
    */
    void copy(const Team& other);

    /**
    *
    */
    void destroy();

public:
    Team();
    Team(const std::string& name, const std::string& coachName, std::string  stadiumName, double budget);
    Team(const Team& other);
    Team& operator=(const Team& other);
    virtual ~Team() noexcept;

    /**
    *
    */
    [[nodiscard]] virtual Team* clone() const = 0;

    /**
    *
    */
    void setTeamName(const std::string& name);

    /**
    *
    */
    void setStadiumName(const std::string& stadiumName);

    /**
    *
    */
    void setBudget(double budget);

    /**
    *
    */
    [[nodiscard]] const std::string& getName() const;

    /**
    *
    */
    [[nodiscard]] const std::string& getCoachName() const;

    /**
    *
    */
    [[nodiscard]] const std::string& getStadiumName() const;

    /**
    *
    */
    [[nodiscard]] const std::vector<Player*>& getPlayers() const;

    /**
    *
    */
    [[nodiscard]] double getBudget() const;

    /**
    *
    */
    [[nodiscard]] Statistics& getStats();

    virtual void addPlayer(Player* player, bool isTransfer) = 0;

    /**
    *
    */
    void buyPlayer(Player* player, Player::Position playerPos, double remainingBudget, bool isTransfer);
};

#endif //TEAM_H