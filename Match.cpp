//
// Created by User on 5/14/2026.
//

#include "Match.h"

#include "AttackingTeam.h"
#include "MatchValidator.h"

Match::Match(const Lineup &hostLineup, const Lineup &guestLineup)
    : host(hostLineup.getTeam()->clone()), guest(guestLineup.getTeam()->clone()), hostLineup(hostLineup), guestLineup(guestLineup),
    hostGoals(0), guestGoals(0), roundNumber(0), goals(std::vector<Goal>()) {
}

Match::Match(const Match &other): hostLineup(nullptr), guestLineup(nullptr) {
    this->host = other.host->clone();
    this->guest = other.guest->clone();
    this->hostLineup = other.hostLineup;
    this->guestLineup = other.guestLineup;
    this->hostGoals = other.hostGoals;
    this->guestGoals = other.guestGoals;
    this->roundNumber = other.roundNumber;
    this->goals = other.goals;
}

Match & Match::operator=(const Match &other) {
    if(this !=  &other) {
        delete this->host; this->host = nullptr;
        delete this->guest; this->guest = nullptr;

        this->host = other.host->clone();
        this->guest = other.guest->clone();
        this->hostLineup = other.hostLineup;
        this->guestLineup = other.guestLineup;
        this->hostGoals = other.hostGoals;
        this->guestGoals = other.guestGoals;
        this->roundNumber = other.roundNumber;
    }

    return *this;
}

Match::~Match() {
    delete this->host; this->host = nullptr;
    delete this->guest; this->guest = nullptr;
}

void Match::increaseRoundNumber() {
    MatchValidator::validateRoundNumber(this->roundNumber);

    this->roundNumber++;
}

Team* Match::getHost() const {
    return this->host;
}

Team* Match::getGuest() const {
    return this->guest;
}

const Lineup& Match::getHostLineup() const {
    return this->hostLineup;
}

const Lineup& Match::getGuestLineup() const {
    return this->guestLineup;
}

unsigned Match::getHostGoals() const {
    return this->hostGoals;
}

unsigned Match::getGuestGoals() const {
    return this->guestGoals;
}

unsigned Match::getRoundNumber() const {
    return this->roundNumber;
}

const std::vector<Player*> Match::getScorers() const {
    std::vector<Player*> scorers = std::vector<Player*>();
    for (int i = 0; i < this->goals.size(); ++i) {
        scorers.push_back(this->goals[i].scorer);
    }
    return scorers;
}