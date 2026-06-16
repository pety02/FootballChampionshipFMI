//
// Created by User on 5/17/2026.
//

#include "../simulation/FootballGameSimulator.h"

#include <algorithm>
#include <memory>
#include "../../model/championship/validator/ChampionshipValidator.h"
#include "../../simulation/validator/FootballGameSimulatorValidator.h"

std::vector<std::string> FootballGameSimulator::getChampions() const {
    Map<std::string, unsigned> champions;

    for (auto& match : this->currentChampionship->getMatches()) {
        champions[match.getHost()->getName()].push_back(
            match.getHost()->getStats().scoredGoals);

        champions[match.getGuest()->getName()].push_back(
            match.getGuest()->getStats().scoredGoals);
    }

    // Convert Map → vector
    std::vector<std::pair<std::string, std::vector<unsigned>>> sortedTeams;

    for (const auto& [k, v] : champions) {
        sortedTeams.push_back(std::pair<std::string, std::vector<unsigned>>(k, v));
    }

    // sort by goals descending
    std::sort(sortedTeams.begin(), sortedTeams.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );

    // extract names
    std::vector<std::string> result;

    for (const auto& [name, goals] : sortedTeams) {
        result.push_back(name);
    }

    return result;
}

FootballGameSimulator::FootballGameSimulator() : championshipHistory(ChampionshipHistory()), currentChampionship(nullptr),
                                                 champion(std::string()), viceChampion(std::string()), bronzeTeam(std::string()), goalMaster(std::string()) {
}

void FootballGameSimulator::simulate() {
    for(const auto& match : this->currentChampionship->getMatches()) {
        this->play(new Match(match));
    }

    this->currentChampionship->finish();
}

void FootballGameSimulator::addMatch(const Match &match) {
    this->currentChampionship->addMatch(match);
}

void FootballGameSimulator::updateChampionshipRound() {
    this->currentChampionship->increaseRoundNumber();
}

std::string FootballGameSimulator::findGoalMaster() {
    std::string goalMasterName;
    Map<std::string, unsigned> scorers;

    for (const auto& match : this->currentChampionship->getMatches()) {

        // every occurrence in getScorers() = one scored goal
        for (const auto& scorer : match.getScorers()) {

            // unique player identification by name
            scorers[scorer->getName()].push_back(1);
        }
    }

    unsigned maxGoals = 0;

    for (const auto& scorer : scorers) {

        const std::string& scorerName = scorer.first;
        unsigned goals = scorer.second.size();

        if (goals > maxGoals) {
            maxGoals = goals;
            goalMasterName = scorerName;
        }
    }

    return goalMasterName;
}

void FootballGameSimulator::finishChampionship() {
    this->champion = this->getChampions()[0];
    this->viceChampion = this->getChampions()[1];
    this->bronzeTeam = this->getChampions()[2];
    this->goalMaster = this->findGoalMaster();

    this->championshipHistory.addChampionship(this->currentChampionship->getYear(), *this->currentChampionship);
}

void FootballGameSimulator::play(Match* match) {
    FootballGameSimulatorValidator::validateMatchExists(this->currentChampionship, *match);
    match->play();
}

void FootballGameSimulator::addScorer(Player* player, Match &match) {
    FootballGameSimulatorValidator::validateMatchExists(this->currentChampionship, match);
    for(const auto& hostLineupPlayer : match.getHostLineup().getPlayers()) {
        if(player->getName() == hostLineupPlayer->getName()) {
            match.addGoal(player, true);
            this->increaseHostGoals(match);
        }
    }

    for(const auto& guestLineupPlayer : match.getGuestLineup().getPlayers()) {
        if(player->getName() == guestLineupPlayer->getName()) {
            match.addGoal(player, false);
            this->increaseGuestGoals(match);
        }
    }
}

void FootballGameSimulator::increaseHostGoals(const Match &match) {
    ++match.getHost()->getStats().scoredGoals;
}

void FootballGameSimulator::increaseGuestGoals(const Match &match) {
    ++match.getGuest()->getStats().scoredGoals;
}

void FootballGameSimulator::finishMatch(Match &match) {
    FootballGameSimulatorValidator::validateMatchExists(this->currentChampionship, match);

    // update the team statistics
    match.getHost()->getStats().scoredGoals += match.getHostGoals();
    match.getHost()->getStats().concededGoals += match.getGuestGoals();

    match.getGuest()->getStats().scoredGoals += match.getGuestGoals();
    match.getGuest()->getStats().concededGoals += match.getHostGoals();

    if(match.getGuestGoals() < match.getHostGoals()) {
        match.getHost()->getStats().winsCount++;
        match.getGuest()->getStats().lossesCount++;
    } else if (match.getHostGoals() == match.getGuestGoals()) {
        match.getHost()->getStats().drawsCount++;
        match.getGuest()->getStats().drawsCount++;
    } else {
        match.getHost()->getStats().lossesCount++;
        match.getGuest()->getStats().winsCount++;
    }

    // update the players statistics
    for (auto hostLineupPlayer : match.getHostLineup().getPlayers()) {
        hostLineupPlayer->getStats().matchesCount++;
        for (auto hostPlayer : match.getHost()->getPlayers()) {
            if(hostLineupPlayer->getName() == hostPlayer->getName()) {
                hostLineupPlayer->getStats().scoredGoals += 1;
            }
        }
    }
    for (auto& guestLineupPlayer : match.getGuestLineup().getPlayers()) {
        guestLineupPlayer->getStats().matchesCount++;
        for (auto guestPlayer : match.getGuest()->getPlayers()) {
            if(guestLineupPlayer->getName() == guestPlayer->getName()) {
                guestLineupPlayer->getStats().scoredGoals += 1;
            }
        }
    }

    // update the round number
    match.increaseRoundNumber();

    // if the championship is on 35 level and the round should finish, finish the championship also
    this->currentChampionship->increaseRoundNumber();
    if(this->currentChampionship->getCurrentRoundNumber() == ChampionshipValidator::MAX_ROUND_NUMBER) {
        this->finishChampionship();
    }
}

const Championship& FootballGameSimulator::getCurrentChampionship() const {
    return *this->currentChampionship;
}