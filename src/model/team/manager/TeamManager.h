//
// Created by User on 5/16/2026.
//

#ifndef TEAMMANAGER_H
#define TEAMMANAGER_H

#include <vector>
#include <string>

#include "../Team.h"
#include "../../player/Player.h"

/**
 * Manages a collection of football teams and coordinates operations
 * involving teams and players.
 *
 * This class is responsible for maintaining the list of registered
 * teams, transferring players between teams, recording match results,
 * and performing team-related administrative tasks.
 *
 * @note TeamManager owns the Team objects stored in its collection and
 * is responsible for releasing their memory upon destruction.
 */
class TeamManager final {
private:
    std::string name = std::string();

    /**
     * Collection of managed teams.
     *
     * TeamManager assumes ownership of these pointers.
     */
    std::vector<Team*> teams = std::vector<Team*>();

public:
    /**
     * Constructs an empty team manager.
     */
    TeamManager() = default;

    /**
     * Constructs a team manager with the specified name and teams.
     *
     * @param name The name of the team manager.
     * @param teams The collection of teams to manage.
     */
    TeamManager(const std::string& name, const std::vector<Team>& teams);

    /**
     * Constructs a team manager as a copy of another manager.
     *
     * @param other The manager to copy.
     */
    TeamManager(const TeamManager& other);

    /**
     * Assigns another team manager to this instance.
     *
     * @param other The manager to assign from.
     *
     * @return Reference to the current object.
     */
    TeamManager& operator=(const TeamManager& other);

    /**
     * Destroys the team manager and releases all owned teams.
     */
    ~TeamManager();

    /**
     * Adds a player to the specified team.
     *
     * @param teamName The name of the team receiving the player.
     * @param player Pointer to the player to add.
     *
     * @throws std::invalid_argument If the team cannot be found
     * or the player cannot be added.
     */
    void addPlayerToTeam(const std::string& teamName,
                         Player* player) const;

    /**
     * Transfers players between two teams.
     *
     * The specified players are exchanged between the provided teams.
     *
     * @param firstPlayer Pointer to the first player.
     * @param firstTeam The first player's current team.
     * @param secondPlayer Pointer to the second player.
     * @param secondTeam The second player's current team.
     *
     * @throws std::invalid_argument If the transfer cannot be completed.
     */
    void transfer(Player* firstPlayer,
                  Team& firstTeam,
                  Player* secondPlayer,
                  Team& secondTeam) const;

    /**
     * Registers the result of a completed match.
     *
     * Updates the statistics of the participating teams according
     * to the provided score.
     *
     * @param homeTeam Pointer to the home team.
     * @param homeGoals Number of goals scored by the home team.
     * @param guestTeam Pointer to the guest team.
     * @param guestGoals Number of goals scored by the guest team.
     */
    void registerMatchResult(Team* homeTeam,
                             unsigned homeGoals,
                             Team* guestTeam,
                             unsigned guestGoals) const;

    /**
     * Adds a team to the manager.
     *
     * @param team Pointer to the team to register.
     *
     * @note Ownership of the provided team pointer is transferred
     * to TeamManager.
     */
    void addTeam(Team* team);

    /**
     * Removes a team from the manager.
     *
     * @param teamName The name of the team to remove.
     *
     * @throws std::invalid_argument If no team with the specified
     * name exists.
     */
    void removeTeam(const std::string& teamName);

    /**
     * Changes the manager's name.
     *
     * @param name The new name.
     */
    void setName(const std::string& name);

    /**
     * Gets the manager's name.
     *
     * @return Constant reference to the manager's name.
     */
    [[nodiscard]] const std::string& getName() const;

    /**
     * Provides mutable access to the managed teams.
     *
     * @return Reference to the collection of managed teams.
     */
    [[nodiscard]] std::vector<Team*>& getTeams();

    /**
     * Provides read-only access to the managed teams.
     *
     * @return Constant reference to the collection of managed teams.
     */
    [[nodiscard]] const std::vector<Team*>& getTeams() const;
};

#endif //TEAMMANAGER_H