//
// Created by User on 5/14/2026.
//

#include "Team.h"

#include <utility>

#include "validator/TeamValidator.h"
#include "../../utils/validator/StringValidator.h"
#include "manager/TeamManager.h"
#include "../../utils/ExceptionMessages.h"

Team::Statistics::Statistics()
: winsCount(0), drawsCount(0), lossesCount(0), scoredGoals(0), concededGoals(0) {
}

void Team::Statistics::increaseWinsCount(unsigned wins) {
    this->winsCount += wins;
}

void Team::Statistics::increaseDrawsCount(unsigned draws) {
    this->drawsCount += draws;
}

void Team::Statistics::increaseLossesCount(unsigned losses) {
    this->lossesCount += losses;
}

void Team::Statistics::increaseScoredGoals(unsigned scoredGoals) {
    this->scoredGoals += scoredGoals;
}

void Team::Statistics::increaseConcededGoals(unsigned concededGoals) {
    this->concededGoals += concededGoals;
}

void Team::buyPlayer(Player& player, Player::Position playerPos, double remainingBudget, bool isTransfer) {
    this->players.emplace_back(player);
    if(isTransfer) {
        this->budget = remainingBudget;
    }

    if (playerPos == Player::Position::FORWARD) this->forwardersCount++;
    else if (playerPos == Player::Position::WINGER) this->wingersCount++;
    else if (playerPos == Player::Position::DEFENDER) this->defendersCount++;
    else if (playerPos == Player::Position::MIDFIELDER) this->midfieldersCount++;
    else if (playerPos == Player::Position::GOALKEEPER) this->goalkeepersCount++;
}

void Team::removePlayer(const std::string& playerName) {
    int i = 0;
    for (auto& player : this->players) {
        if (player.getName() == playerName) {
            this->players.erase(this->players.begin() + i);
        }
        i++;
    }
}

void Team::copy(const Team& other) {
    this->name = other.name;
    this->stadiumName = other.stadiumName;
    this->players.clear();
    for (auto player : other.players) {
        this->players.push_back(player);
    }
    this->budget = other.budget;
    this->stats.winsCount = other.stats.winsCount;
    this->stats.drawsCount = other.stats.drawsCount;
    this->stats.lossesCount = other.stats.lossesCount;
    this->stats.scoredGoals = other.stats.scoredGoals;
    this->stats.concededGoals = other.stats.concededGoals;

    this->teamManager = other.teamManager;
    this->forwardersCount = other.forwardersCount;
    this->wingersCount = other.wingersCount;
    this->defendersCount = other.defendersCount;
    this->midfieldersCount = other.midfieldersCount;
    this->goalkeepersCount = other.goalkeepersCount;
}

void Team::destroy() {
    delete this->teamManager; this->teamManager = nullptr;
}

Team::Team()
    : type(TeamType::UNKNOWN), name(std::string()), stadiumName(std::string()), players(std::vector<Player>()),
        budget(0.0), stats(Team::Statistics()), teamManager(nullptr), forwardersCount(0),
        midfieldersCount(0), goalkeepersCount(0), defendersCount(0), wingersCount(0) {
}

Team::Team(TeamType type, const std::string& name, const std::string& coachName, std::string  stadiumName, const double budget)
    : type(type), name(name), stadiumName(std::move(stadiumName)), players(std::vector<Player>()),
        budget(budget), stats(Team::Statistics()), teamManager(nullptr), forwardersCount(0),
        midfieldersCount(0), goalkeepersCount(0), defendersCount(0), wingersCount(0) {

    StringValidator::validate(name, toString(ExceptionMessages::TEAM_NAME_CANNOT_BE_EMPTY), toString(ExceptionMessages::TEAM_NAME_CANNOT_BE_BLANK));
    StringValidator::validate(name, toString(ExceptionMessages::STADIUM_NAME_CANNOT_BE_EMPTY), toString(ExceptionMessages::STADIUM_NAME_CANNOT_BE_BLANK));
    TeamValidator::validateBudget(budget);
}

Team::Team(const Team& other) {
    this->copy(other);
}

Team& Team::operator=(const Team &other) {
    if(this != &other) {
        this->destroy();
        this->copy(other);
    }

    return *this;
}

Team::~Team() noexcept {
    this->destroy();
}

void Team::setTeamName(const std::string &name) {
    this->name = name;
}

void Team::setStadiumName(const std::string &stadiumName) {
    this->stadiumName = stadiumName;
}

void Team::setBudget(double budget) {
    this->budget = budget;
}

const std::string & Team::getName() const {
    return this->name;
}

const std::string & Team::getCoachName() const {
    if (this->teamManager == nullptr) return "";

    return this->teamManager->getName();
}

const std::string & Team::getStadiumName() const {
    return this->stadiumName;
}

const std::vector<Player>& Team::getPlayers() const {
    return this->players;
}

double Team::getBudget() const {
    return this->budget;
}

Team::Statistics& Team::getStats() {
    return this->stats;
}