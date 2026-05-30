//
// Created by User on 5/16/2026.
//

#include "MatchValidator.h"
#include <stdexcept>

void MatchValidator::validateRoundNumber(const unsigned roundNumber) {
    if(MatchValidator::MAX_ROUND_NUMBER < roundNumber)
        throw std::invalid_argument("Match round number must be at most " + std::to_string(MatchValidator::MAX_ROUND_NUMBER) + ".");
}