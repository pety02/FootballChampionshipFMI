#ifndef LINEUP_H
#define LINEUP_H

#include "../../team/Team.h"
#include "../../player/Player.h"
#include <vector>
#include <string>

/**
* A class that describes the lineups, formed by a team in the championships.
*/
class Lineup final {
private:
    Team* team = nullptr;
    std::vector<Player> players;

    /**
    * Generates a random valid lineup consisting of players from the given team.
    * The selection process respects internal constraints required for a legal lineup.
    *
    * @param team The team from which players are selected.
    * @return A vector containing a randomly generated valid lineup of players.
    */
    static std::vector<Player> generateRandomLineup(const Team& team);

    /**
    * Determines whether a player is eligible to be added to the current team's lineup.
    * The decision may depend on constraints such as uniqueness, team membership,
    * and positional or formation rules.
    *
    * @param player The player to evaluate for addition.
    * @param teamPlayersList The current list of players in the lineup.
    * @return true if the player can be added; false otherwise.
    */
    static bool canAdd(const Player& player, const std::vector<Player>& teamPlayersList);

    /**
    * Attempts to add a player to the lineup while enforcing formation constraints.
    * Updates positional counters if the player is successfully added.
    *
    * @param player The player to be added.
    * @param teamPlayersList The current lineup being constructed.
    * @param gk Counter for goalkeepers.
    * @param def Counter for defenders.
    * @param mid Counter for midfielders.
    * @param wing Counter for wingers.
    * @param fwd Counter for forwards.
    *
    * @return true if the player was successfully added; false otherwise.
    */
    static bool tryAdd(const Player& player, std::vector<Player>& teamPlayersList,
        int& gk, int& def, int& mid, int& wing, int& fwd);

public:
    static constexpr unsigned LINEUP_SIZE = 11;

    /**
    * Default constructor. Creates an empty lineup with no assigned team.
    */
    Lineup() = default;

    /**
    * Constructs a lineup associated with a specific team.
    *
    * @param team Pointer to the team that owns this lineup.
    */
    explicit Lineup(Team* team);

    /**
    * Copy constructor. Performs a deep or member-wise copy of the lineup.
    *
    * @param other The lineup to copy from.
    */
    Lineup(const Lineup& other);

    /**
    * Copy assignment operator. Copies the contents of another lineup into this one.
    *
    * @param other The lineup to copy from.
    * @return Reference to the assigned lineup.
    */
    Lineup& operator=(const Lineup& other);

    /**
    * Move constructor. Transfers ownership of resources from another lineup.
    *
    * @param other The lineup to move from.
    */
    Lineup(Lineup&& other) noexcept;

    /**
    * Move assignment operator. Transfers resources from another lineup into this one.
    *
    * @param other The lineup to move from.
    * @return Reference to the assigned lineup.
    */
    Lineup& operator=(Lineup&& other) noexcept;

    /**
    * Destructor. Cleans up resources used by the lineup.
    */
    ~Lineup();

    /**
    * Assigns a team to this lineup.
    *
    * @param team Pointer to the team to associate with this lineup.
    */
    void setTeam(Team* team);

    /**
    * Adds a player to the lineup if they satisfy the required constraints.
    *
    * @param player The player to add.
    */
    void addPlayer(const Player& player);

    /**
    * Checks whether the lineup is valid according to formation rules and constraints.
    *
    * @return true if the lineup is valid; false otherwise.
    */
    [[nodiscard]] static bool isValid(const std::vector<Player>& players);

    /**
    * Removes a player from the lineup by name, if present.
    *
    * @param playerName The name of the player to remove.
    */
    void removePlayer(const std::string& playerName);

    /**
    * Retrieves the team associated with this lineup.
    *
    * @return Const pointer to the team.
    */
    [[nodiscard]] const Team* getTeam() const;

    /**
    * Retrieves the list of players currently in the lineup.
    *
    * @return Const reference to the vector of players.
    */
    [[nodiscard]] const std::vector<Player>& getPlayers() const;

    /**
    * Outputs the lineup to an output stream in a formatted representation.
    *
    * @param os The output stream.
    * @param lineup The lineup to output.
    * @return Reference to the output stream.
    */
    friend std::ostream& operator<<(std::ostream& os, const Lineup& lineup);

    /**
    * Reads a lineup from an input stream.
    *
    * @param is The input stream.
    * @param lineup The lineup to populate from the stream.
    * @return Reference to the input stream.
    */
    friend std::istream& operator>>(std::istream& is, Lineup& lineup);
};

#endif // LINEUP_H