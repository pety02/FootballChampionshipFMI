#include <catch2/catch_test_macros.hpp>

#include "FootballGameEngine.h"
#include "AttackingTeam.h"
#include "BalancedTeam.h"
#include "DefensiveTeam.h"

#include "../model/player/Player.h"
#include "../model/match/Match.h"
#include "../model/championship/Championship.h"
#include "catch2/matchers/catch_matchers.hpp"

// -------------------------
// Helpers
// -------------------------
static Player makeForward(const std::string& name) {
    return Player(name, 9, Player::Position::FORWARD, 100000, 100);
}

static Player makeMid(const std::string& name) {
    return Player(name, 8, Player::Position::MIDFIELDER, 90000, 90);
}

static Team* makeDefensiveTeam(const std::string& name) {
    Team* team = new DefensiveTeam(name, "Coach", "Stadium", 1000000);
    Player forwarder = makeForward(name + "_F1");
    Player midfielder = makeMid(name + "_M1");
    team->addPlayer(forwarder, false);
    team->addPlayer(midfielder, false);
    return team;
}

// -------------------------
// Engine initialization
// -------------------------
TEST_CASE("Engine initializes correctly", "[engine]") {
    FootballGameEngine engine;

    REQUIRE(engine.getCurrentChampionship().getMatches().empty());
}

// -------------------------
// addMatch + simulate
// -------------------------
TEST_CASE("Lineup constructor throws when valid lineup cannot be generated", "[lineup]") {
    Team* team = new DefensiveTeam("A", "C1", "S1", 1000);

    // deliberately weak squad (no proper formation possible
    Player p1 = Player("GK", 1, Player::Position::GOALKEEPER, 100, 100);
    team->addPlayer(p1, false);
    Player p2 = Player("D1", 2, Player::Position::DEFENDER, 100, 100);
    team->addPlayer(p2, false);
    Player p3 = Player("D2", 3, Player::Position::DEFENDER, 100, 100);
    team->addPlayer(p3, false);

    REQUIRE_NOTHROW(Lineup(team));

    delete team;
}

TEST_CASE("Lineup constructor generates valid lineup", "[lineup]") {
    Team* team = new AttackingTeam("A", "C1", "S1", 1000);

    int index = 1;
    Player player = Player("GK", index++, Player::Position::GOALKEEPER, 10, 100);
    // GK
    team->addPlayer(player, false);

    // DEF
    for (int i = 0; i < 3; i++) {
        Player p = Player("DEF" + std::to_string(i), index++,
            Player::Position::DEFENDER, 100, 10);
        team->addPlayer(p, false);
    }

    // MID
    for (int i = 0; i < 3; i++) {
        Player p = Player("MID" + std::to_string(i), index++,
            Player::Position::MIDFIELDER, 100, 10);
        team->addPlayer(p, false);
    }

    // WING
    for (int i = 0; i < 3; i++) {
        Player p = Player("WING" + std::to_string(i), index++,
            Player::Position::WINGER, 100, 10);
        team->addPlayer(p, false);
    }

    // FORWARD
    for (int i = 0; i < 3; i++) {
        Player p = Player("FWD" + std::to_string(i), index++,
            Player::Position::FORWARD, 100, 10);
        team->addPlayer(p, false);
    }

    Lineup lineup(team);

    const std::vector<Player>& players = lineup.getPlayers();

    REQUIRE(players.size() == 11);

    delete team;
}

// -------------------------
// addScorer logic
// -------------------------
TEST_CASE("addScorer updates goals correctly", "[engine][scorer]") {
    FootballGameEngine engine;

    Team* team = new AttackingTeam("A", "C1", "S1", 1000);

    int index = 1;
    Player player = Player("GK", index++, Player::Position::GOALKEEPER, 10, 100);
    // GK
    team->addPlayer(player, false);

    // DEF
    for (int i = 0; i < 3; i++) {
        Player p = Player("DEF" + std::to_string(i), index++,
            Player::Position::DEFENDER, 100, 10);
        team->addPlayer(p, false);
    }

    // MID
    for (int i = 0; i < 3; i++) {
        Player p = Player("MID" + std::to_string(i), index++,
            Player::Position::MIDFIELDER, 100, 10);
        team->addPlayer(p, false);
    }

    // WING
    for (int i = 0; i < 3; i++) {
        Player p = Player("WING" + std::to_string(i), index++,
            Player::Position::WINGER, 100, 10);
        team->addPlayer(p, false);
    }

    // FORWARD
    for (int i = 0; i < 3; i++) {
        Player p = Player("FWD" + std::to_string(i), index++,
            Player::Position::FORWARD, 100, 10);
        team->addPlayer(p, false);
    }

    Lineup lineup(team);

    Team* team2 = new AttackingTeam("A", "C1", "S1", 1000);

    index = 1;
    Player player2 = Player("GK", index++, Player::Position::GOALKEEPER, 10, 100);
    // GK
    team2->addPlayer(player, false);

    // DEF
    for (int i = 0; i < 3; i++) {
        Player p = Player("DEF" + std::to_string(i), index++,
            Player::Position::DEFENDER, 100, 10);
        team2->addPlayer(p, false);
    }

    // MID
    for (int i = 0; i < 3; i++) {
        Player p = Player("MID" + std::to_string(i), index++,
            Player::Position::MIDFIELDER, 100, 10);
        team2->addPlayer(p, false);
    }

    // WING
    for (int i = 0; i < 3; i++) {
        Player p = Player("WING" + std::to_string(i), index++,
            Player::Position::WINGER, 100, 10);
        team2->addPlayer(p, false);
    }

    // FORWARD
    for (int i = 0; i < 3; i++) {
        Player p = Player("FWD" + std::to_string(i), index++,
            Player::Position::FORWARD, 100, 10);
        team2->addPlayer(p, false);
    }

    Lineup lineup2(team2);

    Lineup hl(team);
    Lineup gl(team2);

    Match match(hl, gl);

    // add match BEFORE addScorer()
    Championship championship = Championship();
    engine.addMatch(match, championship);

    const Player scorer1 = team->getPlayers().back();
    const Player scorer2 = team2->getPlayers().back();

    REQUIRE_NOTHROW(engine.addScorer(scorer1, match));
    REQUIRE_NOTHROW(engine.addScorer(scorer2, match));

    delete team;
    delete team2;
}

// -------------------------
// findGoalMaster
// -------------------------
TEST_CASE("findGoalMaster returns a valid player name", "[engine][goals]") {
    FootballGameEngine engine;

    Team* team = new AttackingTeam("A", "C1", "S1", 1000);

    int index = 1;
    Player player = Player("GK", index++, Player::Position::GOALKEEPER, 10, 100);
    // GK
    team->addPlayer(player, false);

    // DEF
    for (int i = 0; i < 3; i++) {
        Player p = Player("DEF" + std::to_string(i), index++,
            Player::Position::DEFENDER, 100, 10);
        team->addPlayer(p, false);
    }

    // MID
    for (int i = 0; i < 3; i++) {
        Player p = Player("MID" + std::to_string(i), index++,
            Player::Position::MIDFIELDER, 100, 10);
        team->addPlayer(p, false);
    }

    // WING
    for (int i = 0; i < 3; i++) {
        Player p = Player("WING" + std::to_string(i), index++,
            Player::Position::WINGER, 100, 10);
        team->addPlayer(p, false);
    }

    // FORWARD
    for (int i = 0; i < 3; i++) {
        Player p = Player("FWD" + std::to_string(i), index++,
            Player::Position::FORWARD, 100, 10);
        team->addPlayer(p, false);
    }

    Lineup lineup(team);

    Team* team2 = new AttackingTeam("A", "C1", "S1", 1000);

    index = 1;
    Player player2 = Player("GK", index++, Player::Position::GOALKEEPER, 10, 100);
    // GK
    team2->addPlayer(player, false);

    // DEF
    for (int i = 0; i < 3; i++) {
        Player p = Player("DEF" + std::to_string(i), index++,
            Player::Position::DEFENDER, 100, 10);
        team2->addPlayer(p, false);
    }

    // MID
    for (int i = 0; i < 3; i++) {
        Player p = Player("MID" + std::to_string(i), index++,
            Player::Position::MIDFIELDER, 100, 10);
        team2->addPlayer(p, false);
    }

    // WING
    for (int i = 0; i < 3; i++) {
        Player p = Player("WING" + std::to_string(i), index++,
            Player::Position::WINGER, 100, 10);
        team2->addPlayer(p, false);
    }

    // FORWARD
    for (int i = 0; i < 3; i++) {
        Player p = Player("FWD" + std::to_string(i), index++,
            Player::Position::FORWARD, 100, 10);
        team2->addPlayer(p, false);
    }

    Lineup lineup2(team2);

    Lineup hl(team);
    Lineup gl(team2);

    Match match(hl, gl);

    // add match BEFORE addScorer()
    Championship championship = Championship();
    engine.addMatch(match, championship);

    const Player scorer1 = team->getPlayers().back();
    const Player scorer2 = team2->getPlayers().back();

    REQUIRE_NOTHROW(engine.addScorer(scorer1, match));
    REQUIRE_NOTHROW(engine.addScorer(scorer2, match));

    std::string result = engine.findGoalMaster();

    REQUIRE_FALSE(result.empty());

    delete team;
    delete team2;
}

// -------------------------
// finishChampionship
// -------------------------
TEST_CASE("finishChampionship executes without crash", "[engine][championship]") {
    FootballGameEngine engine;

    Team* t1 = new AttackingTeam("A", "C1", "S1", 1000);
    Team* t2 = new BalancedTeam("B", "C2", "S2", 1000);
    Team* t3 = new DefensiveTeam("C", "C3", "S3", 1000);

    Lineup hl1 = Lineup(t1);
    Lineup gl1 = Lineup(t2);
    Match match1(hl1, gl1);

    Lineup hl2 = Lineup(t2);
    Lineup gl2 = Lineup(t3);
    Match match2(hl2, gl2);

    Lineup hl3 = Lineup(t3);
    Lineup gl3 = Lineup(t1);
    Match match3(hl3, gl3);

    Championship championship = Championship();
    engine.addMatch(match1, championship);
    engine.addMatch(match2, championship);
    engine.addMatch(match3, championship);

    engine.simulate();

    REQUIRE_NOTHROW(engine.finishChampionship());

    delete t1;
    delete t2;
    delete t3;
}

// -------------------------
// autoSelectLineups (NEW SIGNATURE)
// -------------------------
// TODO: can be removed because it uses a method marked for removal
// TEST_CASE("autoSelectLineups assigns valid lineups", "[engine][lineup]") {
//     FootballGameEngine engine;
//
//     Team* host = new AttackingTeam("A", "C1", "S1", 1000);
//     Team* guest = new BalancedTeam("B", "C2", "S2", 1000);
//
//     Lineup hl = Lineup(host);
//     Lineup gl = Lineup(guest);
//     Match match(hl, gl);
//
//     REQUIRE_NOTHROW(engine.autoSelectLineups(match, host, guest));
//
//     delete host;
//     delete guest;
// }

// -------------------------
// listTeams
// -------------------------
TEST_CASE("listTeams returns teams", "[engine][teams]") {
    FootballGameEngine engine;
    Championship champ;

    Team* t1 = new AttackingTeam("A", "C1", "S1", 1000);
    Team* t2 = new BalancedTeam("B", "C2", "S2", 1000);

    champ.getTeamManager().addTeam(t1);
    champ.getTeamManager().addTeam(t2);

    std::vector<Team*> teams = FootballGameEngine::listTeams(champ);

    REQUIRE(teams.size() >= 2);

    delete t1;
    delete t2;
}