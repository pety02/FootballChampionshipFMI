//
// Created by User on 5/16/2026.
//

#include "TeamFactory.h"

#include <stdexcept>
#include "AttackingTeam.h"
#include "BalancedTeam.h"
#include "DefensiveTeam.h"

Team* TeamFactory::createTeam(TeamType type, const std::string& name, const std::string& coachName, const std::string& stadiumName, const double budget) {
    switch(type) {
        case TeamType::ATTACKING: return new AttackingTeam(name, coachName, stadiumName, budget);
        case TeamType::DEFENSIVE: return new DefensiveTeam(name, coachName, stadiumName, budget);
        case TeamType::BALANCED: return new BalancedTeam(name, coachName, stadiumName, budget);
        default:
            throw std::invalid_argument("The team type should be ATTACKING, DEFENSIVE or BALANCED.");
    }
}