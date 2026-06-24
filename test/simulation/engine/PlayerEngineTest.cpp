#include <BalancedTeam.h>
#include <DefensiveTeam.h>
#include <sstream>
#include <iostream>

#include "PlayerEngine.h"
#include "catch2/catch_test_macros.hpp"

// Helpers (adjust to your actual constructors / API)
Player makePlayer(const std::string& name, int number = 10,
    Player::Position pos = Player::Position::FORWARD, double salary = 100.0,
    double transferSum = 5.0) {

    Player p = Player(name, number, pos, salary, transferSum);
    return p;
}

TEST_CASE("PlayerEngine::addPlayer(Player, Team) adds player after validation") {
    PlayerEngine engine;

    Team* team = nullptr;
    Player p = makePlayer("Ronaldo");

    REQUIRE_NOTHROW(engine.addPlayer(p, *team));

    bool found = false;
    for (const Player& pl : team->getPlayers()) {
        if (pl.getName() == "Ronaldo") found = true;
    }

    REQUIRE(found);

    delete team;
}

TEST_CASE("PlayerEngine::removePlayer removes player from team") {
    PlayerEngine engine;

    Team* team = nullptr;
    Player p = makePlayer("Neymar");
    team->addPlayer(p, false);

    engine.removePlayer("Neymar", *team);

    REQUIRE(team->getPlayers().empty());

    delete team;
}

TEST_CASE("PlayerEngine::listPlayers returns all team players") {
    PlayerEngine engine;

    Team* team = nullptr;
    Player p1 = makePlayer("A");
    Player p2 = makePlayer("B");
    team->addPlayer(p1, false);
    team->addPlayer(p2, false);

    std::vector<Player> players = engine.listPlayers(*team);

    REQUIRE(players.size() == 2);

    delete team;
}

TEST_CASE("PlayerEngine::transferPlayers swaps players between teams", "[interactive]") {
    PlayerEngine engine;

    Team* t1 = new BalancedTeam("TeamA", "CoachA", "StadiumA", 500000);
    Team* t2 = new DefensiveTeam("TeamB", "CoachB", "StadiumB", 500000);

    Player p1 = makePlayer("P1");
    t1->addPlayer(p1, false);
    Player p2 = makePlayer("P2");
    t2->addPlayer(p2, false);

    // Redirect std::cin input
    std::istringstream input("P1 P2\n");
    std::cin.rdbuf(input.rdbuf());

    engine.transferPlayers(*t1, *t2);

    bool t1HasP2 = false;
    bool t2HasP1 = false;

    for (const Player& p : t1->getPlayers())
        if (p.getName() == "P2") t1HasP2 = true;

    for (const Player& p : t2->getPlayers())
        if (p.getName() == "P1") t2HasP1 = true;

    REQUIRE(t1HasP2);
    REQUIRE(t2HasP1);

    delete t1;
    delete t2;
}

TEST_CASE("PlayerEngine::viewPlayer prints player info", "[output]") {
    PlayerEngine engine;

    Championship c;
    Team* team = nullptr;

    Player p = makePlayer("Messi");
    team->addPlayer(p, false);

    c.getTeamManager().addTeam(team);

    std::ostringstream output;
    std::streambuf* old = std::cout.rdbuf(output.rdbuf());

    engine.viewPlayer("Messi", c);

    std::cout.rdbuf(old);

    std::string out = output.str();

    REQUIRE(out.find("Messi") != std::string::npos);
    REQUIRE(out.find("Player:") != std::string::npos);

    delete team;
}

TEST_CASE("PlayerEngine::updateSalary does nothing if player not found") {
    PlayerEngine engine;

    Championship c;
    Player p = makePlayer("Ghost");

    REQUIRE_NOTHROW(engine.updateSalary(c, p));
}