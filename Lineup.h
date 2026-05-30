//
// Created by User on 5/14/2026.
//

#ifndef LINEUP_H
#define LINEUP_H
#include "Team.h"

/**
*
*/
class Lineup final {
private:
    Team* team;
    std::vector<Player*> players;

    std::vector<Player*> generateRandomLineup();
public:
    static constexpr unsigned LINEUP_SIZE = 11;

    explicit Lineup(Team* team);
    Lineup(const Lineup& other);
    Lineup& operator=(const Lineup& other);
    ~Lineup();

    /**
    *
    */
    void setTeam(Team* team);

    /**
    *
    */
    void addPlayer(Player* player);

    /**
    *
    */
    void removePlayer(const std::string& playerName);

    /**
    *
    */
    [[nodiscard]] const Team* getTeam() const;

    /**
    *
    */
    [[nodiscard]] const std::vector<Player*>& getPlayers() const;
};

#endif //LINEUP_H