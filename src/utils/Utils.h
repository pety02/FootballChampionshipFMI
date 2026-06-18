//
// Created by User on 6/18/2026.
//

#ifndef UTILS_H
#define UTILS_H

#include "../model/team/TeamType.h"
#include <string>
#include <iostream>

class Utils {
public:
    static TeamType parseTeamType(const std::string& type)
    {
        std::cout << "parsing TeamType: " << type << std::endl;
        if (type == "attacking") return TeamType::ATTACKING;
        if (type == "defensive") return TeamType::DEFENSIVE;
        if (type == "balanced")  return TeamType::BALANCED;
        return TeamType::UNKNOWN;
    }

    static std::string toString(TeamType teamType) {
        switch (teamType) {
            case TeamType::ATTACKING: return "attacking";
            case TeamType::DEFENSIVE: return "defensive";
            case TeamType::BALANCED: return "balanced";
            default: return "unknown";
        }
    }
};

#endif //UTILS_H