//
// Created by User on 6/4/2026.
//

#include "CommandLineInterpreter.h"

#include "../model/team/factory/TeamFactory.h"

#include "CommandLineInterpreterValidator.h"
#include "../simulation/MatchResultApplier.h"

Map<unsigned, Championship>
CommandLineInterpreter::listSeasons(
        const ChampionshipHistory& history) {

    return history.getChampionships();
}

void CommandLineInterpreter::playAllMatches(
        Championship& championship) {

    FootballGameSimulator simulator;

    for (auto match : championship.getMatches()) {
        simulator.play(&match);
    }
}

void CommandLineInterpreter::showPodium(
        const Championship& championship) {

    std::cout << "Champion: " << getChampion(championship).getName() << '\n';
}

void CommandLineInterpreter::finishSeason(
        ChampionshipHistory& history,
        Championship& championship) {

    playAllMatches(championship);

    history.addChampionship(championship.getYear(), championship);

    std::cout << "Season finished.\n";
}

void CommandLineInterpreter::playMatch(
        FootballGameSimulator& simulator,
        int matchIndex) {

    Championship championship = simulator.getCurrentChampionship();
    Match match(championship.getMatches()[matchIndex]);
    simulator.play(&match);
}

void CommandLineInterpreter::viewMatches(
        const Championship& championship) {

    int index = 0;

    for (const auto& match : championship.getMatches()) {

        std::cout
                << ++index << ". "
                << match.getHost()->getName()
                << " vs "
                << match.getGuest()->getName()
                << '\n';
    }
}

void CommandLineInterpreter::enterMatchResult(Match &match) {
    Match::MatchResult result(
        match.getHost(),
        match.getGuest());

    std::vector<Match::MatchResult::Scorer*> goals;

    int totalGoalsCount = 0;

    while(totalGoalsCount <= 0) {
        std::cout << "Enter total goals count: ";
        std::cin >> totalGoalsCount;
    }

    std::string playerName;
    unsigned scoredGals;
    while (totalGoalsCount > 0) {
        std::cout << "Enter player name: ";
        std::cin >> playerName;

        std::cout << "Enter goals: ";
        std::cin >> scoredGals;

        CommandLineInterpreterValidator::validateGoalsCount(scoredGals, totalGoalsCount);

        if (CommandLineInterpreterValidator::validateIsHomePlayer(playerName, *match.getHost())) {
            result.homeGoals += scoredGals;
        } else if (CommandLineInterpreterValidator::validateIsGuestPlayer(playerName, *match.getGuest())) {
            result.guestGoals += scoredGals;
        } else {
            throw std::invalid_argument(toString(ExceptionMessages::DOES_NOT_PLAY_IN_THIS_MATCH));
        }

        totalGoalsCount--;
    }

    MatchResultApplier::apply(result);
}

std::vector<Team*> CommandLineInterpreter::listTeams(Championship &championship) {
    return championship.getTeamManager().getTeams();
}

TeamType CommandLineInterpreter::parseTeamType(const std::string& type)
{
    if (type == "attacking") return TeamType::ATTACKING;
    if (type == "defensive") return TeamType::DEFENSIVE;
    if (type == "balanced")  return TeamType::BALANCED;

    throw std::invalid_argument(
    toString(ExceptionMessages::THE_TEAM_TYPE_SHOULD_BE_ONE_OF_THE_GIVEN)
    );
}

void CommandLineInterpreter::addTeam(std::vector<std::string> args, Championship& championship) {
    if (args.empty())
        throw std::invalid_argument(toString(ExceptionMessages::INVALID_ARGUMENT));

    TeamType type = parseTeamType(args[0]);
    std::string name = args[1];
    std::string coach = args[2];
    std::string stadium = args[3];
    double budget = std::stod(args[4]);

    // check duplicates
    for (const auto& currentTeam : championship.getTeamManager().getTeams())
    {
        if (currentTeam->getName() == name)
            throw std::invalid_argument(
                toString(ExceptionMessages::TEAM_ALREADY_EXISTS)
            );
    }

    Team* team = TeamFactory::createTeam(
        type,
        name,
        coach,
        stadium,
        budget
    );

    championship.getTeamManager().addTeam(team);
}

void CommandLineInterpreter::removeTeam(const std::string &teamName, Championship &championship) {
    for (auto currentTeam : championship.getTeamManager().getTeams()) {
        if (std::strcmp(currentTeam->getName().c_str(), teamName.c_str()) != 0)
            throw std::invalid_argument(toString(ExceptionMessages::TEAM_DOES_NOT_EXIST));
    }

    championship.getTeamManager().removeTeam(teamName);
}

Player::Position CommandLineInterpreter::toPosition(const std::string& posValue) {
    // to lowercase
    for (int i = 0; i < posValue.length(); i++) {
        char c = posValue[i];
        if (c >= 'A' && c <= 'Z') {
            c += 32;
        }
    }

    if(posValue == "goalkeeper") {
        return Player::Position::GOALKEEPER;
    } else if (posValue == "defender") {
        return Player::Position::DEFENDER;
    } else if (posValue == "midfielder") {
        return Player::Position::MIDFIELDER;
    } else if (posValue == "winger") {
        return Player::Position::WINGER;
    } else if (posValue == "forward") {
        return Player::Position::FORWARD;
    } else {
        return Player::Position::UNKNOWN;
    }
}

void CommandLineInterpreter::addPlayer(Player& player, Team &team) {
    CommandLineInterpreterValidator::validateUniquePlayerName(player.getName(), team);

    team.addPlayer(player, false);
}

void CommandLineInterpreter::removePlayer(const std::string &playerName, Team &team) {
    team.removePlayer(playerName);
}

void CommandLineInterpreter::transferPlayers(
        Team& firstTeam,
        Team& secondTeam) {

    std::string firstPlayer;
    std::string secondPlayer;

    std::cout << "Player from "
              << firstTeam.getName()
              << ": ";

    std::cin >> firstPlayer;

    std::cout << "Player from "
              << secondTeam.getName()
              << ": ";

    std::cin >> secondPlayer;

    Player* p1 = nullptr;
    Player* p2 = nullptr;

    for (auto p : firstTeam.getPlayers()) {

        if (p->getName() == firstPlayer) {

            p1 = p;
            break;
        }
    }

    for (auto p : secondTeam.getPlayers()) {

        if (p->getName() == secondPlayer) {

            p2 = p;
            break;
        }
    }

    if (!p1 || !p2)
        throw std::invalid_argument(
                toString(ExceptionMessages::
                        BOTH_TEAMS_CANNOT_BE_FOUND));

    firstTeam.removePlayer(firstPlayer);
    secondTeam.removePlayer(secondPlayer);

    firstTeam.addPlayer(*p2, true);
    secondTeam.addPlayer(*p1, true);
}

void CommandLineInterpreter::viewPlayer(const std::string &playerName, const Championship& championship) {
    Player* player = nullptr;
    for(auto t : championship.getTeamManager().getTeams()) {
        for(auto p : t->getPlayers()) {
            if(p->getName() == playerName) {
                player = p;
                break;
            }
        }
    }
    if(player == nullptr) {
        return; // TODO: can be thrown an exception
    }
    std::cout << "Player: { name: " << player->getName() << ", number: " << player->getNumber() << ", position: ";

    switch (player->getPosition()) {
        case Player::Position::GOALKEEPER: std::cout << "Goalkeeper"; break;
        case Player::Position::DEFENDER: std::cout << "Defender"; break;
        case Player::Position::MIDFIELDER: std::cout << "Midfielder"; break;
        case Player::Position::WINGER: std::cout << "Winger"; break;
        case Player::Position::FORWARD: std::cout << "Forward"; break;
        default: std::cout << "Unknown"; break;
    }

    std::cout << ", salary: " << player->getSalary() << ", transferSum: " << player->getTransferSum() << ", stats: { matchesCount: "
    << player->getStats().matchesCount << ", scoredGoals:" << player->getStats().scoredGoals << " } }" << std::endl;
}

std::vector<Player*> CommandLineInterpreter::listPlayers(const Team &team) {
    return team.getPlayers();
}

void CommandLineInterpreter::updateSalary(Championship& championship, Player& player) {
    Team* playsIn = nullptr;
    for(const auto& currMatch : championship.getMatches()) {
        Team* host = currMatch.getHost();
        Team* guest = currMatch.getGuest();

        try {
            CommandLineInterpreterValidator::validateIsHomePlayer(player.getName(), *host);
            playsIn = host;
            break;
        } catch (...) {
            CommandLineInterpreterValidator::validateIsGuestPlayer(player.getName(), *guest);
            playsIn = guest;
            break;
        }
    }

    if (playsIn == nullptr) {
        return;
    }
    championship.getAccountingManager().regulateSalary(player, *playsIn);
}

void CommandLineInterpreter::autoSelectLineup(Match& match) {
    match.setHostLineup(Lineup(match.getHost()));
    match.setGuestLineup(Lineup(match.getGuest()));
}

void CommandLineInterpreter::deleteLineup(
        Match& match,
        const Lineup&) {

    match.clearLineups();
}

Map<Player*, unsigned>
CommandLineInterpreter::listTopScorers(
        Team& team) {

    static Map<Player*, unsigned> scorers;

    for (auto player : team.getPlayers()) {

        scorers.add(
                player,
                player->getStats().scoredGoals);
    }

    return scorers;
}

Team::Statistics CommandLineInterpreter::listTeamStats(Team &team){
    return team.getStats();
}

void CommandLineInterpreter::viewPlayerRanking(
        Championship& championship) {

    for (auto team : championship.getTeamManager().getTeams()) {
        for (auto player : team->getPlayers()) {

            std::cout
                    << player->getName()
                    << " "
                    << player->getStats().scoredGoals
                    << '\n';
        }
    }
}

Map<Team*, Team::Statistics> CommandLineInterpreter::listSeasonStats(Championship &championship) {
    Map<Team*, Team::Statistics> stats;
    for (auto team :
         championship.getTeamManager().getTeams()) {

        stats.add(team, team->getStats());
         }
    return stats;
}

Map<Player*, Player::Statistics> CommandLineInterpreter::listPlayerStats(const Team &team) {
    auto stats = Map<Player*, Player::Statistics>();
    for ( const auto& player: team.getPlayers()) {
        stats.add(player, player->getStats());
    }

    return stats;
}

const Team&
CommandLineInterpreter::getChampion(
        const Championship& championship) {

    Map<Team*, unsigned> champs = Map<Team*, unsigned>();

    for (const auto& team : championship.getTeamManager().getTeams())
    {
        champs.add(team, team->getStats().scoredGoals);
    }

    // sort by goals (descending)
    champs.sortBy([](Team* a, Team* b)
    {
        return a->getStats().scoredGoals > b->getStats().scoredGoals;
    });

    const auto& data = champs.getData();

    if (data.size() < 3) {
        throw std::invalid_argument(toString(ExceptionMessages::INVALID_NUMBER_OF_TEAMS)); // here has memory leak but how to solve it
    }

    return *data[0].first; // 1st place
}

const Team& CommandLineInterpreter::getRunnerUp(const Championship &championship) {
    Map<Team*, unsigned> champs;

    for (const auto& team : championship.getTeamManager().getTeams())
    {
        champs.add(team, team->getStats().scoredGoals);
    }

    // sort by goals (descending)
    champs.sortBy([](Team* a, Team* b)
    {
        return a->getStats().scoredGoals > b->getStats().scoredGoals;
    });

    const auto& data = champs.getData();

    if (data.size() < 3)
        throw std::invalid_argument(toString(ExceptionMessages::INVALID_NUMBER_OF_TEAMS));

    return *data[1].first; // 2nd place
}

const Team& CommandLineInterpreter::getThirdPlace(const Championship &championship)
{
    Map<Team*, unsigned> champs;

    for (const auto& team : championship.getTeamManager().getTeams())
    {
        champs.add(team, team->getStats().scoredGoals);
    }

    // sort by goals (descending)
    champs.sortBy([](Team* a, Team* b)
    {
        return a->getStats().scoredGoals > b->getStats().scoredGoals;
    });

    const auto& data = champs.getData();

    if (data.size() < 3)
        throw std::invalid_argument(toString(ExceptionMessages::INVALID_NUMBER_OF_TEAMS));

    return *data[2].first; // 3rd place
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
    std::cout << "Select host or guest lineup as typing 'host' or 'guest': ";
    std::string lineup;
    while(lineup != "host" && lineup != "guest") {
        std::cin >> lineup;
    }

    if (lineup == "host") {
        match.getHost()->getStats().scoredGoals += 1;
        match.getGuest()->getStats().concededGoals += 1;
    } else {
        match.getGuest()->getStats().scoredGoals += 1;
        match.getHost()->getStats().concededGoals += 1;
    }
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

void CommandLineInterpreter::cleanup()
{
    delete championship;
    championship = nullptr;

    delete history;
    history = nullptr;

    delete simulator;
    simulator = nullptr;
}

void CommandLineInterpreter::execute(Command command, std::vector<std::string> args) {
    switch (command)
    {
        case Command::MENU: {
            menu();
            break;
        }

        case Command::HELP: {
            if (args.empty()) throw std::invalid_argument("Invalid argument");
            help(args[0]);
            break;
        }

        case Command::EXIT: {
            cleanup();
            std::cout << "Exiting program...\n";
            break;
        }

        // =====================
        // SEASONS
        // =====================
        case Command::LIST_SEASONS: {
            std::cout << "Seasons:\n";
            listSeasons(*history);
            break;
        }

        case Command::SHOW_PODIUM: {
            if(championship == nullptr) {
                std::cout << "The current championship is not started yet.\n";
                return;
            }

            try {
                showPodium(*championship);
            } catch (...) {
                delete championship;
                delete history;
                delete simulator;
                throw;
            }
            break;
        }

        case Command::FINISH_SEASON: {
            finishSeason(*history, *championship);
            break;
        }

        case Command::GET_CHAMPION: {
            try {
                std::cout << getChampion(*championship).getName() << "\n";
            } catch(...) {
                delete championship;
                delete history;
                delete simulator;
                throw;
            }
            break;
        }

        case Command::GET_RUNNER_UP: {
            std::cout << getRunnerUp(*championship).getName() << "\n";
            break;
        }

        case Command::GET_THIRD_PLACE: {
            std::cout << getThirdPlace(*championship).getName() << "\n";
            break;
        }

        // =====================
        // MATCHES
        // =====================
        case Command::PLAY_MATCH: {
            playMatch(*simulator, 0); // placeholder index
            break;
        }

        case Command::VIEW_MATCHES: {
            viewMatches(*championship);
            break;
        }

        case Command::ENTER_MATCH_RESULT: {
            // you must select match properly
            enterMatchResult(championship->getMatches()[0]);
            break;
        }

        case Command::SIMULATE_GOAL: {
            simulateGoal(championship->getMatches()[0]);
            break;
        }

        // =====================
        // TEAMS
        // =====================
        case Command::LIST_TEAMS: {
            listTeams(*championship);
            break;
        }

        case Command::ADD_TEAM: {
            if (args.empty()) throw std::invalid_argument("Missing args");
            addTeam(args, *championship);
            break;
        }

        case Command::REMOVE_TEAM: {
            if (args.empty()) throw std::invalid_argument("Missing args");
            removeTeam(args[0], *championship);
            break;
        }

        case Command::LIST_TEAM_STATS: {
            for (auto t : championship->getTeamManager().getTeams()) {
                listTeamStats(*t);
            }
            break;
        }

        // =====================
        // PLAYERS
        // =====================
        case Command::ADD_PLAYER: {
            if (args.empty()) throw std::invalid_argument("Missing args.");
            if(args.size() != 6) throw std::invalid_argument("Invalid args count.");

            std::string teamName = args[0];
            Team* team = nullptr;
            for(auto currTeam : championship->getTeamManager().getTeams()) {
                if(currTeam->getName() == teamName) {
                    team = currTeam;
                    break;
                }
            }
            if(team == nullptr) {
                throw std::invalid_argument(toString(ExceptionMessages::TEAM_NOT_FOUND));
            }
            // const std::string& name, unsigned number, Position position, double salary, double transferSum
            Player player = Player(args[1], std::atoi(args[2].c_str()), toPosition(args[3]),
                std::atof(args[4].c_str()), std::atof(args[5].c_str()));
            addPlayer(player, *team);
            break;
        }

        case Command::REMOVE_PLAYER: {
            auto teams = championship->getTeamManager().getTeams();
            Team* t = nullptr;
            for (auto team : teams) {
                if(team->getName() == args[1]) {
                    t = team;
                }
            }
            if (t == nullptr) throw std::invalid_argument("No team with this name.");
            removePlayer(args[0], *t);
            break;
        }

        case Command::TRANSFER_PLAYERS: {
            auto teams = championship->getTeamManager().getTeams();
            Team* t1 = nullptr; Team* t2 = nullptr;
            for (auto team : teams) {
                if(team->getName() == args[1]) {
                    t1 = team;
                }
                if(team->getName() == args[2]) {
                    t2 = team;
                }
            }
            if (t1 == nullptr || t2 == nullptr) throw std::invalid_argument("No teams with these names.");
            transferPlayers(*t1, *t2);
            break;
        }

        case Command::VIEW_PLAYER: {
            viewPlayer(args[0], *championship);
            break;
        }

        case Command::LIST_PLAYERS: {
            for(auto t : championship->getTeamManager().getTeams()) {
                listPlayers(*t);
            }
            break;
        }

        case Command::UPDATE_SALARY: {
            Player* player = nullptr;
            for(auto t : championship->getTeamManager().getTeams()) {
                for(auto p : t->getPlayers()) {
                    if(p->getName() == args[0]) {
                        player = p;
                        break;
                    }
                }
            }
            if(player == nullptr) throw std::invalid_argument("No player with this name.");
            updateSalary(*championship, *player);
            break;
        }

        case Command::LIST_TOP_SCORERS:
        case Command::GET_TOP_SCORERS: {
            for (auto t : championship->getTeamManager().getTeams()) {
                listTopScorers(*t);
            }
            break;
        }

        case Command::VIEW_PLAYER_RANKING: {
            viewPlayerRanking(*championship);
            break;
        }

        case Command::LIST_PLAYER_STATS: {
            for(auto t : championship->getTeamManager().getTeams()) {
                listPlayerStats(*t);
            }
            break;
        }

        case Command::AUTO_SELECT_LINEUP: {
            autoSelectLineup(championship->getMatches()[0]);
            break;
        }

        case Command::DELETE_LINEUP: {
            Lineup* lineup = nullptr;
            Match* match = nullptr;
            for (const auto& m : championship->getMatches()) {
                if(m.getHost()->getName() == args[0]) {
                    try {
                        match = new Match(m);
                        lineup = new Lineup(m.getHost());
                        deleteLineup(*match, *lineup);
                        continue;
                    } catch(...) {
                        delete match;
                        delete lineup;
                        throw;
                    }
                }
                if (m.getGuest()->getName() == args[0]) {
                    try {
                        match = new Match(m);
                        lineup = new Lineup(m.getGuest());
                        deleteLineup(*match, *lineup);
                    } catch(...) {
                        delete match;
                        delete lineup;
                        throw;
                    }
                }
            }
            break;
        }

        case Command::EXPORT_DATA: {
            exportData(*history, !args.empty() ? args[0] : "out.dat");
            break;
        }

        case Command::IMPORT_DATA: {
            importData(!args.empty() ? args[0] : "in.dat");
            break;
        }

        case Command::LIST_SEASON_STATS: {
            listSeasonStats(*championship);
            break;
        }

        case Command::UNKNOWN:
        default: {
            throw std::invalid_argument("Invalid command");
        }
    }
}
