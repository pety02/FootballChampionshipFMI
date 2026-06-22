//
// Created by User on 6/19/2026.
//

#include "StatisticsEngine.h"
#include <iostream>
#include <algorithm>
#include "../../utils/ExceptionMessages.h"

Team::Statistics StatisticsEngine::listTeamStats(Team& team) {
    return team.getStats();
}

std::vector<Team::Statistics>StatisticsEngine::listSeasonStats(Championship &championship) {
    std::vector<Team::Statistics> stats;
    for (Team* team :
         championship.getTeamManager().getTeams()) {

        stats.push_back(team->getStats());
         }
    return stats;
}

std::vector<Player::Statistics>StatisticsEngine::listPlayerStats(const Team& team) {
    std::vector<Player::Statistics> stats = std::vector<Player::Statistics>();
    for (const Player& player: team.getPlayers()) {
        stats.push_back(player.getStats());
    }

    return stats;
}

void StatisticsEngine::viewPlayerRanking(Championship& championship) {
    for (const Team* team : championship.getTeamManager().getTeams()) {
        for (const Player& player : team->getPlayers()) {

            std::cout
                    << player.getName()
                    << " "
                    << player.getStats().scoredGoals
                    << '\n';
        }
    }
}

const Team& StatisticsEngine::getChampion(
        const Championship& championship) {

    std::vector<std::pair<Team*, unsigned>> champs = std::vector<std::pair<Team*, unsigned>>();

    for (Team* team : championship.getTeamManager().getTeams())
    {
        champs.emplace_back(team, team->getStats().scoredGoals);
    }

    // sort by goals (descending)
    std::ranges::sort(champs, std::less_equal<>());

    if (champs.size() < 3) {
        throw std::invalid_argument(toString(ExceptionMessages::INVALID_NUMBER_OF_TEAMS)); // here has memory leak but how to solve it
    }

    return *champs[0].first; // 1st place
}

const Team& StatisticsEngine::getRunnerUp(const Championship &championship) {
    std::vector<std::pair<Team*, unsigned>> champs = std::vector<std::pair<Team*, unsigned>>();

    for (Team* team : championship.getTeamManager().getTeams())
    {
        champs.emplace_back(team, team->getStats().scoredGoals);
    }

    // sort by goals (descending)
    std::ranges::sort(champs, std::less_equal<>());

    if (champs.size() < 3) {
        throw std::invalid_argument(toString(ExceptionMessages::INVALID_NUMBER_OF_TEAMS)); // here has memory leak but how to solve it
    }

    return *champs[1].first; // 2nd place
}

const Team& StatisticsEngine::getThirdPlace(const Championship &championship)
{
    std::vector<std::pair<Team*, unsigned>> champs = std::vector<std::pair<Team*, unsigned>>();

    for (Team* team : championship.getTeamManager().getTeams())
    {
        champs.emplace_back(team, team->getStats().scoredGoals);
    }

    // sort by goals (descending)
    std::ranges::sort(champs, std::less_equal<>());

    if (champs.size() < 3) {
        throw std::invalid_argument(toString(ExceptionMessages::INVALID_NUMBER_OF_TEAMS)); // here has memory leak but how to solve it
    }

    return *champs[2].first; // 3rd place
}