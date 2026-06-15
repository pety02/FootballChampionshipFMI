//
// Created by User on 6/4/2026.
//

#ifndef COMMANDLINEINTERPRETER_H
#define COMMANDLINEINTERPRETER_H

#include "../model/championship/history/ChampionshipHistory.h"
#include "../../utils/ExceptionMessages.h"
#include <iostream>

/**
 *
 */
enum class Command {
    LIST_SEASONS,

    PLAY_ROUND,
    SHOW_PODIUM,
    FINISH_SEASON,

    PLAY_MATCH,
    VIEW_MATCHES,
    ENTER_MATCH_RESULT,

    LIST_TEAMS,
    ADD_TEAM,
    REMOVE_TEAM,

    ADD_PLAYER,
    REMOVE_PLAYER,
    TRANSFER_PLAYERS,

    VIEW_PLAYER,
    LIST_PLAYERS,
    UPDATE_SALARY,

    AUTO_SELECT_LINEUP,
    DELETE_LINEUP,
    LIST_TOP_SCORERS,
    LIST_TEAM_STATS,
    VIEW_PLAYER_RANKING,
    LIST_SEASON_STATS,
    LIST_PLAYER_STATS, GET_CHAMPION, GET_RUNNER_UP, GET_THIRD_PLACE,
    GET_TOP_SCORERS,
    EXPORT_DATA,
    IMPORT_DATA,
    SIMULATE_GOAL,
    HELP,
    EDIT,
    MENU,
    UNKNOWN
};

/**
 *
 * @param cmd
 * @return
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
    if (cmd == "edit") return Command::EDIT;
    if (cmd == "menu") return Command::MENU;

    return Command::UNKNOWN;
}

/**
 *
 */
class CommandLineInterpreter {
private:

    /**
     *
     * @param championshipHistory
     * @return
     */
    static const Map<unsigned, Championship>& listSeasons(const ChampionshipHistory& championshipHistory);

    /**
     *
     * @param championship
     */
    static void playAllMatches(Championship& championship);

    /**
     *
     * @param championship
     */
    static void showPodium(const Championship& championship);

    /**
     *
     * @param championship
     */
    static void finishSeason(ChampionshipHistory& history, Championship& championship);

    /**
     *
     * @param match
     */
    static void playMatch(Match& match);

    /**
     *
     * @param championship
     */
    static void viewMatches(const Championship& championship);

    /**
     *
     * @param match
     */
    static void enterMatchResult(Match& match);

    /**
     *
     * @param championship
     * @return
     */
    static const std::vector<Team*>& listTeams(Championship& championship);

    /**
     *
     * @param team
     * @param championship
     */
    static void addTeam(Team* team, Championship& championship);

    /**
     *
     * @param teamName
     * @param championship
     */
    static void removeTeam(const std::string& teamName, Championship& championship);

    /**
     *
     * @param player
     * @param team
     */
    static void addPlayer(Player* player, Team& team);

    /**
     *
     * @param playerName
     * @param team
     */
    static void removePlayer(const std::string& playerName, Team& team);

    /**
     *
     * @param firstTeam
     * @param secondTeam
     */
    static void transferPlayers(Team& firstTeam, Team& secondTeam);

    /**
     *
     * @param player
     */
    static void viewPlayer(const Player& player);

    /**
     *
     * @param team
     * @return
     */
    static const std::vector<Player*>& listPlayers(Team& team);

    /**
     *
     * @param player
     * @param newSalary
     */
    static void updateSalary(Championship& championship, Player& player);

    /**
     *
     * @param team
     * @return
     */
    static const Lineup& autoSelectLineup(const Team& team);

    /**
     *
     * @param match
     * @param lineup
     */
    static void deleteLineup(Match& match, const Lineup& lineup);

    /**
     *
     * @param team
     * @return
     */
    static const Map<Player*, unsigned>& listTopScorers(Team& team);

    /**
     *
     * @param team
     * @return
     */
    static const Team::Statistics& listTeamStats(Team& team);

    /**
     *
     * @param team
     */
    static void viewPlayerRanking(Championship &championship);

    /**
     *
     * @param championship
     * @return
     */
    static const Map<Team*, Team::Statistics>& listSeasonStats(Championship& championship);

    /**
     *
     * @param team
     * @return
     */
    static const Map<Player*, Player::Statistics>& listPlayerStats(Team& team);

    /**
     *
     * @param championship
     * @return
     */
    static const Team& getChampion(const Championship& championship);

    /**
     *
     * @param championship
     * @return
     */
    static const Team& getRunnerUp(const Championship& championship);

    /**
     *
     * @param championship
     * @return
     */
    static const Team& gtThirdPlace(const Championship& championship);

    /**
     *
     * @param championship
     * @return
     */
    static const Player& getTopScorer(const Championship& championship);

    /**
     *
     * @param championshipHistory
     * @param filename
     */
    static void exportData(const ChampionshipHistory& championshipHistory, const std::string& filename);

    /**
     *
     * @param filename
     * @return
     */
    static ChampionshipHistory& importData(const std::string& filename);

    /**
     *
     * @param match
     */
    static void simulateGoal(Match& match);

    /**
     *
     */
    static void help(const std::string& command);

    /**
     *
     * @return
     */
    static int exit();

    /**
     *
     */
    static void menu();
public:

    /**
     *
     * @param command
     */
    static void execute(Command command);
};

#endif //COMMANDLINEINTERPRETER_H