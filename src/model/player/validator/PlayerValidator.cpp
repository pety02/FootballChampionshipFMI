//
// Created by User on 5/16/2026.
//

#include "../player/validator/PlayerValidator.h"
#include <stdexcept>
#include "../../../utils/ExceptionMessages.h"

void PlayerValidator::validateNumber(unsigned number) {
  if(number == 0) throw std::invalid_argument(toString(ExceptionMessages::PLAYER_NUMBER_MUST_BE_POSITIVE));
  if(number > 20) throw std::invalid_argument(toString(ExceptionMessages::PLAYER_NUMBER_MUST_BE_LESS_THAN_OR_EQUAL_TO));
}

void PlayerValidator::validatePosition(Player::Position position) {
  if(position <= Player::Position::UNKNOWN || Player::Position::COUNT <= position)
    throw std::invalid_argument(toString(ExceptionMessages::PLAYER_POSITION_MUST_BE_ONE_OF_THE_GIVEN));
}

void PlayerValidator::validateSalary(double salary) {
  if(salary < 0.0) throw std::invalid_argument(toString(ExceptionMessages::SALARY_MUST_BE_NON_NEGATIVE));
}

void PlayerValidator::validateTransferSum(double transferSum) {
  if(transferSum < 0.0) throw std::invalid_argument(toString(ExceptionMessages::TRANSFER_SUM_MUST_BE_NON_NEGATIVE));
}

void PlayerValidator::validateName(const std::string &firstPlayerName, std::string secondPlayerName) {
  if(firstPlayerName == secondPlayerName) {
    throw std::invalid_argument(toString(ExceptionMessages::PLAYER_WITH_THIS_NAME_ALREADY_EXISTS));
  }
}