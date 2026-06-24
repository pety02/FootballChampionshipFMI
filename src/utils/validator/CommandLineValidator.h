#ifndef COMMANDLINEVALIDATOR_H
#define COMMANDLINEVALIDATOR_H

#include <string>
#include "../../model/team/Team.h"

/**
 * Validation utilities used by the CommandLineInterpreter.
 *
 * Responsible for enforcing rules related to:
 * - goal consistency in matches
 * - player-team relationships (home/guest membership)
 * - uniqueness constraints for player operations
 */
class CommandLineValidator {
public:
    /**
     * Validates that the number of scored goals is consistent
     * with the total number of goals recorded in a match.
     *
     * @param scoredGoals Number of goals attributed to a player/team.
     * @param totalScoredGoals Total goals recorded in the match.
     *
     * @throws std::invalid_argument if values are inconsistent.
     */
    static void validateGoalsCount(unsigned scoredGoals, int totalScoredGoals);

    /**
     * Checks whether a player belongs to the home team.
     *
     * NOTE: This function only validates membership, it does not throw.
     *
     * @param playerName Name of the player.
     * @param team Team to check against.
     * @return true if player belongs to the home team, false otherwise.
     */
    static bool validateIsHomePlayer(const std::string &playerName,
                                     const Team &team);

    /**
     * Checks whether a player belongs to the guest team.
     *
     * NOTE: This function only validates membership, it does not throw.
     *
     * @param playerName Name of the player.
     * @param team Team to check against.
     * @return true if player belongs to the guest team, false otherwise.
     */
    static bool validateIsGuestPlayer(const std::string &playerName,
                                      const Team &team);

    /**
     * Ensures that a player name is unique within a given team.
     *
     * @param playerName Name to check.
     * @param team Team in which uniqueness must be guaranteed.
     *
     * @throws std::invalid_argument if a player with the same name exists.
     */
    static void validateUniquePlayerName(const std::string &playerName,
                                         const Team &team);

    /**
    * Searches for a player by name inside a team and returns a copy of the player.
    *
    * This function iterates through the team's player list and attempts to find
    * a player whose name matches the provided input. If found, a copy of that
    * player is returned.
    *
    * The function returns by value to avoid lifetime and ownership issues,
    * ensuring the returned object is independent of the team's internal storage.
    *
    * @param playerName The name of the player to search for.
    * @param team The team in which to search for the player.
    * @return A copy of the matching Player object.
    *
    * @throws std::invalid_argument If no player with the given name exists in the team.
    */
    static Player resolvePlayer(const std::string &playerName, const Team &team);
};

#endif // COMMANDLINEVALIDATOR_H