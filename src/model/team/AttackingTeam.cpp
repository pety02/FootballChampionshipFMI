//
// Created by User on 5/14/2026.
//

#include "AttackingTeam.h"

#include <stdexcept>

#include "../../utils/ExceptionMessages.h"
#include "../../player/validator/PlayerValidator.h"
#include "../../team/manager/TeamManager.h"
#include "../../team/validator/TeamValidator.h"

AttackingTeam::AttackingTeam() : Team() {
}

AttackingTeam::AttackingTeam(const std::string &name, const std::string &coachName, const std::string &stadiumName,
    double budget) : Team(TeamType::ATTACKING, name, coachName, stadiumName, budget) {
}

AttackingTeam::AttackingTeam(const AttackingTeam &other) : Team(other) {
}

Team * AttackingTeam::clone() const {
    return new AttackingTeam(*this);
}

void AttackingTeam::addPlayer(Player& player, bool isTransfer) {
    // 1. Проверка за максимален размер на отбора
    TeamValidator::validateTeamSize(this->players.size(), Team::MAX_TEAM_SIZE);

    // 2. Валидация на бюджета (пресмятане на остатъка)
    double remainingBudget = this->budget - player.getTransferSum();
    TeamValidator::validateRemainingBudget(remainingBudget);

    // 3. Валидация на игралната позиция
    Player::Position playerPosition = player.getPosition();
    PlayerValidator::validatePosition(playerPosition);

    // 4. Специфична валидация за нападатели (Минимум 6 отбелязани гола)
    // Забележка: по условие важи за ВСЕКИ нов нападател в AttackingTeam
    TeamValidator::validatePlayerScoredGoals(playerPosition, Player::Position::FORWARD, player.getStats().scoredGoals,
        AttackingTeam::FORWARD_MIN_SCORED_GOALS, player.getName(), this->name);

    // 5. Изчисляване на оставащите места и нужния минимум по позиции
    // Взимаме броя места, които остават СЛЕД като добавим този играч
    size_t remainingPlaces = Team::MAX_TEAM_SIZE - (this->players.size() + 1);

    // Изчисляваме колко ОЩЕ играчи ни трябват за всяка позиция до минимума
    size_t missingGK = (this->goalkeepersCount < AttackingTeam::REQUIRED_GOALKEEPERS) ? (AttackingTeam::REQUIRED_GOALKEEPERS - this->goalkeepersCount) : 0;
    size_t missingFW = (this->forwardersCount < AttackingTeam::MIN_FORWARDERS_REQUIRED) ? (AttackingTeam::MIN_FORWARDERS_REQUIRED - this->forwardersCount) : 0;
    size_t missingDF = (this->defendersCount < AttackingTeam::MIN_DEFENDERS_REQUIRED) ? (AttackingTeam::MIN_DEFENDERS_REQUIRED - this->defendersCount) : 0;
    size_t missingMF = (this->midfieldersCount < AttackingTeam::MIN_MIDFIELDERS_REQUIRED) ? (AttackingTeam::MIN_MIDFIELDERS_REQUIRED - this->midfieldersCount) : 0;
    size_t missingWG = (this->wingersCount < AttackingTeam::MIN_WINGERS_REQUIRED) ? (AttackingTeam::MIN_WINGERS_REQUIRED - this->wingersCount) : 0;

    // 6. Проверка дали добавянето на текущия играч блокира задължителния минимум на другите позиции
    std::vector<unsigned> args;
    std::string errorMessage;

    switch (playerPosition) {
        case Player::Position::FORWARD:
            args = {missingGK, missingDF, missingMF, missingWG}; errorMessage = toString(ExceptionMessages::TOO_MANY_FORWARDERS); break;
        case Player::Position::WINGER:
            args = {missingGK, missingFW, missingDF, missingMF}; errorMessage = toString(ExceptionMessages::TOO_MANY_WINGERS); break;
        case Player::Position::DEFENDER:
            args = {missingGK, missingFW, missingMF, missingWG}; errorMessage = toString(ExceptionMessages::TOO_MANY_DEFENDERS); break;
        case Player::Position::MIDFIELDER:
            args = {missingGK, missingFW, missingDF, missingWG}; errorMessage = toString(ExceptionMessages::TOO_MANY_MIDFIELDERS); break;
        case Player::Position::GOALKEEPER:
            args = {missingFW, missingDF, missingMF, missingWG}; errorMessage = toString(ExceptionMessages::TOO_MANY_GOALKEEPERS); break;
        default:
            break;
    }

    TeamValidator::validatePlayersCountByPosition(args, remainingPlaces, errorMessage);

    // 7. Ако всички валидации преминат успешно, записваме промените
    this->buyPlayer(player, playerPosition, remainingBudget, isTransfer);
}