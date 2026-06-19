//
// Created by User on 6/19/2026.
//

#ifndef PLAYERENGINE_H
#define PLAYERENGINE_H

#include "../../model/player/Player.h"
#include "../../model/team/Team.h"
#include "../../model/championship/Championship.h"

class PlayerEngine {
public:
    static void addPlayer(const std::string& playerName, Lineup& lineup); // player engine
    static void addPlayer(Player& player, Team& team); // player engine

    static void removePlayer(const std::string& playerName, // player engine
                             Team& team);

    static void transferPlayers(Team& firstTeam, // player engine
                                Team& secondTeam);

    static void viewPlayer(const std::string& playerName, // player engine
                           const Championship& championship);

    static std::vector<Player> listPlayers(const Team& team); // player engine

    static void updateSalary(Championship& championship, // player engine
                             Player& player);
};

#endif //PLAYERENGINE_H
