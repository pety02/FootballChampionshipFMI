//
// Created by User on 5/31/2026.
//

#include "MatchResultApplier.h"

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
    auto& stats = team->getStats();

    stats.increaseScoredGoals(scored);
    stats.increaseConcededGoals(conceded);

    if (scored > conceded)
        stats.increaseWinsCount(1);
    else if (scored < conceded)
        stats.increaseLossesCount(1);
    else
        stats.increaseDrawsCount(1);
}

void MatchResultApplier::applyPlayers(const Match::MatchResult& result)
{
    for (Player* p : result.home->getPlayers())
        p->getStats().increaseMatchesCount();

    for (Player* p : result.guest->getPlayers())
        p->getStats().increaseMatchesCount();

    for (const auto& g : result.goals)
        g.player->getStats().increaseScoredGoals();
}