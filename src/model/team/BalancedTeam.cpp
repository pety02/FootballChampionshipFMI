//
// Created by User on 5/14/2026.
//

#include "BalancedTeam.h"
#include "../player/validator/PlayerValidator.h"
#include "validator/TeamValidator.h"

BalancedTeam::BalancedTeam() : Team() {
}

BalancedTeam::BalancedTeam(const std::string &name, const std::string &coachName, const std::string &stadiumName,
    double budget) : Team(TeamType::BALANCED, name, coachName, stadiumName, budget) {
}

BalancedTeam::BalancedTeam(const BalancedTeam &other) : Team(other) {
}

BalancedTeam & BalancedTeam::operator=(const BalancedTeam &other) {
    Team::operator=(other);
    return *this;
}

Team * BalancedTeam::clone() const {
    return new BalancedTeam(*this);
}

void BalancedTeam::addPlayer(Player& player, bool isTransfer) {
    // 1. Проверка за максимален размер на отбора
    TeamValidator::validateTeamSize(this->players.size(), Team::MAX_TEAM_SIZE);

    // 2. Валидация на бюджета (пресмятане на остатъка)
    double remainingBudget = this->budget - player.getTransferSum();
    TeamValidator::validateRemainingBudget(remainingBudget);

    TeamValidator::validateUniquePlayerNumber(*this, player.getNumber());
    TeamValidator::validateUniquePlayerName(*this, player.getName());

    // 3. Валидация на игралната позиция
    Player::Position playerPosition = player.getPosition();
    PlayerValidator::validatePosition(playerPosition);

    // 5. Изчисляване на оставащите места и нужния минимум по позиции
    // Взимаме броя места, които остават СЛЕД като добавим този играч
    size_t remainingPlaces = Team::MAX_TEAM_SIZE - (this->players.size() + 1);

    // Изчисляваме колко ОЩЕ играчи ни трябват за всяка позиция до минимума
    size_t missingGK = (this->goalkeepersCount < BalancedTeam::REQUIRED_GOALKEEPERS) ? (BalancedTeam::REQUIRED_GOALKEEPERS - this->goalkeepersCount) : 0;
    size_t missingFW = (this->forwardersCount < BalancedTeam::MIN_FORWARDERS_REQUIRED) ? (BalancedTeam::MIN_FORWARDERS_REQUIRED - this->forwardersCount) : 0;
    size_t missingDF = (this->defendersCount < BalancedTeam::MIN_DEFENDERS_REQUIRED) ? (BalancedTeam::MIN_DEFENDERS_REQUIRED - this->defendersCount) : 0;
    size_t missingMF = (this->midfieldersCount < BalancedTeam::MIN_MIDFIELDERS_REQUIRED) ? (BalancedTeam::MIN_MIDFIELDERS_REQUIRED - this->midfieldersCount) : 0;
    size_t missingWG = (this->wingersCount < BalancedTeam::MIN_WINGERS_REQUIRED) ? (BalancedTeam::MIN_WINGERS_REQUIRED - this->wingersCount) : 0;

    // 6. Проверка дали добавянето на текущия играч блокира задължителния минимум на другите позиции
    std::vector<unsigned> args;
    std::string errorMessage;

    switch (playerPosition) {
        case Player::Position::FORWARD:
            args = {missingGK, missingDF, missingMF, missingWG}; errorMessage = "Too many forwarders."; break;
        case Player::Position::WINGER:
            args = {missingGK, missingFW, missingDF, missingMF}; errorMessage = "Too many wingers."; break;
        case Player::Position::DEFENDER:
            args = {missingGK, missingFW, missingMF, missingWG}; errorMessage = "Too many defenders."; break;
        case Player::Position::MIDFIELDER:
            args = {missingGK, missingFW, missingDF, missingWG}; errorMessage = "Too many midfielders."; break;
        case Player::Position::GOALKEEPER:
            args = {missingFW, missingDF, missingMF, missingWG}; errorMessage = "Too many goalkeepers."; break;
        default:
            break;
    }

    TeamValidator::validatePlayersCountByPosition(args, remainingPlaces, errorMessage);

    // 7. Ако всички валидации преминат успешно, записваме промените
    this->buyPlayer(player, playerPosition, remainingBudget, isTransfer);
}
