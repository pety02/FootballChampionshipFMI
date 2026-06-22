//
// Created by User on 6/18/2026.
//

#ifndef UTILS_H
#define UTILS_H

#include "../model/team/TeamType.h"
#include "../model/player/Player.h"
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
};

#endif //UTILS_H
