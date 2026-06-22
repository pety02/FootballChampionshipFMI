//
// Created by User on 5/14/2026.
//

#ifndef ATTACKINGTEAM_H
#define ATTACKINGTEAM_H

#include "Team.h"
#include "../player/Player.h"

/**
 * Represents a team with an attacking play style.
 *
 * Attacking teams prioritize offensive gameplay and typically
 * enforce stricter requirements on forward players and goal scoring.
 */
class AttackingTeam final : public Team {
public:
    /**
     * Minimum number of goals required from forwards in evaluation logic.
     */
    static constexpr unsigned FORWARD_MIN_SCORED_GOALS = 6;

    /**
     * Required number of goalkeepers in the team.
     */
    static constexpr unsigned REQUIRED_GOALKEEPERS = 2;

    /**
     * Minimum number of forward players required in the team.
     */
    static constexpr unsigned MIN_FORWARDERS_REQUIRED = 8;

    /**
     * Minimum number of defenders required in the team.
     */
    static constexpr unsigned MIN_DEFENDERS_REQUIRED = 2;

    /**
     * Minimum number of midfielders required in the team.
     */
    static constexpr unsigned MIN_MIDFIELDERS_REQUIRED = 2;

    /**
     * Minimum number of wingers required in the team.
     */
    static constexpr unsigned MIN_WINGERS_REQUIRED = 2;

    /**
     * Default constructor.
     *
     * Creates an empty attacking team with default values.
     */
    AttackingTeam();

    /**
     * Constructs an attacking team with full details.
     *
     * @param name The name of the team.
     * @param coachName The name of the team's coach.
     * @param stadiumName The name of the home stadium.
     * @param budget The initial budget of the team.
     */
    AttackingTeam(const std::string &name,
                  const std::string &coachName,
                  const std::string &stadiumName,
                  double budget);

    /**
     * Copy constructor.
     *
     * @param other The attacking team to copy.
     */
    AttackingTeam(const AttackingTeam &other);

    /**
     * Copy assignment operator.
     */
    AttackingTeam &operator=(const AttackingTeam &other);

    AttackingTeam(AttackingTeam &&other) noexcept;

    AttackingTeam &operator=(AttackingTeam &&other) noexcept;

    /**
     * Virtual destructor.
     */
    ~AttackingTeam() noexcept override = default;

    /**
     * Creates a polymorphic copy of the team.
     *
     * @return Pointer to a newly allocated copy of this team.
     *
     * @note Caller is responsible for deleting the returned object.
     */
    [[nodiscard]] Team *clone() const override;

    /**
     * Adds a player to the team.
     *
     * This method applies attacking-team-specific rules when adding
     * players, such as enforcing positional constraints or budget limits.
     *
     * @param player The player to add.
     * @param isTransfer Indicates whether the player is being added via transfer.
     */
    void addPlayer(Player &player, bool isTransfer) override;

    /**
   * Outputs the state of an AttackingTeam object to an output stream.
   *
   * This function serializes the attacking team’s data into a human-readable
   * or file-friendly format. The exact format includes team identity information and
   * all relevant attributes required to reconstruct the object.
   *
   * @param os The output stream to write the team data to.
   * @param team The AttackingTeam instance to be written.
   * @return Reference to the output stream to allow chaining.
   */
    friend std::ostream &operator<<(std::ostream &os, const AttackingTeam &team);

    /**
     * Reads an AttackingTeam object from an input stream.
     *
     * This function deserializes an AttackingTeam instance from the given stream.
     * It must reconstruct the internal state of the team in the same format
     * produced by operator<<.
     *
     * The function assumes the input format is valid and consistent with the
     * serialization logic.
     *
     * @param is The input stream to read the team data from.
     * @param team The AttackingTeam instance to populate.
     * @return Reference to the input stream to allow chaining.
     */
    friend std::istream &operator>>(std::istream &is, AttackingTeam &team);
};

#endif //ATTACKINGTEAM_H
