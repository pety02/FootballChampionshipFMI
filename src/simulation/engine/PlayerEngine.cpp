//
// Created by User on 6/19/2026.
//

#include "PlayerEngine.h"

#include "../../utils/validator/CommandLineValidator.h"

void PlayerEngine::addPlayer(const std::string& playerName, Lineup& lineup) {
    for(const Player& p : lineup.getTeam()->getPlayers()) {
        if(p.getName() == playerName) {
            lineup.addPlayer(p);
            break;
        }
    }
}

void PlayerEngine::addPlayer(Player& player, Team &team) {
    CommandLineValidator::validateUniquePlayerName(player.getName(), team);

    team.addPlayer(player, false);
}

void PlayerEngine::removePlayer(const std::string &playerName, Team &team) {
    team.removePlayer(playerName);
}

void PlayerEngine::transferPlayers(
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

    Player p1;
    Player p2;

    for (const Player& p : firstTeam.getPlayers()) {

        if (p.getName() == firstPlayer) {

            p1 = p;
            break;
        }
    }

    for (const Player& p : secondTeam.getPlayers()) {

        if (p.getName() == secondPlayer) {

            p2 = p;
            break;
        }
    }

    firstTeam.removePlayer(firstPlayer);
    secondTeam.removePlayer(secondPlayer);

    firstTeam.addPlayer(p2, true);
    secondTeam.addPlayer(p1, true);
}

void PlayerEngine::viewPlayer(const std::string &playerName, const Championship& championship) {
    Player player;
    for(const Team* t : championship.getTeamManager().getTeams()) {
        for(const Player& p : t->getPlayers()) {
            if(p.getName() == playerName) {
                player = p;
                break;
            }
        }
    }

    std::cout << "Player: { name: " << player.getName() << ", number: " << player.getNumber() << ", position: ";

    switch (player.getPosition()) {
        case Player::Position::GOALKEEPER: std::cout << "Goalkeeper"; break;
        case Player::Position::DEFENDER: std::cout << "Defender"; break;
        case Player::Position::MIDFIELDER: std::cout << "Midfielder"; break;
        case Player::Position::WINGER: std::cout << "Winger"; break;
        case Player::Position::FORWARD: std::cout << "Forward"; break;
        default: std::cout << "Unknown"; break;
    }

    std::cout << ", salary: " << player.getSalary() << ", transferSum: " << player.getTransferSum() << ", stats: { matchesCount: "
    << player.getStats().matchesCount << ", scoredGoals: " << player.getStats().scoredGoals << " } }" << std::endl;
}

std::vector<Player> PlayerEngine::listPlayers(const Team &team) {
    return team.getPlayers();
}

void PlayerEngine::updateSalary(Championship& championship, Player& player) {
    Team* playsIn = nullptr;
    for(const Match& currMatch : championship.getMatches()) {
        Team* host = currMatch.getHost();
        Team* guest = currMatch.getGuest();

        try {
            CommandLineValidator::validateIsHomePlayer(player.getName(), *host);
            playsIn = host;
        } catch (...) {
            CommandLineValidator::validateIsGuestPlayer(player.getName(), *guest);
            playsIn = guest;
        }
    }

    if (playsIn == nullptr) {
        return;
    }
    AccountingManager::regulateSalary(player, *playsIn);
}