//
// Created by User on 5/14/2026.
//

#include "../player/Player.h"
#include "validator/PlayerValidator.h"
#include "../../utils/ExceptionMessages.h"
#include "../../utils/validator/StringValidator.h"

void Player::Statistics::increaseMatchesCount() {
    ++this->matchesCount;
}

void Player::Statistics::increaseScoredGoals() {
    ++this->scoredGoals;
}

Player::Player(const std::string &name, const unsigned number,
    const Position position, const double salary, const double transferSum)
    : name(name), number(number), position(position), salary(salary), transferSum(transferSum) {

    StringValidator::validate(name, toString(ExceptionMessages::PLAYER_NAME_CANNOT_BE_EMPTY), toString(ExceptionMessages::PLAYER_NAME_CANNOT_BE_BLANK));
    PlayerValidator::validateNumber(number);
    PlayerValidator::validatePosition(position);
    PlayerValidator::validateSalary(salary);
    PlayerValidator::validateTransferSum(transferSum);
}

Player::Player(const Player& other)
    : Player(other.name, other.number, other.position, other.salary, other.transferSum) {

}

Player& Player::operator=(const Player& other) {
    if(this != &other) {
        this->name = other.name;
        this->number = other.number;
        this->position = other.position;
        this->salary = other.salary;
        this->transferSum = other.transferSum;
    }

    return *this;
}

void Player::setNumber(const unsigned number) {
    this->number = number;
}

void Player::setPosition(const Position position) {
    this->position = position;
}

void Player::setSalary(const double salary) {
    this->salary = salary;
}

void Player::setTransferSum(const double transferSum) {
    this->transferSum = transferSum;
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