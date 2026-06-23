//
// Created by User on 5/16/2026.
//

#ifndef TEAMVALIDATOR_H
#define TEAMVALIDATOR_H

#include <vector>
#include <string>

#include "../../player/Player.h"
#include "../team/Team.h"

/**
 * A utility class responsible for validating team-related constraints.
 *
 * This class provides static methods that ensure team rules are enforced,
 * such as budget limits, team size restrictions, player statistics consistency,
 * and validity of team-related operations.
 */
class TeamValidator final {
private:
    /**
   * Checks whether a given team is present in a collection of teams.
   *
   * This function determines if the specified team pointer refers to a team
   * that is managed within the provided vector. The check is performed by
   * comparing team identities using the team's name, not by pointer equality.
   *
   * @param t The team to search for.
   * @param teams The collection of teams to search within.
   * @return true if a team with the same name exists in the collection; false otherwise.
   */
    static bool isManaged(const Team *t, const std::vector<Team *> &teams);

public:
    /**
     * Default constructor.
     */
    TeamValidator() = default;

    /**
     * Validates that a team's budget is valid.
     *
     * @param budget The budget to validate.
     *
     * @throws std::invalid_argument If the budget is negative or invalid.
     */
    static void validateBudget(double budget);

    /**
     * Validates that a team does not exceed the allowed size.
     *
     * @param teamSize The current number of players in the team.
     * @param maxTeamSize The maximum allowed number of players.
     *
     * @throws std::invalid_argument If the team size exceeds the limit.
     */
    static void validateTeamSize(unsigned teamSize, unsigned maxTeamSize);

    /**
     * Validates the remaining budget after operations such as transfers.
     *
     * @param remainingBudget The remaining budget to validate.
     *
     * @throws std::invalid_argument If the remaining budget is invalid (e.g., negative).
     */
    static void validateRemainingBudget(double remainingBudget);

    /**
     * Validates consistency between player scoring statistics.
     *
     * Ensures that a player's recorded goals are consistent with
     * the target values expected for a given position or context.
     *
     * @param playerPosition The actual position of the player.
     * @param targetPosition The expected/required position.
     * @param scoredGoals The player's recorded goals.
     * @param targetGoals The expected number of goals.
     * @param playerName The player's name (used for error reporting).
     * @param teamName The team name (used for error reporting).
     *
     * @throws std::invalid_argument If validation fails.
     */
    static void validatePlayerScoredGoals(Player::Position playerPosition,
                                          Player::Position targetPosition,
                                          unsigned scoredGoals,
                                          unsigned targetGoals,
                                          const std::string &playerName,
                                          const std::string &teamName);

    /**
     * Validates that player distribution across positions is correct.
     *
     * @param args A vector representing counts per position or rule set.
     * @param remainingPlaces Number of remaining available slots in the team.
     * @param exceptionMessage Message to use when validation fails.
     *
     * @throws std::invalid_argument If the distribution is invalid.
     */
    static void validatePlayersCountByPosition(const std::vector<unsigned> &args,
                                               unsigned remainingPlaces,
                                               const std::string &exceptionMessage);

    /**
     * Validates that the minimum required number of teams exists.
     *
     * @param minTeamsCount Minimum allowed number of teams.
     * @param currentTeamsCount Current number of registered teams.
     *
     * @throws std::invalid_argument If the team count is below the minimum.
     */
    static void validateTeamsCount(unsigned minTeamsCount,
                                   unsigned currentTeamsCount);

    /**
     * Validates that both teams exist in the provided collection.
     *
     * @param teams List of available teams.
     * @param firstTeam First team to validate.
     * @param secondTeam Second team to validate.
     *
     * @throws std::invalid_argument If either team is not found.
     */
    static void validateThatTeamsAreFound(const std::vector<Team *> &teams,
                                          const Team &firstTeam,
                                          const Team &secondTeam);

    /**
     * Validates that the given teams are managed by the same manager.
     *
     * @param teams List of teams managed by a manager.
     * @param homeTeam Pointer to the home team.
     * @param guestTeam Pointer to the guest team.
     *
     * @throws std::invalid_argument If a team is not managed by the manager.
     */
    static void validateThatTeamsAreMangedByAManager(const std::vector<Team *> &teams,
                                                     const Team *homeTeam,
                                                     const Team *guestTeam);

    /**
     * Validates that a player number is unique within a team.
     *
     * @param team The team to check against.
     * @param number The player number to validate.
     *
     * @throws std::invalid_argument If the number is already used.
     */
    static void validateUniquePlayerNumber(const Team &team, unsigned number);

    /**
     * Validates that a player name is unique within a team.
     *
     * @param team The team to check against.
     * @param name The player name to validate.
     *
     * @throws std::invalid_argument If the name is already used.
     */
    static void validateUniquePlayerName(const Team &team, const std::string &name);

    static void validateForwarders (unsigned forwardersCount);
    static void validateMidfielders (unsigned midfieldersCount);
    static void validateGoalkeepers (unsigned goalkeepersCount);
    static void validateDefenders (unsigned defendersCount);
    static void validateWingers (unsigned wingersCount);
};

#endif //TEAMVALIDATOR_H
