#ifndef MATCHRESULTAPPLIER_H
#define MATCHRESULTAPPLIER_H

#include "../../../model/match/Match.h"

class MatchResultApplier {
public:
    static void apply(const Match::MatchResult& result);

private:
    static void applyTeam(Team* team,
                          unsigned scored,
                          unsigned conceded);

    static void applyPlayers(const Match::MatchResult& result);
};

#endif //MATCHRESULTAPPLIER_H