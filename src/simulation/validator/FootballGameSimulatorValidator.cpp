//
// Created by User on 5/30/2026.
//

#include "FootballGameSimulatorValidator.h"
#include <stdexcept>

#include "../../utils/ExceptionMessages.h"

void FootballGameSimulatorValidator::validateMatchExists(Championship* currentChampionship, const Match& match) {
    bool matchExists = false;
    for(const Match& currentChampionshipMatch : currentChampionship->getMatches()) {
        if(match.getHost()->getName() == currentChampionshipMatch.getHost()->getName()
            && match.getGuest()->getName() == currentChampionshipMatch.getGuest()->getName()) {
            matchExists = true;
            break;
            }
    }

    if(!matchExists) throw std::invalid_argument(toString(ExceptionMessages::MATCH_DOES_NOT_EXIST_IN_THE_CURRENT_CHAMPIONSHIP));
}

void FootballGameSimulatorValidator::validateLineupExists(Championship* currentChampionship, const Lineup& lineup, const Match* match) {
    bool lineupExists = false;

    const std::vector<Match>& currentMatches = currentChampionship->getMatches();

    for (const Match& currentMatch : currentMatches) {

        if (match->getHost()->getName() == currentMatch.getHost()->getName()
                && match->getGuest()->getName() ==  currentMatch.getGuest()->getName()) {

            const Lineup& host = currentMatch.getHostLineup();
            const Lineup& guest = currentMatch.getGuestLineup();

            if (
                lineup.getTeam()->getName() == host.getTeam()->getName() ||
                lineup.getTeam()->getName() == guest.getTeam()->getName()
            ) {
                lineupExists = true;
                break;
            }
                }
    }

    if (!lineupExists) {
        throw std::invalid_argument(
            toString(ExceptionMessages::LINEUP_DOES_NOT_EXIST_IN_THE_CURRENT_CHAMPIONSHIP)
        );
    }
}