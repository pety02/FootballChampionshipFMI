#ifndef UTILS_H
#define UTILS_H

#include "../model/team/TeamType.h"
#include "../model/player/Player.h"
#include "../model/team/Team.h"
#include <string>
#include <vector>

/**
* Custom Pair struct used for storing a pair of data in some methods below.
*/
template<typename L, typename R>
struct Pair {
    L left;
    R right;

    Pair(L left, R right) : left(left), right(right) {
    }
};


/*
 * A class with utility static methods used in the project.
 */
class Utils {
public:
    /**
    * Converts a string representation of a team type into a TeamType enum value.
    *
    * This function compares the input string against known team type identifiers
    * ("attacking", "defensive", "balanced") and returns the corresponding enum.
    * If the input does not match any known type, TeamType::UNKNOWN is returned.
    *
    * Note: The function also prints a debug message showing the input being parsed.
    *
    * @param type The string representation of the team type.
    * @return The corresponding TeamType enum value.
    */
    static TeamType parseTeamType(const std::string &type);

    /**
    * Converts a TeamType enum value into its string representation.
    *
    * This is typically used for serialization, logging, or displaying
    * team types in a human-readable format.
    *
    * @param teamType The TeamType enum value.
    * @return A string representing the team type.
    */
    static std::string toString(TeamType teamType);

    /**
    * Converts the passed string to lower-case.
    *
    * @param str the string that should be converted to lower-case.
    *
    * @return the converted string to lower-case.
    */
    static const std::string &toLowerCase(std::string &str);

    /**
    * Converts a string into a Player::Position enum value.
    *
    * The function performs a case-insensitive normalization attempt by
    * converting uppercase characters to lowercase before comparison,
    * then maps the resulting string to a football position.
    *
    * Supported values:
    * - goalkeeper
    * - defender
    * - midfielder
    * - winger
    * - forward
    *
    * If the input does not match any known position, Player::Position::UNKNOWN
    * is returned.
    *
    * @param posValue The string representation of the player's position.
    * @return The corresponding Player::Position enum value.
    */
    static Player::Position toPosition(std::string &posValue);

    /**
    * Performs an in-place selection sort of teams by goal count in descending order.
    *
    * This is a manual sorting implementation.
    *
    * @param teams Vector of (team name, goals scored) pairs to sort.
    */
    static void selectionSortByGoals(std::vector<Pair<std::string, unsigned> > &teams);

    /**
    * Sorts a vector of team-goal pairs in descending order using selection sort.
    *
    * The function compares the second element of each pair (goals scored)
    * and arranges the vector so that teams with higher goal counts appear first.
    *
    * This is an in-place O(n^2) selection sort implementation.
    *
    * @param ranking Vector of (Team pointer, scored goals) pairs to be sorted.
    *                The vector is modified directly.
    */
    static void selectionSortTeamsByGoals(
        std::vector<std::pair<Team *, unsigned> > &ranking);

    /**
    * Clamps an unsigned integer value within a specified range.
    *
    * If the value is smaller than minVal, minVal is returned.
    * If the value is larger than maxVal, maxVal is returned.
    * Otherwise, the original value is returned unchanged.
    *
    * @param value The value to clamp.
    * @param minVal The minimum allowed value.
    * @param maxVal The maximum allowed value.
    * @return The clamped value within [minVal, maxVal].
    */
    static unsigned clampUnsigned(unsigned value, unsigned minVal, unsigned maxVal);
};

#endif //UTILS_H
