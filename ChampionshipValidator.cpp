//
// Created by User on 5/16/2026.
//

#include "ChampionshipValidator.h"
#include <stdexcept>

void ChampionshipValidator::validateCurrentRoundNumber(const unsigned roundNumber) {
    if(ChampionshipValidator::MAX_ROUND_NUMBER < roundNumber)
        throw std::invalid_argument("Round number must be at most " + std::to_string(ChampionshipValidator::MAX_ROUND_NUMBER) + ".");
}

void ChampionshipValidator::validateYear(const unsigned year, const unsigned currentYear) {
    if(year < 1900)
        throw std::invalid_argument("Year must be at least 1900.");

    if(currentYear < year)
        throw std::invalid_argument("Year must be at most " + std::to_string(currentYear) + ".");
}