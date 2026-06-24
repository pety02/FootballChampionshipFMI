#include "ChampionshipValidator.h"

#include <stdexcept>

#include "../../../utils/ExceptionMessages.h"

void ChampionshipValidator::validateCurrentRoundNumber(const unsigned roundNumber) {
    if(ChampionshipValidator::MAX_ROUND_NUMBER < roundNumber)
        throw std::invalid_argument(toString(ExceptionMessages::CHAMPIONSHIP_ROUND_NUMBER_MUST_BE_AT_MOST));
}