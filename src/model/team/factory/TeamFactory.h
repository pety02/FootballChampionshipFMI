//
// Created by User on 5/16/2026.
//

#ifndef TEAMFACTORY_H
#define TEAMFACTORY_H
#include "../../team/Team.h"
#include <string>

/**
*
*/
enum class TeamType {
    ATTACKING, DEFENSIVE, BALANCED
};

/**
*
*/
class TeamFactory {
public:
    /**
    *
    */
    static Team* createTeam(TeamType type, const std::string& name, const std::string& coachName, const std::string& stadiumName, double budget);
};

#endif //TEAMFACTORY_H