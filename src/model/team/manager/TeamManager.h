#ifndef TEAMMANAGER_H
#define TEAMMANAGER_H

#include <vector>
#include <string>
#include "../factory/TeamFactory.h"

class Team;

/**
 * Manages a collection of football teams and coordinates operations
 * involving teams and players.
 *
 * This class is responsible for maintaining the list of registered
 * teams, transferring players between teams, recording match results,
 * and performing team-related tasks.
 *
 * @note TeamManager owns the Team objects stored in its collection and
 * is responsible for releasing their memory upon destruction.
 */
class TeamManager final {
private:
    std::string name = std::string();

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
    TeamManager(const std::string& name, const std::vector<Team*>& teams);

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
     * @return Reference to the current object.
     */
    TeamManager& operator=(const TeamManager& other);

    /**
    * Move constructor. Transfers ownership of resources from another TeamManager.
    *
    * @param other The TeamManager to move from.
    */
    TeamManager(TeamManager&& other) noexcept;

    /**
    * Move assignment operator. Transfers resources from another TeamManager into this one.
    *
    * @param other The TeamManager to move from.
    * @return Reference to the assigned TeamManager.
    */
    TeamManager& operator=(TeamManager&& other) noexcept;

    /**
     * Destroys the team manager and releases all owned teams.
     */
    ~TeamManager() noexcept;

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

    /**
     * Outputs the team manager and its managed teams to a stream in a formatted representation.
     *
     * @param os The output stream.
     * @param teamManager The team manager to output.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const TeamManager& teamManager);

    /**
     * Reads a team manager and its configuration from a stream.
     *
     * @param is The input stream.
     * @param tm The team manager to populate.
     * @return Reference to the input stream.
     */
    friend std::istream& operator>>(std::istream& is, TeamManager& tm);
};

#endif //TEAMMANAGER_H