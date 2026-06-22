//
// Created by User on 5/17/2026.
//

#include "FootballGameEngine.h"

#include <iostream>
#include <memory>
#include "engine/PlayerEngine.h"

#include "../MatchResultApplier.h"
#include "engine/StatisticsEngine.h"
#include "../../model/championship/validator/ChampionshipValidator.h"
#include "../../simulation/validator/FootballGameSimulatorValidator.h"
#include "../../utils/validator/CommandLineValidator.h"
#include "../../utils/ExceptionMessages.h"
#include "../utils/Utils.h"

std::vector<std::string> FootballGameEngine::getChampions() const
{
    std::vector<Pair<std::string, unsigned>> champions;

    for (Pair<std::string, unsigned>& champ : champions)
    {
        for (const Match& match : currentChampionship.getMatches())
        {
            if (champ.left == match.getHost()->getName())
                champ.right += match.getHostGoals();

            if (champ.left == match.getGuest()->getName())
                champ.right += match.getGuestGoals();
        }
    }

    // Manual selection sort (descending by goals)
    Utils::selectionSortByGoals(champions);

    std::vector<std::string> result;

    for (const Pair<std::string, unsigned>& champ : champions)
    {
        result.push_back(champ.left);
    }

    return result;
}

FootballGameEngine::FootballGameEngine() : championshipHistory(ChampionshipHistory()), currentChampionship(Championship()),
                                                 champion(std::string()), viceChampion(std::string()), bronzeTeam(std::string()), goalMaster(std::string()) {
}

void FootballGameEngine::simulate() {
    for(const Match& match : this->currentChampionship.getMatches()) {
        this->play(match);
    }

    this->currentChampionship.finish();
}

void FootballGameEngine::addMatch(const Match &match, Championship& championship) {
    championship.addMatch(match);
}

/*
void FootballGameEngine::updateChampionshipRound() {
    this->currentChampionship.increaseRoundNumber();
}
*/

std::string FootballGameEngine::findGoalMaster() {
    std::string goalMasterName;
    std::vector<Pair<std::string, unsigned>> scorers;

    for (const Match& match : this->currentChampionship.getMatches()) {

        // every occurrence in getScorers() = one scored goal
        for (const Player& scorer : match.getScorers()) {

            // unique player identification by name
            scorers.emplace_back(scorer.getName(), scorer.getStats().scoredGoals);
        }
    }

    unsigned maxGoals = 0;

    for (const Pair<std::string, unsigned>& scorer : scorers) {

        const std::string& scorerName = scorer.left;
        unsigned goals = scorer.right;

        if (goals > maxGoals) {
            maxGoals = goals;
            goalMasterName = scorerName;
        }
    }

    return goalMasterName;
}

void FootballGameEngine::finishChampionship() {
    for(Match& match : this->currentChampionship.getMatches()) {
        this->finishMatch(match);
    }

    this->champion = this->getChampions()[0];
    this->viceChampion = this->getChampions()[1];
    this->bronzeTeam = this->getChampions()[2];
    this->goalMaster = this->findGoalMaster();

    this->championshipHistory.addChampionship(this->currentChampionship);
}

void FootballGameEngine::play(const Match& match) const {
    FootballGameSimulatorValidator::validateMatchExists(new Championship(this->currentChampionship), match);

    std::cout << "Result: " << match.play();
}

void FootballGameEngine::addScorer(const Player& player, Match &match) const {
    FootballGameSimulatorValidator::validateMatchExists(new Championship(this->currentChampionship), match);
    for(const Player& hostLineupPlayer : match.getHostLineup().getPlayers()) {
        if(player.getName() == hostLineupPlayer.getName()) {
            match.addGoal(player, true);
            FootballGameEngine::increaseHostGoals(match);
        }
    }

    for(const Player& guestLineupPlayer : match.getGuestLineup().getPlayers()) {
        if(player.getName() == guestLineupPlayer.getName()) {
            match.addGoal(player, false);
            FootballGameEngine::increaseGuestGoals(match);
        }
    }
}

void FootballGameEngine::increaseHostGoals(const Match &match) {
    ++match.getHost()->getStats().scoredGoals;
}

void FootballGameEngine::increaseGuestGoals(const Match &match) {
    ++match.getGuest()->getStats().scoredGoals;
}

void FootballGameEngine::finishMatch(Match &match) {
    FootballGameSimulatorValidator::validateMatchExists(new Championship(this->currentChampionship), match);

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
    for (Player hostLineupPlayer : match.getHostLineup().getPlayers()) {
        hostLineupPlayer.getStats().matchesCount++;
        for (const Player& hostPlayer : match.getHost()->getPlayers()) {
            if(hostLineupPlayer.getName() == hostPlayer.getName()) {
                hostLineupPlayer.getStats().scoredGoals += 1;
            }
        }
    }
    for (Player guestLineupPlayer : match.getGuestLineup().getPlayers()) {
        guestLineupPlayer.getStats().matchesCount++;
        for (const Player& guestPlayer : match.getGuest()->getPlayers()) {
            if(guestLineupPlayer.getName() == guestPlayer.getName()) {
                guestLineupPlayer.getStats().scoredGoals += 1;
            }
        }
    }

    // update the round number
    match.increaseRoundNumber();

    // if the championship is on 35 level and the round should finish, finish the championship also
    this->currentChampionship.increaseRoundNumber();
    if(this->currentChampionship.getCurrentRoundNumber() == ChampionshipValidator::MAX_ROUND_NUMBER) {
        this->finishChampionship();
    }
}

const Championship& FootballGameEngine::getCurrentChampionship() const {
    return this->currentChampionship;
}

std::vector<Championship> FootballGameEngine::listSeasons(const ChampionshipHistory &championshipHistory) {

    return championshipHistory.getChampionships();
}

void FootballGameEngine::playAllMatches(
        Championship& championship) {
    for (const Match& match : championship.getMatches()) {
        FootballGameEngine simulator;
        simulator.play(match);
    }
}

void FootballGameEngine::showPodium(
        const Championship& championship) {

    std::cout << "Champion: " << StatisticsEngine::getChampion(championship).getName() << '\n';
}

void FootballGameEngine::finishSeason(
        ChampionshipHistory& history,
        Championship& championship) {

    playAllMatches(championship);

    history.addChampionship(championship);

    std::cout << "Season finished.\n";
}

void FootballGameEngine::viewMatches(
        const Championship& championship) {

    int index = 0;

    for (const Match& match : championship.getMatches()) {

        std::cout
                << ++index << ". "
                << match.getHost()->getName()
                << " vs "
                << match.getGuest()->getName()
                << '\n';
    }
}

void FootballGameEngine::enterMatchResult(const Match &match)
{
    Match::MatchResult result;

    result.home = match.getHost();
    result.guest = match.getGuest();

    std::vector<Match::MatchResult::Scorer*> goals;

    int totalGoalsCount = 0;

    while (totalGoalsCount <= 0)
    {
        std::cout << "Enter total goals count: ";
        std::cin >> totalGoalsCount;
    }

    unsigned remainingHomeGoals = 0;
    unsigned remainingGuestGoals = 0;

    for (int i = 0; i < totalGoalsCount; i++)
    {
        std::string playerName;
        std::cout << "Enter player name: ";
        std::cin >> playerName;

        unsigned scoredGoals;
        std::cout << "Enter goals: ";
        std::cin >> scoredGoals;

        if (CommandLineValidator::validateIsHomePlayer(playerName, *match.getHost()))
        {
            remainingHomeGoals += scoredGoals;

            goals.push_back(
                new Match::MatchResult::Scorer(
                    CommandLineValidator::resolvePlayer(playerName, *match.getHost()),
                    true
                )
            );
        }
        else if (CommandLineValidator::validateIsGuestPlayer(playerName, *match.getGuest()))
        {
            remainingGuestGoals += scoredGoals;

            goals.push_back(
                new Match::MatchResult::Scorer(
                    CommandLineValidator::resolvePlayer(playerName, *match.getGuest()),
                    false
                )
            );
        }
        else
        {
            throw std::invalid_argument(
                toString(ExceptionMessages::DOES_NOT_PLAY_IN_THIS_MATCH)
            );
        }
    }

    result.homeGoals = remainingHomeGoals;
    result.guestGoals = remainingGuestGoals;
    result.goals = goals;

    MatchResultApplier::apply(result);
}

std::vector<Team*> FootballGameEngine::listTeams(Championship &championship) {
    return championship.getTeamManager().getTeams();
}

void FootballGameEngine::addTeam(const std::vector<std::string> &args, Championship& championship) {
    if (args.empty())
        throw std::invalid_argument(toString(ExceptionMessages::INVALID_ARGUMENT));

    TeamType type = Utils::parseTeamType(args[0]);
    const std::string& name = args[1];
    const std::string& coach = args[2];
    const std::string& stadium = args[3];
    const double budget = std::stod(args[4]);

    // check duplicates
    for (const Team* currentTeam : championship.getTeamManager().getTeams())
    {
        if (currentTeam->getName() == name)
            throw std::invalid_argument(
                toString(ExceptionMessages::TEAM_ALREADY_EXISTS)
            );
    }

    Team* team = TeamFactory::createTeam(
        type,
        name,
        coach,
        stadium,
        budget
    );

    championship.getTeamManager().addTeam(team);
}

void FootballGameEngine::removeTeam(const std::string &teamName, Championship &championship) {
    for (const Team* currentTeam : championship.getTeamManager().getTeams()) {
        if (currentTeam->getName() != teamName)
            throw std::invalid_argument(toString(ExceptionMessages::TEAM_DOES_NOT_EXIST));
    }

    championship.getTeamManager().removeTeam(teamName);
}

// TODO: used only in tests can be removed
// void FootballGameEngine::autoSelectLineups(Match& match, Team* host, Team* guest) {
//     Lineup hostLineup = Lineup(host);
//     Lineup guestLineup = Lineup(guest);
//
//     match.setHostLineup(hostLineup);
//     match.setGuestLineup(guestLineup);
// }

void FootballGameEngine::deleteLineups(
        Match& match) {
    match.clearLineups();
}

std::vector<Player>FootballGameEngine::listTopScorers(
    const Team& team) {

    static std::vector<Player> scorers;

    for (const Player& player : team.getPlayers()) {

        scorers.push_back(
                player);
    }

    return scorers;
}

void FootballGameEngine::simulateGoal(const Match &match) {
    std::cout << "Select host or guest lineup as typing 'host' or 'guest': ";
    std::string lineup;
    while(lineup != "host" && lineup != "guest") {
        std::cin >> lineup;
    }

    if (lineup == "host") {
        match.getHost()->getStats().scoredGoals += 1;
        match.getGuest()->getStats().concededGoals += 1;
    } else {
        match.getGuest()->getStats().scoredGoals += 1;
        match.getHost()->getStats().concededGoals += 1;
    }
}

void FootballGameEngine::addManager(Team* team, TeamManager& teamManager) {
    team->setTeamManager(teamManager);
    teamManager.addTeam(team);
}