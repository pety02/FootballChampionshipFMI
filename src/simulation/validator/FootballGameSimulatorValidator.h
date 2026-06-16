//
// Created by User on 5/30/2026.
//

#ifndef FOOTBALLGAMESIMULATORVALIDATOR_H
#define FOOTBALLGAMESIMULATORVALIDATOR_H
#include "../../model/championship/Championship.h"
#include "../../model/match/Match.h"
#include "../../model/match/lineup/Lineup.h""

class FootballGameSimulatorValidator {
public:
    /**
     *
     * @param currentChampionship
     * @param match
     * @return
     */
    static void validateMatchExists(Championship* currentChampionship, const Match& match);

    /**
     *
     * @param currentChampionship
     * @param lineup
     * @param match
     * @return
     */
    static void validateLineupExists(Championship* currentChampionship, const Lineup& lineup, const Match* match);
};

#endif //FOOTBALLGAMESIMULATORVALIDATOR_H