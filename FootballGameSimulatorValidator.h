//
// Created by User on 5/30/2026.
//

#ifndef FOOTBALLGAMESIMULATORVALIDATOR_H
#define FOOTBALLGAMESIMULATORVALIDATOR_H
#include "Championship.h"
#include "Match.h"

class FootballGameSimulatorValidator {
public:
    /**
     *
     * @param match
     * @return
     */
    static void validateMatchExists(Championship* currentChampionship, Match& match);

    /**
     *
     * @param lineup
     * @param match
     * @return
     */
    static void validateLineupExists(Championship* currentChampionship, const Lineup& lineup, Match* match);
};

#endif //FOOTBALLGAMESIMULATORVALIDATOR_H