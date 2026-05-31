//
// Created by User on 5/16/2026.
//

#ifndef CHAMPIONSHIPVALIDATOR_H
#define CHAMPIONSHIPVALIDATOR_H

enum class ExceptionMessage;

/**
* A class that validates the championship fields.
*/
class ChampionshipValidator final {
public:
    static constexpr unsigned MAX_ROUND_NUMBER = 36;

    /**
    * The default constructor of ChampionshipValidator class.
    */
    ChampionshipValidator() = default;

    /**
    * Validates the passed round number to be less than the max allowed championship round number.
    * @param roundNumber - the passed round number that should be validated before to be set.
    */
    static void validateCurrentRoundNumber(unsigned roundNumber);

    /**
    * Validates the passed year to be at least 1900 and at most the current year.
    * @param year - the passed year that should be validated before to be set.
    */
    static void validateYear(unsigned year);
};

#endif //CHAMPIONSHIPVALIDATOR_H