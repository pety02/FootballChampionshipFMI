//
// Created by User on 5/17/2026.
//

#ifndef FOOTBALLGAMESIMULATOR_H
#define FOOTBALLGAMESIMULATOR_H

#include <string>

#include "../model/championship/history/ChampionshipHistory.h"
#include "../model/match/Match.h"
#include "../model/player/Player.h"

/**
 * Core simulation engine for running football championships.
 *
 * This class is responsible for:
 * - Creating and managing a championship lifecycle
 * - Simulating matches
 * - Tracking results and statistics
 * - Determining final rankings (champion, vice-champion, etc.)
 */
class FootballGameSimulator {
private:
    ChampionshipHistory championshipHistory = ChampionshipHistory();

    /**
     * Currently active championship being simulated.
     *
     * Ownership: FootballGameSimulator owns this pointer.
     */
    Championship* currentChampionship = nullptr;

    std::string champion = std::string();
    std::string viceChampion = std::string();
    std::string bronzeTeam = std::string();
    std::string goalMaster = std::string();

    /**
     * Determines the player with the highest number of goals
     * across the championship.
     *
     * @return Name of the top scorer.
     */
    std::string findGoalMaster();

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
    FootballGameSimulator();

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
    void addMatch(const Match& match);

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
    void play(Match* match);

    /**
     * Records a goal scored by a player in a match.
     *
     * @param player Pointer to the scoring player.
     * @param match Reference to the match where the goal occurred.
     */
    void addScorer(Player* player, Match& match);

    /**
     * Increments the home team's goal count in a match.
     *
     * @param match The match to update.
     */
    void increaseHostGoals(const Match& match);

    /**
     * Increments the guest team's goal count in a match.
     *
     * @param match The match to update.
     */
    void increaseGuestGoals(const Match& match);

    /**
     * Marks a match as finished and finalizes its result.
     *
     * @param match Match to finalize.
     */
    void finishMatch(Match& match);

    /**
     * Gets the currently active championship.
     *
     * @return Constant reference to the championship.
     */
    [[nodiscard]] const Championship& getCurrentChampionship() const;
};

#endif // FOOTBALLGAMESIMULATOR_H