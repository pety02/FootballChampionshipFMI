//
// Created by User on 6/18/2026.
//

#ifndef UTILS_H
#define UTILS_H

#include "../model/team/TeamType.h"
#include "../model/player/Player.h"
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

    static Player::Position toPosition(const std::string& posValue) {
        // to lowercase
        for (int i = 0; i < posValue.length(); i++) {
            char c = posValue[i];
            if (c >= 'A' && c <= 'Z') {
                c += 32;
            }
        }

        if(posValue == "goalkeeper") {
            return Player::Position::GOALKEEPER;
        } else if (posValue == "defender") {
            return Player::Position::DEFENDER;
        } else if (posValue == "midfielder") {
            return Player::Position::MIDFIELDER;
        } else if (posValue == "winger") {
            return Player::Position::WINGER;
        } else if (posValue == "forward") {
            return Player::Position::FORWARD;
        } else {
            return Player::Position::UNKNOWN;
        }
    }
};

#endif //UTILS_H