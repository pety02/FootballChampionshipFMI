//
// Created by User on 5/30/2026.
//

#ifndef EXCEPTIONMESSAGES_H
#define EXCEPTIONMESSAGES_H

#include <string>

/**
 * Enumeration of all exception/message keys used in the system.
 *
 * These are converted into human-readable strings via toString().
 */
enum class ExceptionMessages {
    // Player validation messages
    TOO_MANY_FORWARDERS,
    TOO_MANY_WINGERS,
    TOO_MANY_DEFENDERS,
    TOO_MANY_MIDFIELDERS,
    TOO_MANY_GOALKEEPERS,

    // Match validation messages
    NOT_ENOUGH_MATCHES,
    MATCH_ROUND_NUMBER_MUST_BE_AT_MOST,
    CHAMPIONSHIP_ROUND_NUMBER_MUST_BE_AT_MOST,
    YEAR_MUST_BE_AT_LEAST_1900,
    YEAR_MUST_BE_AT_MOST_CURRENT_YEAR,
    MATCH_DOES_NOT_EXIST_IN_THE_CURRENT_CHAMPIONSHIP,
    LINEUP_DOES_NOT_EXIST_IN_THE_CURRENT_CHAMPIONSHIP,
    NO_VALID_LINEUPS,
    ENOUGH_MATCHES,

    // Player validation messages
    PLAYER_NAME_CANNOT_BE_EMPTY,
    PLAYER_NAME_CANNOT_BE_BLANK,
    PLAYER_NUMBER_MUST_BE_POSITIVE,
    PLAYER_NUMBER_MUST_BE_LESS_THAN_OR_EQUAL_TO,
    PLAYER_POSITION_MUST_BE_ONE_OF_THE_GIVEN,
    SALARY_MUST_BE_NON_NEGATIVE,
    TRANSFER_SUM_MUST_BE_NON_NEGATIVE,
    PLAYER_WITH_THIS_NAME_ALREADY_EXISTS,
    PLAYER_CANNOT_BE_NULL,

    // Team validation messages
    TEAM_NAME_CANNOT_BE_EMPTY,
    TEAM_NAME_CANNOT_BE_BLANK,
    STADIUM_NAME_CANNOT_BE_EMPTY,
    STADIUM_NAME_CANNOT_BE_BLANK,
    THE_TEAM_TYPE_SHOULD_BE_ONE_OF_THE_GIVEN,
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
    TEAM_NOT_MANAGED_BY_THIS_MANAGER,
    NOT_UNIQUE_PLAYER_NUMBER,
    NOT_UNIQUE_PLAYER_NAME,

    // Map
    KEY_NOT_FOUND,

    // General
    INVALID_COMMAND,
    INVALID_ARGUMENT,

    // CLI messages
    NOT_ALL_MATCHES_FINISHED_YET,
    DOES_NOT_PLAY_IN_THIS_MATCH,
    TEAM_ALREADY_EXISTS,
    TEAM_DOES_NOT_EXIST,
    NO_LINEUP_WITH_THIS_TEAM_NAME,
    SCORED_GOALS_CANNOT_BE_MORE_THAN_TOTAL_SCORED_GOALS,
    THERE_IS_PLAYER_WITH_SAME_NAME
};

/**
 * Constants used across validation logic.
 */
inline constexpr unsigned CURRENT_YEAR = 2026;
inline constexpr unsigned MAX_TEAM_SIZE = 20;
inline constexpr unsigned MAX_MATCH_ROUND_NUMBER = 2;
inline constexpr unsigned MAX_CHAMPIONSHIP_ROUND_NUMBER = 38;

/**
 * Converts an ExceptionMessages enum value into a readable string.
 *
 * @param message Enum key representing an error message.
 * @return Human-readable message string.
 */
inline std::string toString(ExceptionMessages message) {
    switch (message) {

        // Player validation
        case ExceptionMessages::TOO_MANY_FORWARDERS: return "Too many forwarders.";
        case ExceptionMessages::TOO_MANY_WINGERS: return "Too many wingers.";
        case ExceptionMessages::TOO_MANY_DEFENDERS: return "Too many defenders.";
        case ExceptionMessages::TOO_MANY_MIDFIELDERS: return "Too many midfielders.";
        case ExceptionMessages::TOO_MANY_GOALKEEPERS: return "Too many goalkeepers.";

        // Match validation
        case ExceptionMessages::NOT_ENOUGH_MATCHES: return "Not enough matches.";
        case ExceptionMessages::MATCH_ROUND_NUMBER_MUST_BE_AT_MOST:
            return "Round number must be at most " + std::to_string(MAX_MATCH_ROUND_NUMBER) + ".";
        case ExceptionMessages::CHAMPIONSHIP_ROUND_NUMBER_MUST_BE_AT_MOST:
            return "Round number must be at most " + std::to_string(MAX_CHAMPIONSHIP_ROUND_NUMBER) + ".";
        case ExceptionMessages::YEAR_MUST_BE_AT_LEAST_1900:
            return "Year must be at least 1900.";
        case ExceptionMessages::YEAR_MUST_BE_AT_MOST_CURRENT_YEAR:
            return "Year must be at most " + std::to_string(CURRENT_YEAR) + ".";
        case ExceptionMessages::MATCH_DOES_NOT_EXIST_IN_THE_CURRENT_CHAMPIONSHIP:
            return "Match does not exist in the current championship.";
        case ExceptionMessages::LINEUP_DOES_NOT_EXIST_IN_THE_CURRENT_CHAMPIONSHIP:
            return "Lineup does not exist in the current championship.";
        case ExceptionMessages::NO_VALID_LINEUPS:
            return "No valid line ups.";
        case ExceptionMessages::ENOUGH_MATCHES:
            return "Has enough matches. You cannot add the current match in the current championship.";

        // Player validation
        case ExceptionMessages::PLAYER_NAME_CANNOT_BE_EMPTY:
            return "Player name cannot be empty.";
        case ExceptionMessages::PLAYER_NAME_CANNOT_BE_BLANK:
            return "Player name cannot be blank.";
        case ExceptionMessages::PLAYER_NUMBER_MUST_BE_POSITIVE:
            return "Player number must be positive.";
        case ExceptionMessages::PLAYER_NUMBER_MUST_BE_LESS_THAN_OR_EQUAL_TO:
            return "Player number must be less than or equal to " + std::to_string(MAX_TEAM_SIZE) + ".";
        case ExceptionMessages::PLAYER_POSITION_MUST_BE_ONE_OF_THE_GIVEN:
            return "Player position must be GOALKEEPER, DEFENDER, MIDFIELDER, WINGER or FORWARD.";
        case ExceptionMessages::SALARY_MUST_BE_NON_NEGATIVE:
            return "Salary must be non-negative.";
        case ExceptionMessages::TRANSFER_SUM_MUST_BE_NON_NEGATIVE:
            return "Transfer sum must be non-negative.";
        case ExceptionMessages::PLAYER_WITH_THIS_NAME_ALREADY_EXISTS:
            return "Player with this name already exists.";
        case ExceptionMessages::PLAYER_CANNOT_BE_NULL:
            return "Player cannot be NULL.";

        // Team validation
        case ExceptionMessages::TEAM_NAME_CANNOT_BE_EMPTY:
            return "Team name cannot be empty.";
        case ExceptionMessages::TEAM_NAME_CANNOT_BE_BLANK:
            return "Team name cannot be blank.";
        case ExceptionMessages::STADIUM_NAME_CANNOT_BE_EMPTY:
            return "Stadium name cannot be empty.";
        case ExceptionMessages::STADIUM_NAME_CANNOT_BE_BLANK:
            return "Stadium name cannot be blank.";
        case ExceptionMessages::THE_TEAM_TYPE_SHOULD_BE_ONE_OF_THE_GIVEN:
            return "The team type should be ATTACKING, DEFENSIVE or BALANCED.";
        case ExceptionMessages::COACH_NAME_CANNOT_BE_EMPTY:
            return "Coach name cannot be empty.";
        case ExceptionMessages::COACH_NAME_CANNOT_BE_BLANK:
            return "Coach name cannot be blank.";
        case ExceptionMessages::THE_PLAYER_CANNOT_BE_ADDED_TO_THE_TEAM:
            return "Player cannot be added to the team.";
        case ExceptionMessages::TEAM_NOT_FOUND:
            return "Team not found.";
        case ExceptionMessages::BUDGET_SHOULD_BE_NON_NEGATIVE:
            return "Budget should not be negative.";
        case ExceptionMessages::MAX_TEAM_SIZE_IS:
            return "Max team size is " + std::to_string(MAX_TEAM_SIZE);
        case ExceptionMessages::NOT_ENOUGH_BUDGET_FOR_PLAYER_TRANSFER:
            return "Not enough budget for the player.";
        case ExceptionMessages::INVALID_NUMBER_OF_TEAMS:
            return "Invalid number of teams. Teams should be minimum 4 and even.";
        case ExceptionMessages::BOTH_TEAMS_CANNOT_BE_FOUND:
            return "Both teams cannot be found.";
        case ExceptionMessages::TEAM_WITH_A_NAME_CANNOT_BE_FOUND:
            return "Team with a name cannot be found.";
        case ExceptionMessages::TEAM_NOT_MANAGED_BY_THIS_MANAGER:
            return "Team is not managed by this manager.";
        case ExceptionMessages::NOT_UNIQUE_PLAYER_NUMBER:
            return "The player number is not unique.";
        case ExceptionMessages::NOT_UNIQUE_PLAYER_NAME:
            return "The player name is not unique.";

        // Map
        case ExceptionMessages::KEY_NOT_FOUND:
            return "Map key not found.";

        // General
        case ExceptionMessages::INVALID_COMMAND:
            return "Invalid command.";
        case ExceptionMessages::INVALID_ARGUMENT:
            return "Invalid argument.";

        // CLI
        case ExceptionMessages::NOT_ALL_MATCHES_FINISHED_YET:
            return "Not all matches finished.";
        case ExceptionMessages::DOES_NOT_PLAY_IN_THIS_MATCH:
            return "Does not play in the other match.";
        case ExceptionMessages::TEAM_ALREADY_EXISTS:
            return "Team already exists.";
        case ExceptionMessages::TEAM_DOES_NOT_EXIST:
            return "Team does not exist.";
        case ExceptionMessages::NO_LINEUP_WITH_THIS_TEAM_NAME:
            return "No line up with the team.";
        case ExceptionMessages::SCORED_GOALS_CANNOT_BE_MORE_THAN_TOTAL_SCORED_GOALS:
            return "Scored goals cannot be more than total.";
        case ExceptionMessages::THERE_IS_PLAYER_WITH_SAME_NAME:
            return "There is a player with the name that is already exists.";

        default:
            return "Unknown exception.";
    }
}

#endif // EXCEPTIONMESSAGES_H