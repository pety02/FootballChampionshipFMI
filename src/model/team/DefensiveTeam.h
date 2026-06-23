//
// Created by User on 5/14/2026.
//

#ifndef DEFENSIVETEAM_H
#define DEFENSIVETEAM_H

#include "Team.h"
#include "../player/Player.h"
#include <string>

/**
 * Represents a team with a defensive play style.
 *
 * Defensive teams prioritize strong defensive structure and
 * typically allocate more players to defensive and midfield roles
 * while minimizing attacking emphasis.
 */
class DefensiveTeam final : public Team {
protected:
    DefensiveTeam(TeamType type,
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
     * Minimum number of defenders required in the team.
     */
    static constexpr unsigned MIN_DEFENDERS_REQUIRED = 6;

    /**
     * Minimum number of midfielders required in the team.
     */
    static constexpr unsigned MIN_MIDFIELDERS_REQUIRED = 6;

    /**
     * Minimum number of wingers required in the team.
     */
    static constexpr unsigned MIN_WINGERS_REQUIRED = 2;

    /**
     * Minimum number of forward players required in the team.
     */
    static constexpr unsigned MIN_FORWARDERS_REQUIRED = 2;

    /**
     * Default constructor.
     *
     * Creates a defensive team with default configuration.
     */
    DefensiveTeam();

    /**
     * Constructs a defensive team with full configuration.
     *
     * @param name The name of the team.
     * @param stadiumName The name of the home stadium.
     * @param budget The initial budget of the team.
     */
    DefensiveTeam(const std::string &name,
                  const std::string &stadiumName,
                  double budget);

    /**
     * Copy constructor.
     *
     * @param other The defensive team to copy.
     */
    DefensiveTeam(const DefensiveTeam &other);

    /**
     * Copy assignment operator.
     *
     * @param other The defensive team to assign from.
     * @return Reference to the current object.
     */
    DefensiveTeam &operator=(const DefensiveTeam &other);

    DefensiveTeam(DefensiveTeam &&other) noexcept;

    DefensiveTeam &operator=(DefensiveTeam &&other) noexcept;

    /**
     * Destructor.
     */
    ~DefensiveTeam() noexcept override = default;

    /**
     * Creates a polymorphic copy of the team.
     *
     * @return Pointer to a newly allocated copy of this team.
     *
     * @note The caller is responsible for deleting the returned object.
     */
    [[nodiscard]] Team *clone() const override;

    /**
     * Adds a player to the team using defensive-team rules.
     *
     * This method enforces constraints that favor defensive structure,
     * ensuring a stronger defensive lineup compared to other team types.
     *
     * @param player The player to add.
     * @param isTransfer Indicates whether the player is added via transfer.
     */
    void addPlayer(Player &player, bool isTransfer) override;
};

#endif //DEFENSIVETEAM_H