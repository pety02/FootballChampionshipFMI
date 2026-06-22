//
// Created by User on 5/30/2026.
//

#ifndef FOOTBALLGAMESIMULATORVALIDATOR_H
#define FOOTBALLGAMESIMULATORVALIDATOR_H

#include "../../model/championship/Championship.h"
#include "../../model/match/Match.h"
#include "../../model/match/lineup/Lineup.h"

/**
 * Utility validator class for football game simulation rules.
 *
 * Ensures that match-related operations are valid within the context
 * of a championship, such as verifying match existence and lineup validity.
 */
class FootballGameSimulatorValidator {
public:
    /**
     * Validates that a given match exists in the current championship.
     *
     * @param currentChampionship Pointer to the active championship.
     * @param match Match to validate.
     *
     * @throws std::invalid_argument If the championship is null or the match
     *         does not exist in the championship.
     */
    static void validateMatchExists(const Championship& currentChampionship,
                                    const Match& match);

    /**
     * Validates that a given lineup exists for a match in the championship.
     *
     * @param currentChampionship Pointer to the active championship.
     * @param lineup Lineup to validate.
     * @param match Match associated with the lineup.
     *
     * @throws std::invalid_argument If the lineup is not found or invalid
     *         for the given match.
     */
    static void validateLineupExists(Championship* currentChampionship,
                                     const Lineup& lineup,
                                     const Match* match);
};

#endif // FOOTBALLGAMESIMULATORVALIDATOR_H