#include "../championship/history/ChampionshipHistory.h"

ChampionshipHistory::ChampionshipHistory() : championships(std::vector<Championship>()) {
}

void ChampionshipHistory::addChampionship(const Championship &championship) {
    this->championships.push_back(championship);
}

const std::vector<Championship>& ChampionshipHistory::getChampionships() const {
    return this->championships;
}