#include "SystemCommandsEngine.h"
#include <iostream>
#include "../../utils/Command.h"

void SystemCommandsEngine::terminateProgram() {
    std::cout << "Exiting program...\n";
}

void SystemCommandsEngine::help(const std::string& command) {
    switch (parseCommand(command)) {

        case Command::LIST_SEASONS:
            std::cout << "list_seasons\n"
                      << "Displays all seasons stored in the championship history.\n";
            break;

        case Command::PLAY_ROUND:
            std::cout << "play_round\n"
                      << "Plays all matches from the current round.\n";
            break;

        case Command::SHOW_PODIUM:
            std::cout << "show_podium\n"
                      << "Displays the champion, runner-up and third-place team.\n";
            break;

        case Command::SIMULATE_SEASON:
            std::cout << "simulate_season\n"
                      << "Simulates a real season of a championship and marks the current season as completed.\n"
                      << "Example: simulate_season\n";
            break;

        case Command::PLAY_MATCH:
            std::cout << "play_match <host_team> <guest_team>\n"
                      << "Starts a specific match.\n"
                      << "Example: play_match Barcelona RealMadrid\n";
            break;

        case Command::VIEW_MATCHES:
            std::cout << "view_matches\n"
                      << "Lists all matches from the current season.\n";
            break;

        case Command::ENTER_MATCH_RESULT:
            std::cout << "enter_match_result <host_team> <guest_team>\n"
                      << "Manually enters the score and scorers.\n";
            break;

        case Command::LIST_TEAMS:
            std::cout << "list_teams\n"
                      << "Shows all teams participating in the current championship.\n";
            break;

        case Command::ADD_TEAM:
            std::cout << "add_team <type> <name> <coach> <stadium> <budget>\n"
                      << "Types: attacking, defensive, balanced\n"
                      << "Example:\n"
                      << "add_team attacking Liverpool Klopp 10000000\n";
            break;

        case Command::ADD_MANAGER:
            std::cout << "add_manager <name>\n"
                      << "Example:\n"
                      << "add_manager Anfield\n";
            break;

        case Command::ADD_MATCH:
            std::cout << "add_match <host team name> <guest team name>\n"
                      << "Example:\n"
                      << "add_match Liverpool Liverpool2\n";
            break;

        case Command::REMOVE_TEAM:
            std::cout << "remove_team <team_name>\n"
                      << "Removes a team from the championship.\n";
            break;

        case Command::ADD_PLAYER:
            std::cout << "add_player <team> <name> <number> "
                         "<position> <salary> <transfer_fee>\n"
                      << "Positions: goalkeeper, defender, midfielder, winger, forward\n"
                      << "Example:\n"
                      << "add_player Liverpool Salah 11 forward 150000 50000000\n";
            break;

        case Command::REMOVE_PLAYER:
            std::cout << "remove_player <team> <player_name>\n"
                      << "Removes a player from a team.\n"
                      << "Example:\n"
                      << "remove_player Liverpool Salah\n";
            break;

        case Command::TRANSFER_PLAYERS:
            std::cout << "transfer_players <team1> <player1> "
                         "<team2> <player2>\n"
                      << "Swaps players between teams.\n";
            break;

        case Command::VIEW_PLAYER:
            std::cout << "view_player <player_name>\n"
                      << "Displays detailed information about a player.\n";
            break;

        case Command::LIST_PLAYERS:
            std::cout << "list_players <team>\n"
                      << "Displays all players in a team.\n";
            break;

        case Command::UPDATE_SALARY:
            std::cout << "update_salary <team> <player_name> <new_salary>\n"
                      << "Changes a player's salary manually.\n";
            break;

        case Command::DELETE_LINEUP:
            std::cout << "delete_lineup <host_team> <guest_team>\n"
                      << "Deletes the lineups assigned to a match.\n";
            break;

        case Command::LIST_TOP_SCORERS:
            std::cout << "list_top_scorers <team>\n"
                      << "Displays the top scorers of a team.\n";
            break;

        case Command::LIST_TEAM_STATS:
            std::cout << "list_team_stats <team>\n"
                      << "Displays the statistics of a team.\n";
            break;

        case Command::VIEW_PLAYER_RANKING:
            std::cout << "view_player_ranking <team>\n"
                      << "Displays players sorted by performance.\n";
            break;

        case Command::LIST_SEASON_STATS:
            std::cout << "list_season_stats\n"
                      << "Displays season statistics for all teams.\n";
            break;

        case Command::LIST_PLAYER_STATS:
            std::cout << "list_player_stats <team>\n"
                      << "Displays statistics for every player in a team.\n";
            break;

        case Command::GET_CHAMPION:
            std::cout << "get_champion\n"
                      << "Shows the championship winner.\n";
            break;

        case Command::GET_RUNNER_UP:
            std::cout << "get_runner_up\n"
                      << "Shows the second-place team.\n";
            break;

        case Command::GET_THIRD_PLACE:
            std::cout << "get_third_place\n"
                      << "Shows the third-place team.\n";
            break;

        case Command::GET_TOP_SCORERS:
            std::cout << "get_top_scorers\n"
                      << "Shows the championship top scorer(s).\n";
            break;

        case Command::EXPORT_DATA:
            std::cout << "export_data <filename>\n"
                      << "Saves all championship history to a file.\n"
                      << "Example: export_data championships.dat\n";
            break;

        case Command::IMPORT_DATA:
            std::cout << "import_data <filename>\n"
                      << "Loads championship history from a file.\n";
            break;

        case Command::SIMULATE_GOAL:
            std::cout << "simulate_goal <host_team> <guest_team>\n"
                      << "Simulates a random goal in a match.\n";
            break;

        case Command::HELP:
            std::cout << "help <command>\n"
                      << "Displays detailed information about a command.\n";
            break;

        case Command::MENU:
            std::cout << "menu\n"
                      << "Displays all available commands.\n";
            break;

        case Command::EXIT:
            std::cout << "exit\n"
                      << "Exits the program.\n";
            break;

        default:
            std::cout << "Unknown command.\n"
                      << "Type 'menu' to see all commands or "
                         "'help <command>' for details.\n";
            break;
    }
}

void SystemCommandsEngine::menu() {
    std::cout
        << "Current application is a game simulator called FootballChampionshipFMI.\n"
        << "Its basic purpose is to provide you an opportunity to simulate a championship\n"
        << "season and store/load data about it via the terminal.\n"
        << "Enjoy! :)\n\n";

    std::cout << "======================== AVAILABLE COMMANDS ========================\n\n";

    std::cout << "[Season Management]\n";
    std::cout << "  list_seasons\n";
    std::cout << "  play_round\n";
    std::cout << "  show_podium\n";
    std::cout << "  finish_season\n\n";

    std::cout << "[Match Management]\n";
    std::cout << "  play_match\n";
    std::cout << "  view_matches\n";
    std::cout << "  enter_match_result\n\n";

    std::cout << "[Team Management]\n";
    std::cout << "  list_teams\n";
    std::cout << "  add_team\n";
    std::cout << "  remove_team\n\n";

    std::cout << "[Player Management]\n";
    std::cout << "  add_player\n";
    std::cout << "  remove_player\n";
    std::cout << "  transfer_players\n";
    std::cout << "  view_player\n";
    std::cout << "  list_players\n";
    std::cout << "  update_salary\n\n";

    std::cout << "[Lineup Management]\n";
    std::cout << "  delete_lineup\n\n";

    std::cout << "[Statistics]\n";
    std::cout << "  list_top_scorers\n";
    std::cout << "  list_team_stats\n";
    std::cout << "  view_player_ranking\n";
    std::cout << "  list_season_stats\n";
    std::cout << "  list_player_stats\n\n";

    std::cout << "[Awards]\n";
    std::cout << "  get_champion\n";
    std::cout << "  get_runner_up\n";
    std::cout << "  get_third_place\n";
    std::cout << "  get_top_scorers\n\n";

    std::cout << "[Persistence]\n";
    std::cout << "  export_data\n";
    std::cout << "  import_data\n\n";

    std::cout << "[Simulation Tools]\n";
    std::cout << "  simulate_goal\n\n";

    std::cout << "[System]\n";
    std::cout << "  help\n";
    std::cout << "  exit\n";
    std::cout << "  menu\n\n";

    std::cout << "====================================================================\n";
    std::cout << "Type a command exactly as shown above.\n";
    std::cout << "Example: start_season\n";
    std::cout << "====================================================================\n";
}

void SystemCommandsEngine::exportData(const ChampionshipHistory& history, const std::string &filename) {
    std::ofstream out(filename);

    if (!out.is_open()) {
        std::cout << "Failed to open file\n";
        return;
    }

    const std::vector<Championship>& championships = history.getChampionships();

    out << championships.size() << '\n';

    for (const Championship& championship : championships)
    {
        out << championship << '\n';
    }

    out.close();
}

void SystemCommandsEngine::importData(ChampionshipHistory& history, const std::string &filename) {
    std::ifstream in(filename);

    unsigned count;
    in >> count;

    for (unsigned i = 0; i < count; ++i)
    {
        unsigned year;
        in >> year;

        Championship championship;

        // read championship data
        in >> championship;

        std::cout << championship;

        history.addChampionship(championship);
    }

    in.close();
}