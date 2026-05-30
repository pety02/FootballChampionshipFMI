//
// Created by User on 5/17/2026.
//

#include "FootballGameSimulator.h"
#include <stdexcept>
#include "ChampionshipValidator.h"

void FootballGameSimulator::validateMatchExists(const Match &match) const {
    bool matchExists = false;
    for(const auto& currentChampionshipMatch : this->currentChampionship->getMatches()) {
        if(match.getHost()->getName() == currentChampionshipMatch.getHost()->getName()
            && match.getGuest()->getName() == currentChampionshipMatch.getGuest()->getName()) {
            matchExists = true;
            break;
            }
    }

    if(!matchExists) throw std::invalid_argument("Match does not exist in the current championship.");
}

void FootballGameSimulator::validateLineupExists(const Lineup& lineup, const Match& match) const {
    bool lineupExists = false;

    const std::vector<Match>& currentMatches = currentChampionship->getMatches();

    for (const auto & currentMatche : currentMatches) {

        if (match.getHost()->getName() == currentMatche.getHost()->getName()
                && match.getGuest()->getName() ==  match.getGuest()->getName()) {

            const Lineup& host = currentMatche.getHostLineup();
            const Lineup& guest = currentMatche.getGuestLineup();

            if (
                lineup.getTeam()->getName() == host.getTeam()->getName() ||
                lineup.getTeam()->getName() == guest.getTeam()->getName()
            ) {
                lineupExists = true;
                break;
            }
        }
    }

    if (!lineupExists) {
        throw std::invalid_argument(
            "Lineup does not exist in the current championship."
        );
    }
}

std::vector<std::string> FootballGameSimulator::getChampions() const {
    Map<std::string, unsigned> champions;

    for (const auto& match : this->currentChampionship->getMatches()) {
        champions[match.getHost()->getName()] +=
            match.getHost()->getStats().scoredGoals;

        champions[match.getGuest()->getName()] +=
            match.getGuest()->getStats().scoredGoals;
    }

    std::vector<std::pair<std::string, unsigned>> sortedTeams;

    for (const auto& champion : champions) {
        sortedTeams.push_back(champion);
    }

    // Bubble sort descending by goals
    for (int i = 0; i < (int)sortedTeams.size() - 1; i++) {
        for (int j = 0; j < (int)sortedTeams.size() - i - 1; j++) {
            if (sortedTeams[j].second < sortedTeams[j + 1].second) {
                std::pair<std::string, unsigned> temp = sortedTeams[j];
                sortedTeams[j] = sortedTeams[j + 1];
                sortedTeams[j + 1] = temp;
            }
        }
    }

    std::vector<std::string> result;

    for (const auto&[name, goals] : sortedTeams) {
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
            scorers[scorer->getName()]++;
        }
    }

    unsigned maxGoals = 0;

    for (const auto& scorer : scorers) {

        const std::string& scorerName = scorer.first;
        unsigned goals = scorer.second;

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
    this->validateMatchExists(*match);

    match->play();
}

void FootballGameSimulator::addScorer(Player* player, Match &match) {
    this->validateMatchExists(match);
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
    this->validateMatchExists(match);

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
    for (auto guestLineupPlayer : match.getGuestLineup().getPlayers()) {
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