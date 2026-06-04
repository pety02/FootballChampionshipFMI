//
// Created by User on 5/14/2026.
//

#include "Match.h"

#include "../team/AttackingTeam.h"
#include "MatchValidator.h"
#include <cstdlib>
#include <ctime>

Match::Match(const Lineup &hostLineup, const Lineup &guestLineup)
    : host(hostLineup.getTeam()->clone()), guest(guestLineup.getTeam()->clone()), hostLineup(hostLineup), guestLineup(guestLineup),
    hostGoals(0), guestGoals(0), roundNumber(0), matchResult(MatchResult()), finished(false) {
}

Match::Match(const Match &other): hostLineup(nullptr), guestLineup(nullptr), finished(other.finished) {
    this->host = other.host->clone();
    this->guest = other.guest->clone();
    this->hostLineup = other.hostLineup;
    this->guestLineup = other.guestLineup;
    this->hostGoals = other.hostGoals;
    this->guestGoals = other.guestGoals;
    this->roundNumber = other.roundNumber;
    this->matchResult = other.matchResult;
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
        this->finished = other.finished;
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
    for (int i = 0; i < this->matchResult.goals.size(); ++i) {
        scorers.push_back(this->matchResult.goals[i].player);
    }
    return scorers;
}

void Match::addGoal(Player *scorer, bool isHostPlayer) {
    this->matchResult.goals.push_back(MatchResult::Scorer(scorer, isHostPlayer));
}

bool Match::isFinished() const {
    return this->finished;
}

unsigned Match::calculateAttackStrength(const Lineup& lineup) {
    unsigned strength = 0;

    const std::vector<Player*>& players = lineup.getPlayers();

    for (Player* p : players) {
        switch (p->getPosition()) {
            case Player::Position::FORWARD:
                strength += 4;
            break;

            case Player::Position::WINGER:
                strength += 3;
            break;

            case Player::Position::MIDFIELDER:
                strength += 2;
            break;

            case Player::Position::DEFENDER:
                strength += 1;
            break;

            default:
                break;
        }
    }

    return strength;
}

unsigned Match::calculateDefenseStrength(const Lineup& lineup) {
    unsigned strength = 0;

    const std::vector<Player*>& players = lineup.getPlayers();

    for (Player* p : players) {
        switch (p->getPosition()) {
            case Player::Position::GOALKEEPER:
                strength += 5;
            break;

            case Player::Position::DEFENDER:
                strength += 4;
            break;

            case Player::Position::MIDFIELDER:
                strength += 2;
            break;

            case Player::Position::WINGER:
                strength += 1;
            break;

            default:
                break;
        }
    }

    return strength;
}

Player* Match::chooseScorer(const std::vector<Player*>& players) {
    std::vector<Player*> weightedPool;

    for (Player* p : players) {

        switch (p->getPosition()) {

            case Player::Position::FORWARD:
                for (int i = 0; i < 5; i++)
                    weightedPool.push_back(p);
            break;

            case Player::Position::WINGER:
                for (int i = 0; i < 4; i++)
                    weightedPool.push_back(p);
            break;

            case Player::Position::MIDFIELDER:
                for (int i = 0; i < 2; i++)
                    weightedPool.push_back(p);
            break;

            case Player::Position::DEFENDER:
                weightedPool.push_back(p);
            break;

            default:
                break;
        }
    }

    if (weightedPool.empty()) {
        return players[std::rand() % players.size()];
    }

    return weightedPool[std::rand() % weightedPool.size()];
}

Match::MatchResult Match::play() {

    if (this->finished) {
        return {this->host, this->guest, this->hostGoals, this->guestGoals, this->matchResult.goals};
    }

    static bool seeded = false;
    if (!seeded) {
        std::srand((unsigned)std::time(nullptr));
        seeded = true;
    }

    MatchResult result;
    result.home = this->host;
    result.guest = this->guest;

    const unsigned hostAttack =
        calculateAttackStrength(this->hostLineup);

    const unsigned guestAttack =
        calculateAttackStrength(this->guestLineup);

    const unsigned hostDefense =
        calculateDefenseStrength(this->hostLineup);

    const unsigned guestDefense =
        calculateDefenseStrength(this->guestLineup);

    const int hostAdvantage = 5;

    unsigned hostGoals = 0;
    unsigned guestGoals = 0;

    std::vector<MatchResult::Scorer> goals;

    // HOME ATTACKS
    for (int i = 0; i < 10; i++) {

        int chance = 30 + hostAttack - guestDefense + hostAdvantage;
        if (chance < 5) chance = 5;
        if (chance > 80) chance = 80;

        if ((std::rand() % 100) < chance) {
            ++hostGoals;

            Player* scorer = chooseScorer(this->hostLineup.getPlayers());
            goals.push_back({scorer, true});
        }
    }

    // GUEST ATTACKS
    for (int i = 0; i < 10; i++) {

        int chance = 30 + guestAttack - hostDefense;
        if (chance < 5) chance = 5;
        if (chance > 80) chance = 80;

        if ((std::rand() % 100) < chance) {
            ++guestGoals;

            Player* scorer = chooseScorer(this->guestLineup.getPlayers());
            goals.push_back({scorer, false});
        }
    }

    hostGoals = std::min(hostGoals, 8u);
    guestGoals = std::min(guestGoals, 8u);

    result.homeGoals = hostGoals;
    result.guestGoals = guestGoals;
    result.goals = goals;

    return result;
}