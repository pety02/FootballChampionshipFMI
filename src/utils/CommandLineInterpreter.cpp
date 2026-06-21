//
// Created by User on 6/4/2026.
//

#include "CommandLineInterpreter.h"
#include <iostream>
#include "../simulation/engine/FootballGameEngine.h"
#include "ExceptionMessages.h"
#include "../simulation/engine/StatisticsEngine.h"
#include <fstream>
#include "../simulation/engine/PlayerEngine.h"
#include "../simulation/engine/SystemCommandsEngine.h"
#include "Utils.h"

void CommandLineInterpreter::execute(const Command command, const std::vector<std::string> &args) {
    switch (command)
    {
        case Command::MENU: {
            SystemCommandsEngine::menu();
            break;
        }

        case Command::HELP: {
            if (args.empty()) throw std::invalid_argument("Invalid argument");
                SystemCommandsEngine::help(args[0]);
            break;
        }

        case Command::EXIT: {
            SystemCommandsEngine::terminateProgram();
            break;
        }

        // =====================
        // SEASONS
        // =====================
        case Command::LIST_SEASONS: {
            std::cout << "Seasons:\n";
            FootballGameEngine::listSeasons(history);
            break;
        }

        case Command::SHOW_PODIUM: {
            FootballGameEngine::showPodium(championship);
            break;
        }

        case Command::FINISH_SEASON: {
            FootballGameEngine::finishSeason(history, championship);
            break;
        }

        case Command::GET_CHAMPION: {
            std::cout << StatisticsEngine::getChampion(championship).getName() << "\n";
            break;
        }

        case Command::GET_RUNNER_UP: {
            std::cout << StatisticsEngine::getRunnerUp(championship).getName() << "\n";
            break;
        }

        case Command::GET_THIRD_PLACE: {
            std::cout << StatisticsEngine::getThirdPlace(championship).getName() << "\n";
            break;
        }

        // =====================
        // MATCHES
        // =====================
        case Command::PLAY_MATCH: {

            break;
        }

        case Command::VIEW_MATCHES: {
            FootballGameEngine::viewMatches(championship);
            break;
        }

        case Command::ENTER_MATCH_RESULT: {
            // you must select match properly
            FootballGameEngine::enterMatchResult(championship.getMatches()[0]);
            break;
        }

        case Command::SIMULATE_GOAL: {
            FootballGameEngine::simulateGoal(championship.getMatches()[0]);
            break;
        }

        // =====================
        // TEAMS
        // =====================
        case Command::LIST_TEAMS: {
            FootballGameEngine::listTeams(championship);
            break;
        }

        case Command::ADD_TEAM: {
            if (args.empty()) throw std::invalid_argument("Missing args");
            FootballGameEngine::addTeam(args, championship);
            break;
        }

        case Command::ADD_MANAGER: {
            if (args.empty()) throw std::invalid_argument("Missing args");
            TeamManager teamManager = TeamManager();
            teamManager.setName(args[0]);
            for(const Match& match : championship.getMatches()) {
                FootballGameEngine::addManager(match.getHost(), teamManager);
                FootballGameEngine::addManager(match.getGuest(), teamManager);
                championship.setTeamManager(teamManager);
            }
            break;
        }

        case Command::ADD_MATCH: {
            if (args.empty()) throw std::invalid_argument("Missing args");
            if(args.size() < 2) throw std::invalid_argument("Invalid args size");

            const std::string& hostName = args[0];
            const std::string& guestName = args[1];
            Lineup hostLineup, guestLineup;
            for(Team* team : championship.getTeamManager().getTeams()) {
                if(team->getName() == hostName) {
                    std::cout << "Auto selecting a host lineup that will play in the match..." << std::endl;
                    hostLineup = Lineup(team);
                    continue;
                }
                if(team->getName() == guestName) {
                    std::cout << "Auto selecting a guest lineup that will play in the match..." << std::endl;
                    guestLineup = Lineup(team);
                    continue;
                }
            }
            Match match = Match(hostLineup, guestLineup);
            FootballGameEngine::addMatch(match, championship);
            break;
        }

        case Command::REMOVE_TEAM: {
            if (args.empty()) throw std::invalid_argument("Missing args");
            FootballGameEngine::removeTeam(args[0], championship);
            break;
        }

        case Command::LIST_TEAM_STATS: {
            for (Team* t : championship.getTeamManager().getTeams()) {
                StatisticsEngine::listTeamStats(*t);
            }
            break;
        }

        // =====================
        // PLAYERS
        // =====================
        case Command::ADD_PLAYER: {
            if (args.empty()) throw std::invalid_argument("Missing args.");
            if(args.size() != 6) throw std::invalid_argument("Invalid args count.");

            const std::string& teamName = args[0];
            Team* team = nullptr;
            for(Team* currTeam : championship.getTeamManager().getTeams()) {
                if(currTeam->getName() == teamName) {
                    team = currTeam;
                    break;
                }
            }
            if(team == nullptr) {
                throw std::invalid_argument(toString(ExceptionMessages::TEAM_NOT_FOUND));
            }
            // const std::string& name, unsigned number, Position position, double salary, double transferSum
            Player player = Player(args[1], std::atoi(args[2].c_str()), Utils::toPosition(args[3]),
                std::atof(args[4].c_str()), std::atof(args[5].c_str()));
            PlayerEngine::addPlayer(player, *team);
            break;
        }

        case Command::REMOVE_PLAYER: {
            std::vector<Team*> teams = championship.getTeamManager().getTeams();
            Team* t = nullptr;
            for (Team* team : teams) {
                if(team->getName() == args[1]) {
                    t = team;
                }
            }
            if (t == nullptr) throw std::invalid_argument("No team with this name.");
            PlayerEngine::removePlayer(args[0], *t);
            break;
        }

        case Command::TRANSFER_PLAYERS: {
            std::vector<Team*> teams = championship.getTeamManager().getTeams();
            Team* t1 = nullptr; Team* t2 = nullptr;
            for (Team* team : teams) {
                if(team->getName() == args[1]) {
                    t1 = team;
                }
                if(team->getName() == args[2]) {
                    t2 = team;
                }
            }
            if (t1 == nullptr || t2 == nullptr) throw std::invalid_argument("No teams with these names.");
            PlayerEngine::transferPlayers(*t1, *t2);
            break;
        }

        case Command::VIEW_PLAYER: {
            PlayerEngine::viewPlayer(args[0], championship);
            break;
        }

        case Command::LIST_PLAYERS: {
            for(Team* t : championship.getTeamManager().getTeams()) {
                PlayerEngine::listPlayers(*t);
            }
            break;
        }

        case Command::UPDATE_SALARY: {
            Player player;
            for(Team* t : championship.getTeamManager().getTeams()) {
                for(const Player& p : t->getPlayers()) {
                    if(p.getName() == args[0]) {
                        player = p;
                        break;
                    }
                }
            }
            PlayerEngine::updateSalary(championship, player);
            break;
        }

        case Command::LIST_TOP_SCORERS:
        case Command::GET_TOP_SCORERS: {
            for (Team* t : championship.getTeamManager().getTeams()) {
                FootballGameEngine::listTopScorers(*t);
            }
            break;
        }

        case Command::VIEW_PLAYER_RANKING: {
            StatisticsEngine::viewPlayerRanking(championship);
            break;
        }

        case Command::LIST_PLAYER_STATS: {
            for(Team* t : championship.getTeamManager().getTeams()) {
                StatisticsEngine::listPlayerStats(*t);
            }
            break;
        }

        case Command::DELETE_LINEUP: {
            Match* match = nullptr;
            for (const Match& m : championship.getMatches()) {
                FootballGameEngine::deleteLineups(*match);
            }
            break;
        }

        case Command::EXPORT_DATA: {
            SystemCommandsEngine::exportData(history, !args.empty() ? args[0] : "out.dat");
            break;
        }

        case Command::IMPORT_DATA: {
            SystemCommandsEngine::importData(history, !args.empty() ? args[0] : "in.dat");
            std::cout << "IMPORTED DATA:" << std::endl;
            for(const Championship& record : history) {
                std::cout << record;
            }
            break;
        }

        case Command::LIST_SEASON_STATS: {
            StatisticsEngine::listSeasonStats(championship);
            break;
        }

        case Command::UNKNOWN:
        default: {
            throw std::invalid_argument("Invalid command");
        }
    }
}
