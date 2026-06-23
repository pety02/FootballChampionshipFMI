//
// Created by User on 5/14/2026.
//

#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include "manager/TeamManager.h"

#include "TeamType.h"

class TeamManager;

#include "../player/Player.h"

/**
 * Base class representing a football team.
 *
 * This class defines the core properties and behavior shared by all
 * team types (Attacking, Defensive, Balanced, etc.).
 *
 * It manages players, financial data, and match statistics.
 *
 * Derived classes must implement specific behavior for player
 * management and formation rules.
 */
class Team {
public:
    const static unsigned MAX_FORWARDERS = 8;
    const static unsigned MAX_MIDFIELDERS = 2;
    const static unsigned MAX_GOALKEEPERS = 2;
    const static unsigned MAX_DEFENDERS = 2;
    const static unsigned MAX_WINGERS = 2;

     /**
     * Represents statistical performance of a team.
     */
    struct Statistics {
        unsigned winsCount = 0;
        unsigned drawsCount = 0;
        unsigned lossesCount = 0;
        unsigned scoredGoals = 0;
        unsigned concededGoals = 0;

        /**
         * Initializes all statistics to zero.
         */
        Statistics();

        /**
         * Increases the number of wins by a given value.
         */
        void increaseWinsCount(unsigned wins);

        /**
         * Increases the number of draws by a given value.
         */
        void increaseDrawsCount(unsigned draws);

        /**
         * Increases the number of losses by a given value.
         */
        void increaseLossesCount(unsigned losses);

        /**
         * Increases the number of goals scored.
         */
        void increaseScoredGoals(unsigned scoredGoals);

        /**
         * Increases the number of goals conceded.
         */
        void increaseConcededGoals(unsigned concededGoals);

        friend std::ostream &operator<<(std::ostream &os, const Statistics &stats) {
            os << stats.concededGoals << ' '
                    << stats.scoredGoals << ' '
                    << stats.drawsCount << ' '
                    << stats.winsCount << ' '
                    << stats.lossesCount;

            return os;
        }

        friend std::istream &operator>>(std::istream &is, Statistics &stats) {
            unsigned concededGoals, scoredGoals, drawsCount, winsCount, lossesCount;
            is >> concededGoals >> scoredGoals >> drawsCount >> winsCount >> lossesCount;

            stats.concededGoals = concededGoals;
            stats.scoredGoals = scoredGoals;
            stats.drawsCount = drawsCount;
            stats.winsCount = winsCount;
            stats.lossesCount = lossesCount;

            return is;
        }
    };

    /**
     * Maximum number of players allowed in a team.
     */
    static constexpr unsigned MAX_TEAM_SIZE = 20;

protected:
    TeamType type = TeamType::UNKNOWN;
    std::string name = std::string();
    std::string stadiumName = std::string();
    std::vector<Player> players = std::vector<Player>();

    double budget = 0.0;
    Statistics stats = Statistics();
    TeamManager *teamManager = nullptr;

    unsigned forwardersCount = 0;
    unsigned midfieldersCount = 0;
    unsigned goalkeepersCount = 0;
    unsigned defendersCount = 0;
    unsigned wingersCount = 0;

    Team(TeamType type,
         const std::string &name,
         const std::string &stadiumName,
         const std::vector<Player> &players,
         double budget,
         const Statistics &stats,
         unsigned forwardersCount,
         unsigned midfieldersCount,
         unsigned goalkeepersCount,
         unsigned defendersCount,
         unsigned wingersCount);

public:
    /**
     * Default constructor.
     */
    Team();

    /**
     * Constructs a team with basic information.
     *
     * @param type
     * @param name The team name.
     * @param stadiumName The stadium name.
     * @param budget The initial budget.
     */
    Team(TeamType type,
         const std::string &name,
         const std::string &stadiumName,
         double budget);

    /**
     * Copy constructor.
     *
     * Performs a deep copy of all team resources.
     */
    Team(const Team &other);

    Team(Team &&other) noexcept;

    /**
     * Copy assignment operator.
     */
    Team &operator=(const Team &other) = delete;

    Team &operator=(Team &&other) noexcept;

    /**
     * Virtual destructor.
     *
     * Ensures proper cleanup of derived classes.
     */
    virtual ~Team() noexcept;

    /**
     * Creates a polymorphic copy of the team.
     *
     * @return Pointer to a newly allocated copy of the team.
     *
     * @note Caller is responsible for deleting the returned object.
     */
    [[nodiscard]] virtual Team *clone() const = 0;

    /**
     * Gets the team name.
     *
     * @return Constant reference to the team name.
     */
    [[nodiscard]] const std::string &getName() const;

    /**
     * Gets all players in the team.
     *
     * @return Constant reference to the player list.
     */
    [[nodiscard]] const std::vector<Player> &getPlayers() const;

    /**
     * Gets mutable access to team statistics.
     *
     * @return Reference to team statistics.
     */
    [[nodiscard]] Statistics &getStats();

    /**
     * Adds a player to the team (team-type specific rules apply).
     *
     * @param player Player to add.
     * @param isTransfer True if added via transfer, false otherwise.
     */
    virtual void addPlayer(Player &player, bool isTransfer) = 0;

    /**
     * Buys a player for the team.
     *
     * @param player Player to buy.
     * @param playerPos Player position.
     * @param remainingBudget Current available budget.
     * @param isTransfer Whether this operation is part of a transfer.
     */
    void buyPlayer(Player &player,
                   Player::Position playerPos,
                   double remainingBudget,
                   bool isTransfer);

    /**
     * Removes a player from the team.
     *
     * @param playerName Name of the player to remove.
     *
     * @throws std::invalid_argument If player is not found.
     */
    void removePlayer(const std::string &playerName);

    void setTeamManager(const TeamManager &teamManager);

    /**
    * Serializes a Team object to an output stream.
    *
    * This function writes the full state of the Team in a structured format
    * suitable for persistence. The output includes the team type, basic
    * identification data, financial information, statistical data, positional
    * counts, and all players belonging to the team.
    *
    * Each field is written on a separate line, and the players are serialized
    * using their own stream insertion operator.
    *
    * @param os The output stream to write the team data to.
    * @param team The Team object to serialize.
    * @return Reference to the output stream to allow chained output operations.
    */
    friend std::ostream &operator<<(std::ostream &os, const Team &team);

    /**
    * Deserializes a Team object from an input stream.
    *
    * This function reconstructs a Team instance from a previously serialized
    * representation produced by operator<<. It reads structured data in a strict
    * order and restores the full internal state of the team, including all
    * players.
    *
    * The function assumes the input format is valid and correctly ordered.
    * Player objects are reconstructed using their own extraction operator.
    *
    * @param is The input stream to read the team data from.
    * @param team The Team object to populate.
    * @return Reference to the input stream to allow chained input operations.
    */
    friend std::istream &operator>>(std::istream &is, Team &team);
};

#endif //TEAM_H
