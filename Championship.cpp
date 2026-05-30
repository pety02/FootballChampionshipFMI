//
// Created by User on 5/14/2026.
//

#include "Championship.h"

#include <stdexcept>

#include "ChampionshipHistory.h"
#include "ChampionshipValidator.h"

Championship::Championship(const TeamManager& teamManager, const std::vector<Match> &matches)
    : teamManager(teamManager), currentRoundNumber(0), year(ChampionshipHistory::CURRENT_YEAR), matches(matches), finished(false) {
    unsigned teamsCount = teamManager.getTeams().size();
    if(matches.size() < teamsCount * (teamsCount - 1)) throw std::invalid_argument("Not enough matches.");
    bool hasValidLineups = true;
    for (const auto & match : matches) {
        if(match.getHostLineup().getPlayers().size() < 11
            || match.getGuestLineup().getPlayers().size() > 11) {
            hasValidLineups = false;
            break;
        }
    }
    if(!hasValidLineups) throw std::invalid_argument("No valid lineups.");
}

void Championship::increaseRoundNumber() {
    ChampionshipValidator::validateCurrentRoundNumber(this->currentRoundNumber);

    this->currentRoundNumber++;
}

const TeamManager & Championship::getTeamManager() const {
    return this->teamManager;
}

const std::vector<Match> & Championship::getMatches() const {
    return this->matches;
}

unsigned Championship::getCurrentRoundNumber() const {
    return this->currentRoundNumber;
}

bool Championship::isFinished() const {
    return this->finished;
}

unsigned Championship::getYear() const {
    return this->year;
}
