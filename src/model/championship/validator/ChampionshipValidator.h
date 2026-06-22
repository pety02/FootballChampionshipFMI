//
// Created by User on 5/16/2026.
//

#ifndef CHAMPIONSHIPVALIDATOR_H
#define CHAMPIONSHIPVALIDATOR_H

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
};

#endif //CHAMPIONSHIPVALIDATOR_H