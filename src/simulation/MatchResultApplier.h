#ifndef MATCHRESULTAPPLIER_H
#define MATCHRESULTAPPLIER_H

#include "../model/match/Match.h"

/**
 * Utility class responsible for applying match results
 * to teams and players.
 *
 * This class updates team statistics (wins, losses, goals)
 * and player statistics based on a completed match result.
 */
class MatchResultApplier {
public:
    /**
     * Applies a complete match result to all relevant entities.
     *
     * This includes:
     * - Updating team statistics (goals scored/conceded, win/draw/loss)
     * - Updating player statistics (goals scored, matches played)
     *
     * @param result The match result to apply.
     */
    static void apply(const Match::MatchResult& result);

private:
    /**
     * Applies statistical updates to a single team.
     *
     * @param team Pointer to the team to update.
     * @param scored Number of goals scored by the team.
     * @param conceded Number of goals conceded by the team.
     */
    static void applyTeam(Team* team,
                          unsigned scored,
                          unsigned conceded);

    /**
     * Applies player-level statistics based on match events.
     *
     * Updates goal counts and match participation for players
     * involved in the match result.
     *
     * @param result The match result containing scorer information.
     */
    static void applyPlayers(const Match::MatchResult& result);
};

#endif // MATCHRESULTAPPLIER_H