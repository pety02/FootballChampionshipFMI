//
// Created by User on 5/16/2026.
//

#ifndef MATCHVALIDATOR_H
#define MATCHVALIDATOR_H

#include <vector>
#include "../../match/Match.h"

/**
* A validator class of a football match.
*/
class MatchValidator final {
public:
    static constexpr unsigned MAX_ROUND_NUMBER = 2;
    static constexpr unsigned MAX_LINEUP_SIZE = 11;

    /**
    * Default constructor of the match validator class.
    */
    MatchValidator() = default;

    /**
    * Validates that the round number is at most the max match round number.
    */
    static void validateRoundNumber(unsigned roundNumber);

    /**
    * Validates that the lineups players' count is at most the max lineup size.
    */
    static void validateLineups(const std::vector<Match>& matches);

    /**
    * Validates that the matches count is at most the target count.
    */
    static void validateHasEnoughMatches(unsigned currentSize, unsigned targetSize);
};

#endif //MATCHVALIDATOR_H