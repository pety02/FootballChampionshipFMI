//
// Created by User on 5/16/2026.
//

#ifndef MATCHVALIDATOR_H
#define MATCHVALIDATOR_H

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
};

#endif //MATCHVALIDATOR_H