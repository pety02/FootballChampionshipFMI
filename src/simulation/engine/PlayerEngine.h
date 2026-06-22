//
// Created by User on 6/19/2026.
//

#ifndef PLAYERENGINE_H
#define PLAYERENGINE_H

#include "../../model/player/Player.h"
#include "../../model/championship/Championship.h"

class PlayerEngine {
public:
    /**
    * Adds a player to a team after validating uniqueness constraints.
    *
    * Ensures that the player name is not already used within the team
    * before adding the player.
    *
    * @param player The player to add.
    * @param team The team receiving the player.
    */
    static void addPlayer(Player &player, Team &team);

    /**
    * Removes a player from a team by name.
    *
    * @param playerName The name of the player to remove.
    * @param team The team from which the player will be removed.
    */
    static void removePlayer(const std::string &playerName,
                             Team &team);

    /**
     * Interactively transfers players between two teams.
     *
     * The function asks for player names from both teams, locates them,
     * removes them from their current teams, and swaps them.
     *
     * @param firstTeam The first team involved in the transfer.
     * @param secondTeam The second team involved in the transfer.
     */
    static void transferPlayers(Team &firstTeam,
                                Team &secondTeam);

    /**
    * Displays detailed information about a player within a championship.
    *
    * The function searches all teams in the championship and prints the
    * full player profile once found.
    *
    * @param playerName The name of the player to display.
    * @param championship The championship context in which to search.
    */
    static void viewPlayer(const std::string &playerName,
                           const Championship &championship);

    /**
    * Returns all players belonging to a given team.
    *
    * @param team The team whose players are requested.
    * @return Vector of players.
    */
    static std::vector<Player> listPlayers(const Team &team);

    /**
    * Updates a player's salary based on their participation in a championship.
    *
    * The function determines the team the player belongs to by checking match
    * participation and then delegates salary regulation to the accounting system.
    *
    * @param championship The championship context.
    * @param player The player whose salary will be updated.
    */
    static void updateSalary(Championship &championship,
                             Player &player);
};

#endif //PLAYERENGINE_H