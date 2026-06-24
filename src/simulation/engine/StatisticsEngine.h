#ifndef STATISTICSENGINE_H
#define STATISTICSENGINE_H

#include "../../model/championship/Championship.h"
#include "../../model/team/Team.h"

class StatisticsEngine {
public:
    /**
    * Returns the statistical summary of a single team.
    *
    * @param team The team whose statistics are requested.
    * @return A copy of the team's statistics.
    */
    static Team::Statistics listTeamStats(Team &team);

    /**
    * Collects statistics for all teams participating in a championship.
    *
    * @param championship The championship to analyze.
    * @return A vector containing statistics for each team.
    */
    static std::vector<Team::Statistics> listSeasonStats(Championship &championship);

    /**
    * Collects statistics for all players in a team.
    *
    * @param team The team whose players' statistics are requested.
    * @return A vector of player statistics.
    */
    static std::vector<Player::Statistics> listPlayerStats(const Team &team);

    /**
    * Prints a ranking of all players in a championship based on scored goals.
    *
    * @param championship The championship whose player rankings are displayed.
    */
    static void viewPlayerRanking(Championship &championship);

    /**
    * Builds a ranking of teams based on scored goals in the championship.
    *
    * This function extracts all teams from the championship, pairs each team
    * with its total number of scored goals, and then sorts the resulting list
    * in descending order using a custom selection sort implementation.
    *
    * Sorting is delegated to Utils::selectionSortTeamsByGoals.
    *
    * @param championship The championship whose teams are being ranked.
    * @return A vector of (Team pointer, scored goals) pairs sorted
    *         in descending order by goals scored.
    */
    static std::vector<std::pair<Team *, unsigned> > buildTeamRanking(const Championship &championship);

    /**
    * Determines the champion team of a championship based on scored goals.
    *
    * Teams are ranked in descending order by total scored goals.
    *
    * @param championship The championship to evaluate.
    * @return Reference to the winning team.
    */
    static const Team &getChampion(const Championship &championship);

    /**
    * Determines the runner-up team of a championship.
    *
    * @param championship The championship to evaluate.
    * @return Reference to the second-place team.
    */
    static const Team &getRunnerUp(const Championship &championship);

    /**
    * Determines the third-place team of a championship.
    *
    * @param championship The championship to evaluate.
    * @return Reference to the third-place team.
    */
    static const Team &getThirdPlace(const Championship &championship);
};

#endif //STATISTICSENGINE_H
