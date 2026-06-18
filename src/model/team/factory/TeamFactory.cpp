//
// Created by User on 5/16/2026.
//

#include "TeamFactory.h"
#include <stdexcept>
#include "../../team/AttackingTeam.h"
#include "../../team/BalancedTeam.h"
#include "../../team/DefensiveTeam.h"

Team* TeamFactory::createTeam(TeamType type, const std::string& name, const std::string& coachName, const std::string& stadiumName, const double budget) {
    switch(type) {
        case TeamType::ATTACKING: return new AttackingTeam(name, coachName, stadiumName, budget);
        case TeamType::DEFENSIVE: return new DefensiveTeam(name, coachName, stadiumName, budget);
        case TeamType::BALANCED:  return new BalancedTeam(name, coachName, stadiumName, budget);
        default:
            return nullptr;
    }
}

Team* TeamFactory::createEmptyTeam(TeamType type)
{
    switch (type)
    {
        case TeamType::ATTACKING:
            return new AttackingTeam();

        case TeamType::DEFENSIVE:
            return new DefensiveTeam();

        case TeamType::BALANCED:
            return new BalancedTeam();

        default:
            return nullptr;
    }
}