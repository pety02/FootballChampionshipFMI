//
// Created by User on 5/14/2026.
//

#ifndef BALANCEDTEAM_H
#define BALANCEDTEAM_H

#include "Team.h"
#include <string>

/**
 * Represents a team with a balanced play style.
 *
 * Balanced teams aim to maintain equal strength across all positions
 * including defense, midfield, attack, and wings.
 */
class BalancedTeam final : public Team {
protected:
    BalancedTeam(TeamType type,
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
     * Required number of goalkeepers in the team.
     */
    static constexpr unsigned REQUIRED_GOALKEEPERS = 2;

    /**
     * Minimum number of forward players required.
     */
    static constexpr unsigned MIN_FORWARDERS_REQUIRED = 4;

    /**
     * Minimum number of defenders required.
     */
    static constexpr unsigned MIN_DEFENDERS_REQUIRED = 4;

    /**
     * Minimum number of midfielders required.
     */
    static constexpr unsigned MIN_MIDFIELDERS_REQUIRED = 4;

    /**
     * Minimum number of wingers required.
     */
    static constexpr unsigned MIN_WINGERS_REQUIRED = 4;

    /**
     * Default constructor.
     *
     * Creates a balanced team with default values.
     */
    BalancedTeam();

    /**
     * Constructs a balanced team with full configuration.
     *
     * @param name The name of the team.
     * @param stadiumName The name of the home stadium.
     * @param budget The initial budget of the team.
     */
    BalancedTeam(const std::string &name,
                 const std::string &stadiumName,
                 double budget);

    /**
     * Copy constructor.
     *
     * @param other The balanced team to copy.
     */
    BalancedTeam(const BalancedTeam &other);

    /**
     * Copy assignment operator.
     *
     * @param other The balanced team to assign from.
     * @return Reference to the current object.
     */
    BalancedTeam &operator=(const BalancedTeam &other);

    BalancedTeam(BalancedTeam &&other) noexcept;

    BalancedTeam &operator=(BalancedTeam &&other) noexcept;

    /**
     * Destructor.
     */
    ~BalancedTeam() noexcept override = default;

    /**
     * Creates a polymorphic copy of the team.
     *
     * @return Pointer to a newly allocated copy of this team.
     *
     * @note The caller is responsible for deleting the returned object.
     */
    [[nodiscard]] Team *clone() const override;

    /**
     * Adds a player to the team using balanced-team rules.
     *
     * This method enforces constraints to ensure balanced distribution
     * across all player positions.
     *
     * @param player The player to add.
     * @param isTransfer Indicates whether the player is added via transfer.
     */
    void addPlayer(Player &player, bool isTransfer) override;
};

#endif //BALANCEDTEAM_H