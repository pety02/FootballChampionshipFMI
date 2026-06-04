//
// Created by User on 6/4/2026.
//

#ifndef COMMAND_H
#define COMMAND_H
#include <string>

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

inline Command toCommand(const std::string &commandValue) {
    switch (commandValue) {
        case "start_season": return Command::START_SEASON;
        case "list_seasons": return Command::LIST_SEASONS;
        case "load_seasons": return Command::LOAD_SEASONS;
        case "save_seasons": return Command::SAVE_SEASONS;
        case "load_season": return Command::LOAD_SEASON;
        case "save_season": return Command::SAVE_SEASON;

        case "play_round": return Command::PLAY_ROUND;
        case "play_all_rounds": return Command::PLAY_ALL_ROUNDS;
        case "show_standings": return Command::SHOW_STANDINGS;
        case "show_podium": return Command::SHOW_PODIUM;
        case "finish_season": return Command::FINISH_SEASON;

        case "play_match": return Command::PLAY_MATCH;
        case "view_matches": return Command::VIEW_MATCHES;
        case "view_round_matches": return Command::VIEW_ROUND_MATCHES;
        case "enter_match_result": return Command::ENTER_MATCH_RESULT;

        case "list_teams": return Command::LIST_TEAMS;
        case "view_team": return Command::VIEW_TEAM;
        case "add_team": return Command::ADD_TEAM;
        case "remove_team": return Command::REMOVE_TEAM;
        case "start_new_season_for_team": return Command::START_NEW_SEASON_FOR_TEAM;

        case "add_player": return Command::ADD_PLAYER;
        case "remove_player": return Command::REMOVE_PLAYER;
        case "transfer_player": return Command::TRANSFER_PLAYER;

        case "view_player": return Command::VIEW_PLAYER;
        case "list_players": return Command::LIST_PLAYERS;
        case "update_salary": return Command::UPDATE_SALARY;
        case "view_player_stats": return Command::VIEW_PLAYER_STATS;

        case "create_lineup": return Command::CREATE_LINEUP;
        case "edit_lineup": return Command::EDIT_LINEUP;
        case "validate_lineup": return Command::VALIDATE_LINEUP;
        case "auto_select_lineup": return Command::AUTO_SELECT_LINEUP;
        case "view_lineup": return Command::VIEW_LINEUP;

        case "view_top_scorers": return Command::VIEW_TOP_SCORERS;
        case "view_team_stats": return Command::VIEW_TEAM_STATS;
        case "player_ranking": return Command::PLAYER_RANKING;
        case "view_season_stats": return Command::VIEW_SEASON_STATS;

        case "get_champion": return Command::GET_CHAMPION;
        case "get_vice_champion": return Command::GET_VICE_CHAMPION;
        case "get_third_place": return Command::GET_THIRD_PLACE;
        case "get_top_scorer": return Command::GET_TOP_SCORER;

        case "export_data": return Command::EXPORT_DATA;
        case "import_data": return Command::IMPORT_DATA;
        case "backup": return Command::BACKUP;
        case "restore_backup": return Command::RESTORE_BACKUP;

        case "simulate_goal": return Command::SIMULATE_GOAL;
        case "simulate_match": return Command::SIMULATE_MATCH;
        case "force_result": return Command::FORCE_RESULT;

        case "help": return Command::HELP;
        case "exit": return Command::EXIT;
        case "menu": return Command::MENU;

        default: return Command::UNKNOWN;
    }
}

#endif //COMMAND_H