//
// Created by User on 5/17/2026.
//

#ifndef FOOTBALLGAMEENGINE_H
#define FOOTBALLGAMEENGINE_H

#include <string>

#include "../../model/championship/history/ChampionshipHistory.h"
#include "../../model/match/Match.h"
#include "../../model/player/Player.h"

/**
 * Core simulation engine for running football championships.
 *
 * This class is responsible for:
 * - Creating and managing a championship lifecycle
 * - Simulating matches
 * - Tracking results and statistics
 * - Determining final rankings (champion, vice-champion, etc.)
 */
class FootballGameEngine {
private:
    ChampionshipHistory championshipHistory = ChampionshipHistory();
    Championship currentChampionship = Championship();

    std::string champion = std::string();
    std::string viceChampion = std::string();
    std::string bronzeTeam = std::string();
    std::string goalMaster = std::string();

    /**
     * Retrieves the list of championship winners across history.
     *
     * @return Vector of champion team names.
     */
    [[nodiscard]] std::vector<std::string> getChampions() const;

public:
    /**
     * Default constructor.
     */
    FootballGameEngine();

    /**
     * Determines the player with the highest number of goals
     * across the championship.
     *
     * @return Name of the top scorer.
     */
    std::string findGoalMaster();

    /**
     * Initializes and creates a new championship.
     *
     * Allocates and prepares all required data structures for simulation.
     */
    void simulate();

    /**
     * Adds a match to the current championship.
     *
     * @param match Match to be added.
     *
     * @throws std::invalid_argument If no championship is active.
     */
    static void addMatch(const Match &match, Championship& championship);

    /**
     * Advances the championship to the next round.
     */
    void updateChampionshipRound();

    /**
     * Finalizes the current championship and computes final rankings.
     */
    void finishChampionship();

    /**
     * Simulates a single match.
     *
     * @param match Pointer to the match to simulate.
     */
    void play(const Match &match) const;

    /**
     * Records a goal scored by a player in a match.
     *
     * @param player Pointer to the scoring player.
     * @param match Reference to the match where the goal occurred.
     */
    void addScorer(const Player &player, Match &match) const;

    /**
     * Increments the home team's goal count in a match.
     *
     * @param match The match to update.
     */
    static void increaseHostGoals(const Match &match);

    /**
     * Increments the guest team's goal count in a match.
     *
     * @param match The match to update.
     */
    static void increaseGuestGoals(const Match &match);

    /**
     * Marks a match as finished and finalizes its result.
     *
     * @param match Match to finalize.
     */
    void finishMatch(Match &match);

    /**
     * Gets the currently active championship.
     *
     * @return Constant reference to the championship.
     */
    [[nodiscard]] const Championship &getCurrentChampionship() const;

    static std::vector<Championship> listSeasons(const ChampionshipHistory &championshipHistory); // simulator

    static void playAllMatches(Championship &championship); // simulator

    static void showPodium(const Championship &championship); // simulator

    static void finishSeason(ChampionshipHistory &history, // simulator
                             Championship &championship);

    static void viewMatches(const Championship &championship); // simulator

    static void enterMatchResult(const Match &match); // simulator

    static std::vector<Team *> listTeams(Championship &championship); // simulator

    static void addTeam(const std::vector<std::string> &args, // simulator
                        Championship &championship);

    static void removeTeam(const std::string &teamName, // simulator
                           Championship &championship);

    static void autoSelectLineups(Match &match, Team *host, Team *guest); // simulator

    static void deleteLineup(Match &match, // simulator
                             const Lineup &lineup);

    static std::vector<Player> listTopScorers(const Team &team); // simulator

    static void simulateGoal(const Match &match); // simulator

    static void addManager(Team* team, TeamManager& teamManager);
};

#endif // FOOTBALLGAMEENGINE_H
