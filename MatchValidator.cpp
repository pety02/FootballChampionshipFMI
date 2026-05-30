//
// Created by User on 5/16/2026.
//

#include "MatchValidator.h"
#include <stdexcept>

void MatchValidator::validateRoundNumber(const unsigned roundNumber) {
    if(MatchValidator::MAX_ROUND_NUMBER < roundNumber)
        throw std::invalid_argument("Match round number must be at most " + std::to_string(MatchValidator::MAX_ROUND_NUMBER) + ".");
}

void MatchValidator::validateLineups(const std::vector<Match>& matches) {
    bool hasValidLineups = true;

    for (const auto & match : matches) {
        if(match.getHostLineup().getPlayers().size() < 11
            || match.getGuestLineup().getPlayers().size() > 11) {
            hasValidLineups = false;
            break;
            }
    }
    if(!hasValidLineups) throw std::invalid_argument("No valid lineups.");
}

void MatchValidator::validateMatchesCount(unsigned currentSize, unsigned targetSize) {
    if(currentSize >= targetSize)
        throw std::invalid_argument("Has enough matches. You cannot add the current match in the current championship.");
}