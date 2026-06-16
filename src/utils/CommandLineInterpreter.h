//
// Created by User on 6/4/2026.
//

#ifndef COMMANDLINEINTERPRETER_H
#define COMMANDLINEINTERPRETER_H

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include "../model/championship/history/ChampionshipHistory.h"
#include "../model/team/factory/TeamFactory.h"
#include "../simulation/FootballGameSimulator.h"
#include "../utils/Map.h"
#include "../model/match/Match.h"
#include "../model/match/lineup/Lineup.h"

/**
 * Enum representing all supported CLI commands.
 *
 * This enum is used internally after parsing user input strings.
 */
enum Command {
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
    LIST_PLAYER_STATS,

    GET_CHAMPION,
    GET_RUNNER_UP,
    GET_THIRD_PLACE,
    GET_TOP_SCORERS,

    EXPORT_DATA,
    IMPORT_DATA,

    SIMULATE_GOAL,

    HELP,
    EXIT,
    MENU,

    UNKNOWN
};

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

/**
 * Main CLI controller responsible for interpreting commands
 * and delegating execution to the simulation logic.
 *
 * IMPORTANT:
 * - This class uses raw pointers but does NOT own the objects
 *   passed into its constructor.
 */
class CommandLineInterpreter {
private:
    ChampionshipHistory* history = nullptr;
    Championship* championship = nullptr;
    FootballGameSimulator* simulator = nullptr;

public:
    /**
     * Creates interpreter with external ownership.
     *
     * @param h Championship history (owned externally)
     * @param c Active championship (owned externally)
     * @param s Simulator (owned externally)
     */
    CommandLineInterpreter(
        ChampionshipHistory& h,
        Championship& c,
        FootballGameSimulator& s
    ) : history(&h), championship(&c), simulator(&s) {}

private:
    static Map<unsigned, Championship>
    listSeasons(const ChampionshipHistory& championshipHistory);

    static void playAllMatches(Championship& championship);

    static void showPodium(const Championship& championship);

    static void finishSeason(ChampionshipHistory& history,
                             Championship& championship);

    static void playMatch(FootballGameSimulator& simulator,
                          int matchIndex);

    static void viewMatches(const Championship& championship);

    static void enterMatchResult(Match& match);

    static std::vector<Team*> listTeams(Championship& championship);

    static TeamType parseTeamType(const std::string& type);

    static void addTeam(std::vector<std::string> args,
                        Championship& championship);

    static void removeTeam(const std::string& teamName,
                           Championship& championship);

    static Player::Position toPosition(const std::string& posValue);

    static void addPlayer(Player& player, Team& team);

    static void removePlayer(const std::string& playerName,
                             Team& team);

    static void transferPlayers(Team& firstTeam,
                                Team& secondTeam);

    static void viewPlayer(const std::string& playerName,
                           const Championship& championship);

    static std::vector<Player*> listPlayers(const Team& team);

    static void updateSalary(Championship& championship,
                             Player& player);

    static void autoSelectLineup(Match& match);

    static void deleteLineup(Match& match,
                             const Lineup& lineup);

    static Map<Player*, unsigned> listTopScorers(Team& team);

    static Team::Statistics listTeamStats(Team& team);

    static void viewPlayerRanking(Championship& championship);

    static Map<Team*, Team::Statistics>
    listSeasonStats(Championship& championship);

    static Map<Player*, Player::Statistics>
    listPlayerStats(const Team& team);

    static const Team& getChampion(const Championship& championship);

    static const Team& getRunnerUp(const Championship& championship);

    static const Team& getThirdPlace(const Championship& championship);

    static const Player& getTopScorer(const Championship& championship);

    static void exportData(const ChampionshipHistory& history,
                           const std::string& filename);

    static ChampionshipHistory&
    importData(const std::string& filename);

    static void simulateGoal(Match& match);

    static void help(const std::string& command);

    static void menu();

    /**
     * Frees dynamically allocated resources owned by this interpreter.
     *
     * NOTE: only deletes members if this class owns them (check design).
     */
    void cleanup();

public:
    /**
     * Executes a parsed command with arguments.
     *
     * @param command Parsed command enum
     * @param args Command arguments
     */
    void execute(Command command, std::vector<std::string> args);
};

#endif // COMMANDLINEINTERPRETER_H