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
    * Constructs an AttackingTeam with full configuration.
    *
    * This constructor forwards all parameters to the base Team class constructor
    * and initializes an attacking-style team with the given squad composition.
    *
    * The validation of all parameters (name, stadium, budget, and player constraints)
    * is performed in the base Team constructor.
    *
    * @param type The team type (expected to be ATTACKING).
    * @param name The name of the team.
    * @param stadiumName The name of the home stadium.
    * @param players Initial list of players in the team.
    * @param budget Initial budget of the team.
    * @param forwardersCount Number of forward players.
    * @param midfieldersCount Number of midfield players.
    * @param goalkeepersCount Number of goalkeepers.
    * @param defendersCount Number of defenders.
    * @param wingersCount Number of wingers.
    */
    AttackingTeam(TeamType type,
                  const std::string &name,
                  const std::string &stadiumName,
                  const std::vector<Player> &players,
                  double budget,
                  unsigned forwardersCount,
                  unsigned midfieldersCount,
                  unsigned goalkeepersCount,
                  unsigned defendersCount,
                  unsigned wingersCount);

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
     * @param stadiumName The name of the home stadium.
     * @param budget The initial budget of the team.
     */
    AttackingTeam(const std::string &name,
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
};

#endif //ATTACKINGTEAM_H
