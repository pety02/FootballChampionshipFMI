//
// Created by User on 5/16/2026.
//

#ifndef CHAMPIONSHIPVALIDATOR_H
#define CHAMPIONSHIPVALIDATOR_H

enum class ExceptionMessage;

/**
*
*/
class ChampionshipValidator final {
public:
    static constexpr unsigned MAX_ROUND_NUMBER = 36;

    ChampionshipValidator() = default;

    /**
    *
    */
    static void validateCurrentRoundNumber(unsigned roundNumber);

    /**
    *
    */
    static void validateYear(unsigned year);
};

#endif //CHAMPIONSHIPVALIDATOR_H