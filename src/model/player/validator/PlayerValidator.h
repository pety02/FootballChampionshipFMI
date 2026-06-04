//
// Created by User on 5/16/2026.
//

#ifndef PLAYERVALIDATOR_H
#define PLAYERVALIDATOR_H

#include "../player/Player.h"

/**
*
*/
class PlayerValidator final {
public:
    PlayerValidator() = default;

    /**
    *
    */
    static void validateNumber(unsigned number);

    /**
    *
    */
    static void validatePosition(Player::Position position);

    /**
    *
    */
    static void validateSalary(double salary);

    /**
    *
    */
    static void validateTransferSum(double transferSum);

    static void validateName(const std::string& firstPlayerName, std::string secondPlayerName);
};

#endif //PLAYERVALIDATOR_H