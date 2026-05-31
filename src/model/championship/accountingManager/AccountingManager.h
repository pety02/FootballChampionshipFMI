//
// Created by User on 5/17/2026.
//

#ifndef ACCOUNTINGMANAGER_H
#define ACCOUNTINGMANAGER_H

#include "../../player/Player.h"
#include "../../team/Team.h"

/**
* A class that regulates the salary of a definite player in a definite team on the basis of
* the task requirements on the salary.
*/
class AccountingManager final {
public:
    /**
    * The default constructor of the AccountingManager class
    */
    AccountingManager() = default;

    /**
    * @brief Adjusts a player's salary based on participation and performance.
    *
    * The salary regulation process evaluates the player's contribution to the team
    * and updates their salary according to the following rules:
    *
    * - If the player has participated in at least half of the team's matches,
    *   their salary is increased by 20%.
    * - If the team has played fewer than 7 matches in total, the player's salary
    *   is reduced by 10%.
    * - Goal-scoring performance affects salary:
    *   - More than 10 goals: salary increased by 20%.
    *   - More than 5 goals: salary increased by 10%.
    *   - Fewer than 5 goals and the player is a forward: salary reduced by 15%.
    *
    * Team matches are calculated as the sum of wins, draws, and losses.
    * The method first verifies that the given player belongs to the specified team.
    *
    * @param player Reference to the player whose salary will be adjusted.
    * @param team Reference to the team used to evaluate participation and performance.
    */
    void regulateSalary(Player& player, Team& team);
};

#endif //ACCOUNTINGMANAGER_H