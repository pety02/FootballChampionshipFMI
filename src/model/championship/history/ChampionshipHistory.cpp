//
// Created by User on 5/14/2026.
//

#include "../championship/history/ChampionshipHistory.h"

#include "../validator/ChampionshipValidator.h"

ChampionshipHistory::ChampionshipHistory() : championships(Map<unsigned, Championship>()) {
}

void ChampionshipHistory::addChampionship(unsigned year, const Championship &championship) {
    ChampionshipValidator::validateYear(year);

    this->championships[year] = championship;
}

const Map<unsigned, Championship>& ChampionshipHistory::getChampionships() const {
    return this->championships;
}

Championship& ChampionshipHistory::operator[](unsigned year) {
    return championships[year];
}

void ChampionshipHistory::setCurrentYear(unsigned year) {
    ChampionshipValidator::validateYear(year);

    ChampionshipHistory::CURRENT_YEAR = year;
}