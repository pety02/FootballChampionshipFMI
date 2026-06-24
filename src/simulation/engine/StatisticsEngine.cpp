//
// Created by User on 6/19/2026.
//

#include "StatisticsEngine.h"
#include <iostream>
#include "../../utils/ExceptionMessages.h"
#include "../../utils/Utils.h"

std::vector<std::pair<Team*, unsigned>> StatisticsEngine::buildTeamRanking(const Championship& championship)
{
    std::vector<std::pair<Team*, unsigned>> ranking;

    for (Team* team : championship.getTeamManager().getTeams())
    {
        ranking.emplace_back(team, team->getStats().scoredGoals);
    }

    Utils::selectionSortTeamsByGoals(ranking);

    return ranking;
}

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

const Team& StatisticsEngine::getChampion(const Championship& championship)
{
    auto ranking = buildTeamRanking(championship);

    if (ranking.size() < 3)
    {
        throw std::invalid_argument(
            toString(ExceptionMessages::INVALID_NUMBER_OF_TEAMS));
    }

    return *ranking[0].first;
}

const Team& StatisticsEngine::getRunnerUp(const Championship& championship)
{
    auto ranking = buildTeamRanking(championship);

    if (ranking.size() < 3)
    {
        throw std::invalid_argument(
            toString(ExceptionMessages::INVALID_NUMBER_OF_TEAMS));
    }

    return *ranking[1].first;
}

const Team& StatisticsEngine::getThirdPlace(const Championship& championship)
{
    auto ranking = buildTeamRanking(championship);

    if (ranking.size() < 3)
    {
        throw std::invalid_argument(
            toString(ExceptionMessages::INVALID_NUMBER_OF_TEAMS));
    }

    return *ranking[2].first;
}