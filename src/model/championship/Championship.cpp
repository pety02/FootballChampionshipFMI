//
// Created by User on 5/14/2026.
//

#include "Championship.h"

#include <stdexcept>

#include "../../championship/history/ChampionshipHistory.h"
#include "../../championship/validator/ChampionshipValidator.h"
#include "../../match/validator/MatchValidator.h"
#include "../../utils/ExceptionMessages.h"

Championship::Championship(const TeamManager& teamManager, const std::vector<Match> &matches)
    : teamManager(teamManager), currentRoundNumber(0), year(ChampionshipHistory::CURRENT_YEAR), matches(matches), finished(false) {
    unsigned teamsCount = teamManager.getTeams().size();
    if(matches.size() < teamsCount * (teamsCount - 1)) throw std::invalid_argument(toString(ExceptionMessages::NOT_ENOUGH_MATCHES));

    MatchValidator::validateLineups(matches);
}

void Championship::increaseRoundNumber() {
    ChampionshipValidator::validateCurrentRoundNumber(this->currentRoundNumber + 1);

    ++this->currentRoundNumber;
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

void Championship::addMatch(const Match &match) {
    if(this->matches.empty()) {
        this->matches.push_back(match);
        return;
    }

    unsigned teamsCount = this->teamManager.getTeams().size();
    MatchValidator::validateMatchesCount(this->matches.size(), teamsCount * (teamsCount - 1));
    this->matches.push_back(match);
}

void Championship::finish() {
    this->finished = true;
}