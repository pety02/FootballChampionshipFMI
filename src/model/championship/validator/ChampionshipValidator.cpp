//
// Created by User on 5/16/2026.
//

#include "ChampionshipValidator.h"

#include <ChampionshipHistory.h>
#include <stdexcept>

#include "../../../utils/ExceptionMessages.h"

void ChampionshipValidator::validateCurrentRoundNumber(const unsigned roundNumber) {
    if(ChampionshipValidator::MAX_ROUND_NUMBER < roundNumber)
        throw std::invalid_argument(toString(ExceptionMessages::CHAMPIONSHIP_ROUND_NUMBER_MUST_BE_AT_MOST));
}

void ChampionshipValidator::validateYear(const unsigned year) {
    if(year < 1900)
        throw std::invalid_argument(toString(ExceptionMessages::YEAR_MUST_BE_AT_LEAST_1900));

    if(ChampionshipHistory::CURRENT_YEAR < year)
        throw std::invalid_argument(toString(ExceptionMessages::YEAR_MUST_BE_AT_MOST_CURRENT_YEAR));
}