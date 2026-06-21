//
// Created by User on 6/19/2026.
//

#ifndef STATISTICSENGINE_H
#define STATISTICSENGINE_H
#include "../../model/championship/Championship.h"
#include "../../model/team/Team.h"

class StatisticsEngine {
public:
    static Team::Statistics listTeamStats(Team& team);

    static std::vector<Team::Statistics>
    listSeasonStats(Championship &championship);

    static std::vector<Player::Statistics>
    listPlayerStats(const Team& team);

    static Player getTopScorer(const Championship& championship);

    static void viewPlayerRanking(Championship& championship);

    static const Team& getChampion(const Championship& championship);

    static const Team& getRunnerUp(const Championship& championship);

    static const Team& getThirdPlace(const Championship& championship);
};

#endif //STATISTICSENGINE_H