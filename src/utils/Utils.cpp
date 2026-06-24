#include "Utils.h"
#include <iostream>

TeamType Utils::parseTeamType(const std::string& type)
{
    std::cout << "parsing TeamType: " << type << std::endl;
    if (type == "attacking") return TeamType::ATTACKING;
    if (type == "defensive") return TeamType::DEFENSIVE;
    if (type == "balanced")  return TeamType::BALANCED;
    return TeamType::UNKNOWN;
}

std::string Utils::toString(TeamType teamType) {
    switch (teamType) {
        case TeamType::ATTACKING: return "attacking";
        case TeamType::DEFENSIVE: return "defensive";
        case TeamType::BALANCED: return "balanced";
        default: return "unknown";
    }
}

const std::string& Utils::toLowerCase(std::string& str) {
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c >= 'A' && c <= 'Z') {
            c += 32;
        }
    }

    return str;
}

Player::Position Utils::toPosition(std::string& posValue) {
    posValue = toLowerCase(posValue);

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

void Utils::selectionSortByGoals(
    std::vector<Pair<std::string, unsigned>>& teams)
{
    for (size_t i = 0; i < teams.size(); ++i)
    {
        size_t maxIndex = i;

        for (size_t j = i + 1; j < teams.size(); ++j)
        {
            if (teams[j].right > teams[maxIndex].right)
            {
                maxIndex = j;
            }
        }

        if (maxIndex != i)
        {
            Pair<std::string, unsigned> temp = teams[i];
            teams[i] = teams[maxIndex];
            teams[maxIndex] = temp;
        }
    }
}

void Utils::selectionSortTeamsByGoals(
    std::vector<std::pair<Team*, unsigned>>& ranking)
{
    for (size_t i = 0; i < ranking.size(); ++i)
    {
        size_t maxIndex = i;

        for (size_t j = i + 1; j < ranking.size(); ++j)
        {
            if (ranking[j].second > ranking[maxIndex].second)
            {
                maxIndex = j;
            }
        }

        if (maxIndex != i)
        {
            std::pair<Team*, unsigned> temp = ranking[i];
            ranking[i] = ranking[maxIndex];
            ranking[maxIndex] = temp;
        }
    }
}

unsigned Utils::clampUnsigned(unsigned value, unsigned minVal, unsigned maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}