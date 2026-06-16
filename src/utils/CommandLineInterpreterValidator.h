//
// Created by User on 6/15/2026.
//

#ifndef COMMANDLINEINTERPRETERVALIDATOR_H
#define COMMANDLINEINTERPRETERVALIDATOR_H

#include "../model/match/Match.h"

class CommandLineInterpreterValidator {
public:
    static void validGoalsCount(unsigned scoredGals, int totalScoredGoals);
    static bool validateIsHomePlayer(const std::string& playerName, const Team& team);
    static bool validateIsGuestPlayer(const std::string& playerName, const Team& team);
    static void validateUniquePlayerName(const std::string& playerName, const Team& team);
};

#endif //COMMANDLINEINTERPRETERVALIDATOR_H