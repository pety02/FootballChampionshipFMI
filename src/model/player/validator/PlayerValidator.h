//
// Created by User on 5/16/2026.
//

#ifndef PLAYERVALIDATOR_H
#define PLAYERVALIDATOR_H

#include "../player/Player.h"

/**
 * A utility class responsible for validating player-related data.
 *
 * This class provides static helper methods used to verify whether
 * player properties satisfy the application's business rules before
 * a player is created or modified.
 */
class PlayerValidator final {
public:
    /**
     * Default constructor.
     */
    PlayerValidator() = default;

    /**
     * Validates a player's squad number.
     *
     * The number must satisfy the constraints defined by the application
     * (for example, being positive and within the allowed team size).
     *
     * @param number The player's squad number to validate.
     *
     * @throws std::invalid_argument If the number is invalid.
     */
    static void validateNumber(unsigned number);

    /**
     * Validates a player's position.
     *
     * Ensures that the specified position is one of the supported
     * football positions defined by the Player class.
     *
     * @param position The player's position to validate.
     *
     * @throws std::invalid_argument If the position is invalid.
     */
    static void validatePosition(Player::Position position);

    /**
     * Validates a player's salary.
     *
     * Salaries must comply with the application's financial rules
     * (for example, they cannot be negative).
     *
     * @param salary The salary value to validate.
     *
     * @throws std::invalid_argument If the salary is invalid.
     */
    static void validateSalary(double salary);

    /**
     * Validates a player's transfer value.
     *
     * Transfer sums must satisfy the application's constraints
     * (for example, they cannot be negative).
     *
     * @param transferSum The transfer value to validate.
     *
     * @throws std::invalid_argument If the transfer sum is invalid.
     */
    static void validateTransferSum(double transferSum);
};

#endif //PLAYERVALIDATOR_H