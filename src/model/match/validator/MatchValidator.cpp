//
// Created by User on 5/16/2026.
//

#include "../../match/validator/MatchValidator.h"
#include <stdexcept>

#include "../../../utils/ExceptionMessages.h"

void MatchValidator::validateRoundNumber(const unsigned roundNumber) {
    if(MatchValidator::MAX_ROUND_NUMBER < roundNumber)
        throw std::invalid_argument(toString(ExceptionMessages::MATCH_ROUND_NUMBER_MUST_BE_AT_MOST));
}

void MatchValidator::validateLineups(const std::vector<Match>& matches) {
    bool hasValidLineups = true;

    for (const auto & match : matches) {
        if(MatchValidator::MAX_LINEUP_SIZE < match.getHostLineup().getPlayers().size()
            || MatchValidator::MAX_LINEUP_SIZE < match.getGuestLineup().getPlayers().size()) {
            hasValidLineups = false;
            break;
            }
    }
    if(!hasValidLineups) throw std::invalid_argument(toString(ExceptionMessages::NO_VALID_LINEUPS));
}

void MatchValidator::validateMatchesCount(unsigned currentSize, unsigned targetSize) {
    if(targetSize <= currentSize)
        throw std::invalid_argument(toString(ExceptionMessages::ENOUGH_MATCHES));
}