//
// Created by User on 5/14/2026.
//

#include "ChampionshipHistory.h"

#include "ChampionshipValidator.h"

ChampionshipHistory::ChampionshipHistory() : championships(Map<unsigned, Championship>()) {
}

void ChampionshipHistory::addChampionship(unsigned year, const Championship &championship) {
    ChampionshipValidator::validateYear(year, ChampionshipHistory::CURRENT_YEAR);

    this->championships[year] = championship;
}

const Map<unsigned, Championship>& ChampionshipHistory::getChampionships() const {
    return this->championships;
}

Championship& ChampionshipHistory::operator[](unsigned year) {
    return championships[year];
}

void ChampionshipHistory::setCurrentYear(unsigned year) {
    ChampionshipHistory::CURRENT_YEAR = year;
}