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
     * @param coachName The name of the team's coach.
     * @param stadiumName The name of the home stadium.
     * @param budget The initial budget of the team.
     */
    BalancedTeam(const std::string &name,
                 const std::string &coachName,
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

    /**
    * Outputs the state of a BalancedTeam object to an output stream.
    *
    * This function serializes the BalancedTeam instance into a structured format
    * suitable for display or persistence. The output includes all relevant team
    * attributes required to reconstruct the object later using the corresponding
    * input operator.
    *
    * @param os The output stream to write the team data to.
    * @param team The BalancedTeam instance to serialize.
    * @return Reference to the output stream to support chained output operations.
    */
    friend std::ostream &operator<<(std::ostream &os, const BalancedTeam &team);

    /**
     * Reads a BalancedTeam object from an input stream.
     *
     * This function deserializes a BalancedTeam instance from a previously
     * serialized format produced by operator<<. It reconstructs the internal
     * state of the team and assumes the input data is well-formed and follows
     * the expected structure.
     *
     * @param is The input stream to read the team data from.
     * @param team The BalancedTeam instance to populate.
     * @return Reference to the input stream to support chained input operations.
     */
    friend std::istream &operator>>(std::istream &is, BalancedTeam &team);
};

#endif //BALANCEDTEAM_H
