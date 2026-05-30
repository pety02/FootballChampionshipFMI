//
// Created by User on 5/16/2026.
//

#include "PlayerValidator.h"
#include <stdexcept>

void PlayerValidator::validateNumber(unsigned number) {
  if(number == 0) throw std::invalid_argument("Player number must be positive.");
  if(number > 20) throw std::invalid_argument("Player number must be less than 20.");
}

void PlayerValidator::validatePosition(Player::Position position) {
  if(position <= Player::Position::UNKNOWN || Player::Position::COUNT <= position)
    throw std::invalid_argument("Player position must be GOALKEEPER, DEFENDER, MIDFIELDER, WINGER or FORWARD.");
}

void PlayerValidator::validateSalary(double salary) {
  if(salary < 0.0) throw std::invalid_argument("Salary must be non-negative.");
}

void PlayerValidator::validateTransferSum(double transferSum) {
  if(transferSum < 0.0) throw std::invalid_argument("TransferSum must be non-negative.");
}