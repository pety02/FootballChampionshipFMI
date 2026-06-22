//
// Created by User on 5/14/2026.
//

#include "../championship/history/ChampionshipHistory.h"

#include <stdexcept>

#include "../validator/ChampionshipValidator.h"

ChampionshipHistory::ChampionshipHistory() : championships(std::vector<Championship>()) {
}

void ChampionshipHistory::addChampionship(const Championship &championship) {
    this->championships.push_back(championship);
}

const std::vector<Championship>& ChampionshipHistory::getChampionships() const {
    return this->championships;
}