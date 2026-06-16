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
    TRANSFER_PLAYER,

    VIEW_PLAYER,
    LIST_PLAYERS,
    UPDATE_SALARY,
    VIEW_PLAYER_STATS,

    CREATE_LINEUP,
    EDIT_LINEUP,
    VALIDATE_LINEUP,
    AUTO_SELECT_LINEUP,
    VIEW_LINEUP,

    VIEW_TOP_SCORERS,
    VIEW_TEAM_STATS,
    PLAYER_RANKING,
    VIEW_SEASON_STATS,

    GET_CHAMPION,
    GET_VICE_CHAMPION,
    GET_THIRD_PLACE,
    GET_TOP_SCORER,

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
    if (commandValue == "transfer_player") return Command::TRANSFER_PLAYER;

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
    if (commandValue == "get_vice_champion") return Command::GET_VICE_CHAMPION;
    if (commandValue == "get_third_place") return Command::GET_THIRD_PLACE;
    if (commandValue == "get_top_scorer") return Command::GET_TOP_SCORER;

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

#endif // COMMAND_H