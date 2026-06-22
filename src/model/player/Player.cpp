//
// Created by User on 5/14/2026.
//

#include "../player/Player.h"

#include <iostream>

#include "validator/PlayerValidator.h"
#include "../../utils/ExceptionMessages.h"
#include "../../utils/validator/StringValidator.h"

Player::Statistics::Statistics(unsigned matchesCount, unsigned scoredGoals)
                    : matchesCount(matchesCount), scoredGoals(scoredGoals) {}

std::ostream& operator<<(std::ostream& os, const Player::Statistics& stats) {
    os << stats.matchesCount << "\n" << stats.scoredGoals << "\n";

    return os;
}

std::istream& operator>>(std::istream& is, Player::Statistics& stats) {
    unsigned matchesCount, scoredGoals;

    is >> matchesCount >> scoredGoals;
    stats = Player::Statistics(matchesCount, scoredGoals);

    return is;
}

void Player::Statistics::increaseMatchesCount() {
    ++this->matchesCount;
}

void Player::Statistics::increaseScoredGoals() {
    ++this->scoredGoals;
}

Player::Player(const std::string &name, const unsigned number,
    const Position position, const double salary, const double transferSum)
    : name(name), number(number), salary(salary), transferSum(transferSum) {

    StringValidator::validate(name, toString(ExceptionMessages::PLAYER_NAME_CANNOT_BE_EMPTY), toString(ExceptionMessages::PLAYER_NAME_CANNOT_BE_BLANK));
    PlayerValidator::validateNumber(number);
    PlayerValidator::validatePosition(position);
    PlayerValidator::validateSalary(salary);
    PlayerValidator::validateTransferSum(transferSum);

    this->setPosition(position);
}

Player::Player(const Player& other)
    : Player(other.name, other.number, other.position, other.salary, other.transferSum) {

}

Player& Player::operator=(const Player& other) {
    if(this != &other) {
        this->name = other.name;
        this->number = other.number;
        this->setPosition(other.position);
        this->salary = other.salary;
        this->transferSum = other.transferSum;
    }

    return *this;
}

void Player::setPosition(const Position position) {
    this->position = position;

    if (this->position == Position::FORWARD) {
        if (this->stats.scoredGoals < 6) {
            this->stats.scoredGoals = 6;
        }
    }
}

void Player::setSalary(const double salary) {
    this->salary = salary;
}

const std::string & Player::getName() const {
    return this->name;
}

unsigned Player::getNumber() const {
    return this->number;
}

Player::Position Player::getPosition() const {
    return this->position;
}

double Player::getSalary() const {
    return this->salary;
}

double Player::getTransferSum() const {
    return this->transferSum;
}

const Player::Statistics& Player::getStats() const {
    return this->stats;
}

Player::Statistics& Player::getStats() {
    return this->stats;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << player.name << '\n'
       << player.number << '\n'
       << static_cast<int>(player.position) << '\n'
       << player.salary << '\n'
       << player.transferSum << '\n'
       << player.stats << '\n';

    return os;
}

std::istream& operator>>(std::istream& is, Player& player)
{
    std::string name;
    unsigned number;
    int pos;
    double salary;
    double transferSum;
    Player::Statistics stats;

    std::getline(is >> std::ws, name);

    is >> number
       >> pos
       >> salary
       >> transferSum
       >> stats;

    player.name = name;
    player.number = number;
    player.setPosition(static_cast<Player::Position>(pos));
    player.salary = salary;
    player.transferSum = transferSum;
    player.stats = stats;

    return is;
}