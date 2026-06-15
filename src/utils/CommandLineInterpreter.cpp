//
// Created by User on 6/4/2026.
//

#include "CommandLineInterpreter.h"

#include "MatchResultApplier.h"

const Map<unsigned, Championship>& CommandLineInterpreter::listSeasons(const ChampionshipHistory &championshipHistory) {
    return championshipHistory.getChampionships();
}

void CommandLineInterpreter::playAllMatches(Championship &championship) {
    for (auto match : championship.getMatches()) {
        CommandLineInterpreter::playMatch(match);
    }
}

void CommandLineInterpreter::showPodium(const Championship &championship) {
    std::cout << "The champion is: " << CommandLineInterpreter::getChampion(championship).getName() << "." << std::endl;
    std::cout << "The vice-champion is: " << CommandLineInterpreter::getRunnerUp(championship).getName() << "." << std::endl;
    std::cout << "The third champion is: " << CommandLineInterpreter::getTopScorer(championship).getName() << "." << std::endl;
}

void CommandLineInterpreter::finishSeason(ChampionshipHistory& history, Championship &championship) {
    for (const auto& match : championship.getMatches()) {
        if (!match.isFinished()) {
            throw std::invalid_argument(toString(ExceptionMessages::NOT_ALL_MATCHES_FINISHED_YET));
        } else {
            Match finishedMatch(match);
            enterMatchResult(finishedMatch);
        }
    }
    std::string filename;
    std:: cout << "Enter filename for championship data's export: ";
    std::cin >> filename;
    history.addChampionship(championship.getYear(), championship);
    championship.finish();

    exportData(history, filename);
}

void CommandLineInterpreter::playMatch(Match &match) {
    // TODO: maka a simulation of a real football game
}

void CommandLineInterpreter::viewMatches(const Championship &championship) {
    for (const auto& match : championship.getMatches()) {
        std::cout << "The host in the match is: " << match.getHost() << " with goals:" << match.getHostGoals() << "." << std::endl;
        std::cout << "The guest in the match is: " << match.getGuest() << " with goals:" << match.getGuestGoals() << "." << std::endl;
        std::cout << "The top scorers are: " << getTopScorer(championship).getName() << "." << std::endl;
    }
}

void CommandLineInterpreter::enterMatchResult(Match &match) {
    Match::MatchResult result;
    result.home = match.getHost();
    result.guest = match.getGuest();

    std::vector<Match::MatchResult::Scorer*> goals;
    int totalGoalsCount;
    std::cout << "Enter total goals count: ";
    std::cin >> totalGoalsCount;

    std::string playerName;
    unsigned scoredGals;
    while (totalGoalsCount > 0) {
        std::cout << "Enter player name: ";
        std::cin >> playerName;

        std::cout << "Enter goals: ";
        std::cin >> scoredGals;

        if (validGoalsCount(scoredGals)) {
            // TODO: check these warnings below
            if (isHomePlayer(playerName, match.getHost())) {
                result.homeGoals += scoredGals;
            } else if (isGuestPlayer(playerName, match.getGuest())) {
                result.guestGoals += scoredGals;
            } else {
              throw std::invalid_argument(toString(ExceptionMessages::DOES_NOT_PLAY_IN_THIS_MATCH));
            }

            totalGoalsCount--;
        } else {
            throw std::invalid_argument(toString(ExceptionMessages::GOALS_COUNT_CANNOT_BE_NEGATIVE));
        }
    }

    MatchResultApplier::apply(result);
}

const std::vector<Team*>& CommandLineInterpreter::listTeams(Championship &championship) {
    return championship.getTeamManager().getTeams();
}

void CommandLineInterpreter::addTeam(Team* team, Championship &championship) {
    for (int i = 0; i < championship.getTeamManager().getTeams().size(); i++) {
        Team* currentTeam = championship.getTeamManager().getTeams()[i];
        if (std::strcmp(currentTeam->getName().c_str(), team->getName().c_str()) == 0)
            throw std::invalid_argument(toString(ExceptionMessages::TEAM_ALREADY_EXSISTS));
    }

    championship.getTeamManager().addTeam(team);
}

void CommandLineInterpreter::removeTeam(const std::string &teamName, Championship &championship) {
    for (int i = 0; i < championship.getTeamManager().getTeams().size(); i++) {
        Team* currentTeam = championship.getTeamManager().getTeams()[i];
        if (std::strcmp(currentTeam->getName().c_str(), teamName.c_str()) != 0)
            throw std::invalid_argument(toString(ExceptionMessages::TEAM_DOES_NOT_EXSIST));
    }

    championship.getTeamManager().removeTeam(teamName);
}

void CommandLineInterpreter::addPlayer(Player* player, Team &team) {
    if (hasPlayerWithName(team, player->getName())) {
        throw std::invalid_argument(toString(ExceptionMessages::THERE_IS_PLAYER_WITH_SAME_NAME));
    }

    team.addPlayer(player, false);
}

void CommandLineInterpreter::removePlayer(const std::string &playerName, Team &team) {
    team.removePlayer(playerName);
}

void CommandLineInterpreter::transferPlayers(Team &firstTeam, Team &secondTeam) {
    // TODO:
    // 1. Get randomly two players from the given teams
    // 2.1. Validates that team A does not have a player with the same name as the transferred player from the team B
    // 2.2. Add a player from team A to a team B with a isTransfer = true flag
    // 3.1. Validates that team B does not have a player with the same name as the transferred player from the team A
    // 3.2. Add a player from team B to a team A with a isTransfer = true flag
}

void CommandLineInterpreter::viewPlayer(const Player &player) {
    // TODO: prints the data of the player
}

const std::vector<Player*>& CommandLineInterpreter::listPlayers(Team &team) {
    return team.getPlayers();
}

void CommandLineInterpreter::updateSalary(Championship& championship, Player &player) {
    Team* t = nullptr;
    for (auto currTeam : championship.getTeamManager().getTeams()) {
        for (auto currPlayer : currTeam->getPlayers()) {
            if (std::strcmp(currPlayer->getName().c_str(), player.getName().c_str()) != 0) {
                throw std::invalid_argument(toString(ExceptionMessages::NO_PLAYER_WITH_THIS_NAME));
            } else {
                t = currTeam;
                break;
            }
        }
    }
    championship.getAccountingManager().regulateSalary(player, *t);
}

const Lineup & CommandLineInterpreter::autoSelectLineup(const Team &team) {
    // TODO: maka a simulation of selecting lineups
}

void CommandLineInterpreter::deleteLineup(Match &match, const Lineup &lineup) {
    if (std::strcmp(match.getGuest()->getName().c_str(), lineup.getTeam()->getName().c_str()) == 0) {
        match.setGuest(nullptr);
    } else if (std::strcmp(match.getHost()->getName().c_str(), lineup.getTeam()->getName().c_str()) == 0) {
        match.setHost(nullptr);
    } else {
        throw std::invalid_argument(toString(ExceptionMessages::NO_LINEUP_WITH_THIS_TEAM_NAME));
    }
}

const Map<Player*, unsigned>& CommandLineInterpreter::listTopScorers(Team &team) {
    Map<Player*, unsigned> champs;
    for (const auto player : team.getPlayers()) {
        champs.add(player, player->getStats().scoredGoals);
    }
    // TODO: sort them by goals
    for (const auto& pair : champs.getData()) {
        // TODO: traverse them and find the top three biggest goals' value and return the players
    }
}

const Team::Statistics& CommandLineInterpreter::listTeamStats(Team &team){
    return team.getStats();
}

void CommandLineInterpreter::viewPlayerRanking(Championship &championship) {
    for (auto team : championship.getTeamManager().getTeams()) {
        auto champs = listTopScorers(*team);
        for (auto player : champs.getData()) {

        }
    }
}

const Map<Team*, Team::Statistics>& CommandLineInterpreter::listSeasonStats(Championship &championship) {
    Map<Team*, Team::Statistics> stats;
    for ( const auto& team: championship.getTeamManager().getTeams()) {
        stats.add(team, team->getStats());
    }
    // TODO: check this warning
    return stats;
}

const Map<Player*, Player::Statistics>& CommandLineInterpreter::listPlayerStats(Team &team) {
    Map<Player*, Player::Statistics> stats;
    for ( const auto& player: team.getPlayers()) {
        stats.add(player, player->getStats());
    }
    // TODO: check this warning
    return stats;
}

const Team& CommandLineInterpreter::getChampion(const Championship &championship) {
    std::pair<Team*, int> champ = {};
    for (const auto team : championship.getTeamManager().getTeams()) {
        if (team->getStats().winsCount > champ.second) {
            champ = {team, team->getStats().winsCount};
        }
    }

    return *champ.first;
}

const Team& CommandLineInterpreter::getRunnerUp(const Championship &championship) {
    Map<Team*, int> champs;
    for (const auto team : championship.getTeamManager().getTeams()) {
        champs.add(team, team->getStats().winsCount);
    }
    // TODO: sort them by goals
    for (const auto pair: champs.getData()) {
        // TODO: traverse them and find the second biggest goals' value and return the team
    }
}

const Team& CommandLineInterpreter::gtThirdPlace(const Championship &championship) {
    Map<Team*, int> champs;
    for (const auto team : championship.getTeamManager().getTeams()) {
        champs.add(team, team->getStats().winsCount);
    }
    // TODO: sort them by goals
    for (const auto pair: champs.getData()) {
        // TODO: traverse them and find the third biggest goals' value and return the team
    }
}

const Player& CommandLineInterpreter::getTopScorer(const Championship &championship) {
    // TODO: implement similar logic to this with top teams
}

void CommandLineInterpreter::exportData(const ChampionshipHistory &championshipHistory, const std::string &filename) {
    // TODO: save data for a real game simulation in a file
}

ChampionshipHistory& CommandLineInterpreter::importData(const std::string &filename) {
    // TODO: read a file and init a game from data saved in this file
}

void CommandLineInterpreter::simulateGoal(Match &match) {
    // TODO: simulate real match scoring a goal
}

void CommandLineInterpreter::help(const std::string& command) {
    Command cmd = parseCommand(command);

    switch (cmd) {

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

        case Command::FINISH_SEASON:
            std::cout << "finish_season\n"
                      << "Marks the current season as completed.\n";
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
                      << "add_team attacking Liverpool Klopp Anfield 10000000\n";
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
                      << "Removes a player from a team.\n";
            break;

        case Command::TRANSFER_PLAYERS:
            std::cout << "transfer_players <team1> <player1> "
                         "<team2> <player2>\n"
                      << "Swaps players between teams.\n";
            break;

        case Command::VIEW_PLAYER:
            std::cout << "view_player <team> <player_name>\n"
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

        case Command::AUTO_SELECT_LINEUP:
            std::cout << "auto_select_lineup <team>\n"
                      << "Automatically generates a valid lineup.\n";
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

        default:
            std::cout << "Unknown command.\n"
                      << "Type 'menu' to see all commands or "
                         "'help <command>' for details.\n";
            break;
    }
}

int CommandLineInterpreter::exit() {
    // TODO: clear all used resource in order to prevent from memory leaks
    return 0;
}

void CommandLineInterpreter::menu() {
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
    std::cout << "  auto_select_lineup\n";
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
    std::cout << "  simulate_goal\n";

    std::cout << "[System]\n";
    std::cout << "  help\n";
    std::cout << "  edit\n";
    std::cout << "  menu\n\n";

    std::cout << "====================================================================\n";
    std::cout << "Type a command exactly as shown above.\n";
    std::cout << "Example: start_season\n";
    std::cout << "====================================================================\n";
}

void CommandLineInterpreter::execute(Command command) {
    switch (command) {
        case Command::MENU: menu(); break;
        default: throw std::invalid_argument(toString(ExceptionMessages::INVALID_COMMAND));
    }
}