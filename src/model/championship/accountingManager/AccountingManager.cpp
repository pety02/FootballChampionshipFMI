//
// Created by User on 5/17/2026.
//

#include "AccountingManager.h"

void AccountingManager::regulateSalary(Player& player, Team& team) {
    unsigned teamTotalMatches = 0;
    for (int index = 0; index < team.getPlayers().size(); index++) {
        if(player.getName() == team.getPlayers()[index].getName()) {
            teamTotalMatches = team.getStats().lossesCount + team.getStats().winsCount + team.getStats().drawsCount;
            break;
        }
    }

    double playerCurrentSalary = player.getSalary();
    unsigned playerTotalMatches = player.getStats().matchesCount;
    unsigned playerScoredGoals = player.getStats().scoredGoals;

    if(teamTotalMatches / 2 <= playerTotalMatches) {
        player.setSalary(1.20 * playerCurrentSalary);
    }

    if(teamTotalMatches < 7) {
        player.setSalary(0.90 * playerCurrentSalary);
    }

    if(10 < playerScoredGoals) {
        player.setSalary(1.20 * playerCurrentSalary);
    } else if(5 < playerScoredGoals) {
        player.setSalary(1.10 * playerCurrentSalary);
    } else if(playerScoredGoals < 5 && player.getPosition() == Player::Position::FORWARD) {
        player.setSalary(0.85 * playerCurrentSalary);
    }
}