//
// Created by User on 6/4/2026.
//

#ifndef COMMAND_H
#define COMMAND_H

#include <string>

/**
 * Represents all supported CLI commands in the application.
 *
 * Each command corresponds to a user operation such as managing
 * seasons, teams, players, matches, and simulation control.
 */
enum class Command {
    START_SEASON,
    LIST_SEASONS,
    LOAD_SEASONS,
    SAVE_SEASONS,
    LOAD_SEASON,
    SAVE_SEASON,

    PLAY_ROUND,
    PLAY_ALL_ROUNDS,
    SHOW_STANDINGS,
    SHOW_PODIUM,
    FINISH_SEASON,

    PLAY_MATCH,
    VIEW_MATCHES,
    VIEW_ROUND_MATCHES,
    ENTER_MATCH_RESULT,

    LIST_TEAMS,
    VIEW_TEAM,
    ADD_TEAM,
    REMOVE_TEAM,
    START_NEW_SEASON_FOR_TEAM,

    ADD_PLAYER,
    REMOVE_PLAYER,
    TRANSFER_PLAYERS,

    VIEW_PLAYER,
    LIST_PLAYERS,
    UPDATE_SALARY,
    VIEW_PLAYER_STATS,

    CREATE_LINEUP,
    EDIT_LINEUP,
    VALIDATE_LINEUP,
    AUTO_SELECT_LINEUP,
    DELETE_LINEUP,
    LIST_TOP_SCORERS,
    LIST_TEAM_STATS,
    VIEW_PLAYER_RANKING,
    LIST_SEASON_STATS,
    LIST_PLAYER_STATS,
    VIEW_LINEUP,

    VIEW_TOP_SCORERS,
    VIEW_TEAM_STATS,
    PLAYER_RANKING,
    VIEW_SEASON_STATS,

    GET_CHAMPION,
    GET_RUNNER_UP,
    GET_THIRD_PLACE,
    GET_TOP_SCORERS,

    EXPORT_DATA,
    IMPORT_DATA,
    BACKUP,
    RESTORE_BACKUP,

    SIMULATE_GOAL,
    SIMULATE_MATCH,
    FORCE_RESULT,

    HELP,
    EXIT,
    MENU,

    UNKNOWN
};

/**
 * Converts a string command into the corresponding Command enum value.
 *
 * @param commandValue Input command string from user.
 * @return Matching Command enum value, or Command::UNKNOWN if not recognized.
 */
inline Command toCommand(const std::string& commandValue) {
    if (commandValue == "start_season") return Command::START_SEASON;
    if (commandValue == "list_seasons") return Command::LIST_SEASONS;
    if (commandValue == "load_seasons") return Command::LOAD_SEASONS;
    if (commandValue == "save_seasons") return Command::SAVE_SEASONS;
    if (commandValue == "load_season") return Command::LOAD_SEASON;
    if (commandValue == "save_season") return Command::SAVE_SEASON;

    if (commandValue == "play_round") return Command::PLAY_ROUND;
    if (commandValue == "play_all_rounds") return Command::PLAY_ALL_ROUNDS;
    if (commandValue == "show_standings") return Command::SHOW_STANDINGS;
    if (commandValue == "show_podium") return Command::SHOW_PODIUM;
    if (commandValue == "finish_season") return Command::FINISH_SEASON;

    if (commandValue == "play_match") return Command::PLAY_MATCH;
    if (commandValue == "view_matches") return Command::VIEW_MATCHES;
    if (commandValue == "view_round_matches") return Command::VIEW_ROUND_MATCHES;
    if (commandValue == "enter_match_result") return Command::ENTER_MATCH_RESULT;

    if (commandValue == "list_teams") return Command::LIST_TEAMS;
    if (commandValue == "view_team") return Command::VIEW_TEAM;
    if (commandValue == "add_team") return Command::ADD_TEAM;
    if (commandValue == "remove_team") return Command::REMOVE_TEAM;
    if (commandValue == "start_new_season_for_team") return Command::START_NEW_SEASON_FOR_TEAM;

    if (commandValue == "add_player") return Command::ADD_PLAYER;
    if (commandValue == "remove_player") return Command::REMOVE_PLAYER;
    if (commandValue == "transfer_players") return Command::TRANSFER_PLAYERS;

    if (commandValue == "view_player") return Command::VIEW_PLAYER;
    if (commandValue == "list_players") return Command::LIST_PLAYERS;
    if (commandValue == "update_salary") return Command::UPDATE_SALARY;
    if (commandValue == "view_player_stats") return Command::VIEW_PLAYER_STATS;

    if (commandValue == "create_lineup") return Command::CREATE_LINEUP;
    if (commandValue == "edit_lineup") return Command::EDIT_LINEUP;
    if (commandValue == "validate_lineup") return Command::VALIDATE_LINEUP;
    if (commandValue == "auto_select_lineup") return Command::AUTO_SELECT_LINEUP;
    if (commandValue == "view_lineup") return Command::VIEW_LINEUP;

    if (commandValue == "view_top_scorers") return Command::VIEW_TOP_SCORERS;
    if (commandValue == "view_team_stats") return Command::VIEW_TEAM_STATS;
    if (commandValue == "player_ranking") return Command::PLAYER_RANKING;
    if (commandValue == "view_season_stats") return Command::VIEW_SEASON_STATS;

    if (commandValue == "get_champion") return Command::GET_CHAMPION;
    if (commandValue == "get_runner_up") return Command::GET_RUNNER_UP;
    if (commandValue == "get_third_place") return Command::GET_THIRD_PLACE;
    if (commandValue == "get_top_scorers") return Command::GET_TOP_SCORERS;

    if (commandValue == "export_data") return Command::EXPORT_DATA;
    if (commandValue == "import_data") return Command::IMPORT_DATA;
    if (commandValue == "backup") return Command::BACKUP;
    if (commandValue == "restore_backup") return Command::RESTORE_BACKUP;

    if (commandValue == "simulate_goal") return Command::SIMULATE_GOAL;
    if (commandValue == "simulate_match") return Command::SIMULATE_MATCH;
    if (commandValue == "force_result") return Command::FORCE_RESULT;

    if (commandValue == "help") return Command::HELP;
    if (commandValue == "exit") return Command::EXIT;
    if (commandValue == "menu") return Command::MENU;

    return Command::UNKNOWN;
}

/**
* Converts string input into internal Command enum.
*
* @param cmd Raw command string entered by the user.
* @return Corresponding Command enum value or UNKNOWN.
*/
inline Command parseCommand(const std::string& cmd) {
    if (cmd == "list_seasons") return Command::LIST_SEASONS;

    if (cmd == "play_round") return Command::PLAY_ROUND;
    if (cmd == "show_podium") return Command::SHOW_PODIUM;
    if (cmd == "finish_season") return Command::FINISH_SEASON;

    if (cmd == "play_match") return Command::PLAY_MATCH;
    if (cmd == "view_matches") return Command::VIEW_MATCHES;
    if (cmd == "enter_match_result") return Command::ENTER_MATCH_RESULT;

    if (cmd == "list_teams") return Command::LIST_TEAMS;
    if (cmd == "add_team") return Command::ADD_TEAM;
    if (cmd == "remove_team") return Command::REMOVE_TEAM;

    if (cmd == "add_player") return Command::ADD_PLAYER;
    if (cmd == "remove_player") return Command::REMOVE_PLAYER;
    if (cmd == "transfer_players") return Command::TRANSFER_PLAYERS;

    if (cmd == "view_player") return Command::VIEW_PLAYER;
    if (cmd == "list_players") return Command::LIST_PLAYERS;
    if (cmd == "update_salary") return Command::UPDATE_SALARY;

    if (cmd == "auto_select_lineup") return Command::AUTO_SELECT_LINEUP;
    if (cmd == "delete_lineup") return Command::DELETE_LINEUP;

    if (cmd == "list_top_scorers") return Command::LIST_TOP_SCORERS;
    if (cmd == "list_team_stats") return Command::LIST_TEAM_STATS;
    if (cmd == "view_player_ranking") return Command::VIEW_PLAYER_RANKING;
    if (cmd == "list_season_stats") return Command::LIST_SEASON_STATS;
    if (cmd == "list_player_stats") return Command::LIST_PLAYER_STATS;

    if (cmd == "get_champion") return Command::GET_CHAMPION;
    if (cmd == "get_runner_up") return Command::GET_RUNNER_UP;
    if (cmd == "get_third_place") return Command::GET_THIRD_PLACE;
    if (cmd == "get_top_scorers") return Command::GET_TOP_SCORERS;

    if (cmd == "export_data") return Command::EXPORT_DATA;
    if (cmd == "import_data") return Command::IMPORT_DATA;

    if (cmd == "simulate_goal") return Command::SIMULATE_GOAL;

    if (cmd == "help") return Command::HELP;
    if (cmd == "exit") return Command::EXIT;
    if (cmd == "menu") return Command::MENU;

    return Command::UNKNOWN;
}

#endif // COMMAND_H