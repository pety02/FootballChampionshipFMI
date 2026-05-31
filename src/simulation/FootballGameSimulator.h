//
// Created by User on 5/17/2026.
//

#ifndef FOOTBALLGAMESIMULATOR_H
#define FOOTBALLGAMESIMULATOR_H

#include <string>
#include "../../model/championship/history/ChampionshipHistory.h"

/**
 *
 */
class FootballGameSimulator {
private:
    ChampionshipHistory championshipHistory;
    Championship* currentChampionship;
    std::string champion;
    std::string viceChampion;
    std::string bronzeTeam;
    std::string goalMaster;

    std::string findGoalMaster();

    [[nodiscard]] std::vector<std::string> getChampions() const;
public:
    FootballGameSimulator();

    /**
     *
     */
    void simulate(); // creates/initializes the current championship

    /**
     *
     * @param match
     */
    void addMatch(const Match& match); // adds a match in the current championship

    /**
     *
     */
    void updateChampionshipRound();

    /**
     *
     */
    void finishChampionship();

    /**
     *
     * @param match
     */
    void play(Match* match);

    /**
     *
     * @param player
     * @param match
     */
    void addScorer(Player* player, Match& match);

    /**
     *
     * @param match
     */
    void increaseHostGoals(const Match& match);

    /**
     *
     * @param match
     */
    void increaseGuestGoals(const Match& match);

    /**
     *
     * @param match
     */
    void finishMatch(Match& match);

 // записване в и зареждане от файл на данни за първенствата
};

#endif //FOOTBALLGAMESIMULATOR_H