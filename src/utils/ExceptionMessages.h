//
// Created by User on 5/30/2026.
//

#ifndef EXCEPTIONMESSAGES_H
#define EXCEPTIONMESSAGES_H

#include <string>
#include "../model/championship/history/ChampionshipHistory.h"
#include "../model/championship/validator/ChampionshipValidator.h"
#include "../model/match/validator/MatchValidator.h"

enum class ExceptionMessages {
    // Player type validation messages
    TOO_MANY_FORWARDERS,
    TOO_MANY_WINGERS,
    TOO_MANY_DEFENDERS,
    TOO_MANY_MIDFIELDERS,
    TOO_MANY_GOALKEEPERS,

    // Matches validation messages
    NOT_ENOUGH_MATCHES,
    MATCH_ROUND_NUMBER_MUST_BE_AT_MOST,
    CHAMPIONSHIP_ROUND_NUMBER_MUST_BE_AT_MOST,
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
    PLAYER_NUMBER_MUST_BE_LESS_THAN_OR_EQUAL_TO,
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

    // Map validation messages
    KEY_NOT_FOUND
};

unsigned CURRENT_YEAR = ChampionshipHistory::CURRENT_YEAR;
unsigned MAX_TEAM_SIZE = Team::MAX_TEAM_SIZE;
unsigned MAX_MATCH_ROUND_NUMBER = MatchValidator::MAX_ROUND_NUMBER;
unsigned MAX_CHAMPIONSHIP_ROUND_NUMBER = ChampionshipValidator::MAX_ROUND_NUMBER;

static const std::string& toString(ExceptionMessages message) {

    switch (message) {
        case ExceptionMessages::TOO_MANY_FORWARDERS: return "Too many forwarders.";
        case ExceptionMessages::TOO_MANY_WINGERS: return "Too many wingers.";
        case ExceptionMessages::TOO_MANY_DEFENDERS: return "Too many defenders.";
        case ExceptionMessages::TOO_MANY_MIDFIELDERS: return "Too many midfielders.";
        case ExceptionMessages::TOO_MANY_GOALKEEPERS: return "Too many goalkeepers.";

        case ExceptionMessages::NOT_ENOUGH_MATCHES: return "Not enough matches.";
        case ExceptionMessages::MATCH_ROUND_NUMBER_MUST_BE_AT_MOST: return "Round number must be at most " + std::to_string(MAX_MATCH_ROUND_NUMBER) + ".";
        case ExceptionMessages::CHAMPIONSHIP_ROUND_NUMBER_MUST_BE_AT_MOST: return "Round number must be at most " + std::to_string(MAX_CHAMPIONSHIP_ROUND_NUMBER) + ".";
        case ExceptionMessages::YEAR_MUST_BE_AT_LEAST_1900: return "Year must be at least 1900.";
        case ExceptionMessages::YEAR_MUST_BE_AT_MOST_CURRENT_YEAR: return "Year must be at most " + std::to_string(CURRENT_YEAR) + ".";
        case ExceptionMessages::MATCH_DOES_NOT_EXIST_IN_THE_CURRENT_CHAMPIONSHIP: return "Match does not exist in the current championship.";
        case ExceptionMessages::LINEUP_DOES_NOT_EXIST_IN_THE_CURRENT_CHAMPIONSHIP: return "Lineup does not exist in the current championship.";
        case ExceptionMessages::NO_VALID_LINEUPS: return "No valid line ups.";
        case ExceptionMessages::ENOUGH_MATCHES: return "Has enough matches. You cannot add the current match in the current championship.";

        case ExceptionMessages::PLAYER_NAME_CANNOT_BE_EMPTY: return "Player name cannot be empty.";
        case ExceptionMessages::PLAYER_NAME_CANNOT_BE_BLANK: return "Player name cannot be blank.";
        case ExceptionMessages::PLAYER_NUMBER_MUST_BE_POSITIVE: return "Player number must be positive.";
        case ExceptionMessages::PLAYER_NUMBER_MUST_BE_LESS_THAN_OR_EQUAL_TO: return "Player number must be less than or equal to " + std::to_string(MAX_TEAM_SIZE) + ".";
        case ExceptionMessages::PLAYER_POSITION_MUST_BE_ONE_OF_THE_GIVEN: return "Player position must be GOALKEEPER, DEFENDER, MIDFIELDER, WINGER or FORWARD.";
        case ExceptionMessages::SALARY_MUST_BE_NON_NEGATIVE: return "Salary must be non-negative.";
        case ExceptionMessages::TRANSFER_SUM_MUST_BE_NON_NEGATIVE: return "Transfer sum must be non-negative.";
        case ExceptionMessages::PLAYER_WITH_THIS_NAME_ALREADY_EXISTS: return "Player with this name already exists.";
        case ExceptionMessages::PLAYER_CANNOT_BE_NULL: return "Player cannot be NULL.";

        case ExceptionMessages::TEAM_NAME_CANNOT_BE_EMPTY: return "Team cannot be NULL.";
        case ExceptionMessages::TEAM_NAME_CANNOT_BE_BLANK: return "Team cannot be blank.";
        case ExceptionMessages::STADIUM_NAME_CANNOT_BE_EMPTY: return "Stadium name cannot be empty.";
        case ExceptionMessages::STADIUM_NAME_CANNOT_BE_BLANK: return "Stadium name cannot be blank.";
        case ExceptionMessages::THE_TEAM_TYPE_SHOULD_BE_ONE_OF_THE_GIVEN: return "The team type should be ATTACKING, DEFENSIVE or BALANCED.";
        case ExceptionMessages::COACH_NAME_CANNOT_BE_EMPTY: return "Coach name cannot be empty.";
        case ExceptionMessages::COACH_NAME_CANNOT_BE_BLANK: return "Coach name cannot be blank.";
        case ExceptionMessages::THE_PLAYER_CANNOT_BE_ADDED_TO_THE_TEAM: return "Player cannot be added to the team.";
        case ExceptionMessages::TEAM_NOT_FOUND: return "Team not found.";
        case ExceptionMessages::BUDGET_SHOULD_BE_NON_NEGATIVE: return "Budget should not be negative.";
        case ExceptionMessages::MAX_TEAM_SIZE_IS: return "Max team size is " + std::to_string(MAX_TEAM_SIZE);
        case ExceptionMessages::NOT_ENOUGH_BUDGET_FOR_PLAYER_TRANSFER: return "Not enough budget for the player.";
        case ExceptionMessages::INVALID_NUMBER_OF_TEAMS: return "Invalid number of teams. Teams should be minimum 4 and their count should be an even number.";
        case ExceptionMessages::BOTH_TEAMS_CANNOT_BE_FOUND: return "Both teams cannot be found.";
        case ExceptionMessages::TEAM_WITH_A_NAME_CANNOT_BE_FOUND: return "Team with a name cannot be found.";
        case ExceptionMessages::TEAM_NOT_MANAGED_BY_THIS_MANAGER: return "Team is not managed by this manager.";

        case ExceptionMessages::KEY_NOT_FOUND: return "Map key not found.";

        default: return "Unknown exception.";
    }
}

#endif //EXCEPTIONMESSAGES_H