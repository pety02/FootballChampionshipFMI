//
// Created by User on 5/16/2026.
//

#ifndef MATCHVALIDATOR_H
#define MATCHVALIDATOR_H

#include <vector>
#include "../../match/Match.h"
#include "../../utils/ExceptionMessages.h"

/**
*
*/
class MatchValidator final {
public:
    static constexpr unsigned MAX_ROUND_NUMBER = 2;
    MatchValidator() = default;

    /**
    *
    */
    static void validateRoundNumber(unsigned roundNumber);

    static void validateLineups(const std::vector<Match>& matches);

    static void validateMatchesCount(unsigned currentSize, unsigned targetSize);
};

#endif //MATCHVALIDATOR_H