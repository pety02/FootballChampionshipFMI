//
// Created by User on 5/31/2026.
//

#include "../simulation/MatchResultApplier.h"

void MatchResultApplier::apply(const Match::MatchResult& result)
{
    applyTeam(result.home, result.homeGoals, result.guestGoals);
    applyTeam(result.guest, result.guestGoals, result.homeGoals);

    applyPlayers(result);
}

void MatchResultApplier::applyTeam(Team* team,
                      unsigned scored,
                      unsigned conceded)
{
    Team::Statistics& stats = team->getStats();

    stats.increaseScoredGoals(scored);
    stats.increaseConcededGoals(conceded);

    if (scored > conceded)
        stats.increaseWinsCount(1);
    else if (scored < conceded)
        stats.increaseLossesCount(1);
    else
        stats.increaseDrawsCount(1);
}

void MatchResultApplier::applyPlayers(const Match::MatchResult& result) {
    bool isHome = false;
    for (Player p : result.home->getPlayers()) {
        p.getStats().increaseMatchesCount();
        isHome = true;
    }

    for (Player p : result.guest->getPlayers()) {
        p.getStats().increaseMatchesCount();
        isHome = false;
    }

    for (Match::MatchResult::Scorer* g : result.goals) {
        g->player.getStats().increaseScoredGoals();
        g->isHome = isHome;
    }
}