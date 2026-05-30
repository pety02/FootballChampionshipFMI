//
// Created by User on 5/30/2026.
//

#ifndef EXCEPTIONMESSAGES_H
#define EXCEPTIONMESSAGES_H
#include <string>

enum class ExceptionMessages {
    // Player type validation messages
    TOO_MANY_FORWARDERS,
    TOO_MANY_WINGERS,
    TOO_MANY_DEFENDERS,
    TOO_MANY_MIDFIELDERS,
    TOO_MANY_GOALKEEPERS,

    // Matches validation messages
    NOT_ENOUGH_MATCHES,
    ROUND_NUMBER_MUST_BE_AT_MOST,
    YEAR_MUST_BE_AT_LEAST_1900,
    YEAR_MUST_BE_AT_MOST_CURRENT_YEAR,
    MATCH_DOES_NOT_EXIST_IN_THE_CURRENT_CHAMPIONSHIP,
    LINEUP_DOES_NOT_EXIST_IN_THE_CURRENT_CHAMPIONSHIP,
    NO_VALID_LINEUPS,
    ENOUGH_MATCHES, // "Has enough matches. You cannot add the current match in the current championship."

    // Players validation messages
    PLAYER_NAME_CANNOT_BE_EMPTY,
    PLAYER_NAME_CANNOT_BE_BLANK,
    PLAYER_NUMBER_MUST_BE_POSITIVE,
    PLAYER_NUMBER_MUST_BE_LESS_THAN_20,
    PLAYER_POSITION_MUST_BE_ONE_OF_THE_GIVEN, // "Player position must be GOALKEEPER, DEFENDER, MIDFIELDER, WINGER or FORWARD."
    SALARY_MUST_BE_NON_NEGATIVE,
    TRANSFER_SUM_MUST_BE_NON_NEGATIVE,
    PLAYER_WITH_THIS_NAME_ALREADY_EXISTS,
    PLAYER_CANNOT_BE_NULL,

    // Teams validation messages
    TEAM_NAME_CANNOT_BE_EMPTY,
    TEAM_NAME_CANNOT_BE_BLANK,
    STADIUM_NAME_CANNOT_BE_EMPTY,
    STADIUM_NAME_CANNOT_BE_BLANK,
    THE_TEAM_TYPE_SHOULD_BE_ONE_OF_THE_GIVEN, // "The team type should be ATTACKING, DEFENSIVE or BALANCED."
    COACH_NAME_CANNOT_BE_EMPTY,
    COACH_NAME_CANNOT_BE_BLANK,
    THE_PLAYER_CANNOT_BE_ADDED_TO_THE_TEAM,
    TEAM_NOT_FOUND,
    BUDGET_SHOULD_BE_NON_NEGATIVE,
    MAX_TEAM_SIZE_IS,
    NOT_ENOUGH_BUDGET_FOR_PLAYER_TRANSFER,
    INVALID_NUMBER_OF_TEAMS,
    BOTH_TEAMS_CANNOT_BE_FOUND,
    TEAM_WITH_A_NAME_CANNOT_BE_FOUND,
    TEAM_NOT_MANAGED_BY_THIS_MANAGER
};

static const std::string& toString(ExceptionMessages message) {
    switch (message) {
        case ExceptionMessages::TOO_MANY_FORWARDERS: return "Too many forwarders.";
        case ExceptionMessages::TOO_MANY_WINGERS: return "Too many wingers.";
        case ExceptionMessages::TOO_MANY_DEFENDERS: return "Too many defenders.";
        case ExceptionMessages::TOO_MANY_MIDFIELDERS: return "Too many midfielders.";
        case ExceptionMessages::TOO_MANY_GOALKEEPERS: return "Too many goalkeepers.";



        default: return "Unknown exception.";
    }
}

#endif //EXCEPTIONMESSAGES_H