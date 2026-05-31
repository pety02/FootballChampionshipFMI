//
// Created by User on 5/17/2026.
//

#ifndef ACCOUNTINGMANAGER_H
#define ACCOUNTINGMANAGER_H

#include "../../player/Player.h"
#include "../../team/Team.h"

class AccountingManager final {
public:
    AccountingManager() = default;

    void regulateSalary(Player& player, Team& team);
};

#endif //ACCOUNTINGMANAGER_H