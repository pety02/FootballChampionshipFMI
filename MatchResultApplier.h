#ifndef MATCHRESULTAPPLIER_H
#define MATCHRESULTAPPLIER_H

class MatchResultApplier {
public:
    static void apply(const MatchResult& result)
    {
        applyTeam(result.home, result.homeGoals, result.guestGoals);
        applyTeam(result.guest, result.guestGoals, result.homeGoals);

        applyPlayers(result);
    }

private:
    static void applyTeam(Team* team,
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

    static void applyPlayers(const MatchResult& result)
    {
        for (Player* p : result.home->getLineup().getPlayers())
            p->getStats().increaseMatchesCount();

        for (Player* p : result.guest->getLineup().getPlayers())
            p->getStats().increaseMatchesCount();

        for (const auto& g : result.goals)
            g.player->getStats().increaseScoredGoals();
    }
};

#endif //MATCHRESULTAPPLIER_H