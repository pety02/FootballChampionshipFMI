//
// Created by User on 5/14/2026.
//

#include "../championship/Championship.h"

#include <stdexcept>

#include "history/ChampionshipHistory.h"
#include "validator/ChampionshipValidator.h"
#include "../match/validator/MatchValidator.h"
#include "../../utils/ExceptionMessages.h"

Championship::Championship(const TeamManager& teamManager, const std::vector<Match> &matches)
    : teamManager(teamManager), matches(matches), currentRoundNumber(0), year(ChampionshipHistory::CURRENT_YEAR), finished(false) {
    unsigned teamsCount = teamManager.getTeams().size();
    if(matches.size() < teamsCount * (teamsCount - 1)) throw std::invalid_argument(toString(ExceptionMessages::NOT_ENOUGH_MATCHES));

    MatchValidator::validateLineups(matches);
}

void Championship::increaseRoundNumber() {
    ChampionshipValidator::validateCurrentRoundNumber(this->currentRoundNumber + 1);

    ++this->currentRoundNumber;
}

TeamManager & Championship::getTeamManager() {
    return this->teamManager;
}

const TeamManager & Championship::getTeamManager() const {
    return this->teamManager;
}

const std::vector<Match> & Championship::getMatches() const {
    return this->matches;
}

std::vector<Match> & Championship::getMatches() {
    return this->matches;
}

unsigned Championship::getCurrentRoundNumber() const {
    return this->currentRoundNumber;
}

AccountingManager &Championship::getAccountingManager() {
    return this->accountingManager;
}

const AccountingManager &Championship::getAccountingManager() const {
    return this->accountingManager;
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