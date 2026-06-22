//
// Created by User on 5/14/2026.
//

#include "DefensiveTeam.h"
#include "../player/validator/PlayerValidator.h"
#include "validator/TeamValidator.h"

DefensiveTeam::DefensiveTeam() : Team() {
}

DefensiveTeam::DefensiveTeam(const std::string &name, const std::string &coachName, const std::string &stadiumName,
    double budget) : Team(TeamType::DEFENSIVE, name, coachName, stadiumName, budget) {
}

DefensiveTeam::DefensiveTeam(const DefensiveTeam &other) : Team(other) {
}

DefensiveTeam & DefensiveTeam::operator=(const DefensiveTeam &other) {
    Team::operator=(other);
    return *this;
}

Team* DefensiveTeam::clone() const {
    return new DefensiveTeam(*this);
}

void DefensiveTeam::addPlayer(Player& player, bool isTransfer) {
    // 1. Max team's size check
    TeamValidator::validateTeamSize(this->players.size(), Team::MAX_TEAM_SIZE);

    // 2. Validates the budget and calculate the remaining budget
    double remainingBudget = this->budget - player.getTransferSum();
    TeamValidator::validateRemainingBudget(remainingBudget);

    TeamValidator::validateUniquePlayerNumber(*this, player.getNumber());
    TeamValidator::validateUniquePlayerName(*this, player.getName());

    // 3. Validate playing positions
    Player::Position playerPosition = player.getPosition();
    PlayerValidator::validatePosition(playerPosition);

    // 4. Calculate remaining positions and their required minimum after inserting the current player
    size_t remainingPlaces = Team::MAX_TEAM_SIZE - (this->players.size() + 1);

    // 5. Calculates how many players are required till the bear minimum for each position
    size_t missingGK = (this->goalkeepersCount < DefensiveTeam::REQUIRED_GOALKEEPERS) ? (DefensiveTeam::REQUIRED_GOALKEEPERS - this->goalkeepersCount) : 0;
    size_t missingFW = (this->forwardersCount < DefensiveTeam::MIN_FORWARDERS_REQUIRED) ? (DefensiveTeam::MIN_FORWARDERS_REQUIRED - this->forwardersCount) : 0;
    size_t missingDF = (this->defendersCount < DefensiveTeam::MIN_DEFENDERS_REQUIRED) ? (DefensiveTeam::MIN_DEFENDERS_REQUIRED - this->defendersCount) : 0;
    size_t missingMF = (this->midfieldersCount < DefensiveTeam::MIN_MIDFIELDERS_REQUIRED) ? (DefensiveTeam::MIN_MIDFIELDERS_REQUIRED - this->midfieldersCount) : 0;
    size_t missingWG = (this->wingersCount < DefensiveTeam::MIN_WINGERS_REQUIRED) ? (DefensiveTeam::MIN_WINGERS_REQUIRED - this->wingersCount) : 0;

    // 6. Check if the inserting of the current player blocks the bear minimum for other positions
    std::vector<unsigned> args;
    std::string errorMessage;

    switch (playerPosition) {
        case Player::Position::FORWARD:
            args = {missingGK, missingDF, missingMF, missingWG}; errorMessage = "Too many forwarders."; break;
        case Player::Position::WINGER:
            args = {missingGK, missingFW, missingDF, missingMF}; errorMessage = "Too many wingers."; break;
        case Player::Position::DEFENDER:
            args = {missingGK, missingFW, missingMF, missingWG}; errorMessage = "Too many defenders."; break;
        case Player::Position::MIDFIELDER:
            args = {missingGK, missingFW, missingDF, missingWG}; errorMessage = "Too many midfielders."; break;
        case Player::Position::GOALKEEPER:
            args = {missingFW, missingDF, missingMF, missingWG}; errorMessage = "Too many goalkeepers."; break;
        default:
            break;
    }

    TeamValidator::validatePlayersCountByPosition(args, remainingPlaces, errorMessage);

    // 7. Buy player if all validations passed successfully
    this->buyPlayer(player, playerPosition, remainingBudget, isTransfer);
}

std::ostream& operator<<(std::ostream& os, const DefensiveTeam& team)
{
    os << Utils::toString(team.type) << '\n'
       << team.name << '\n'
       << team.stadiumName << '\n'
       << team.budget << '\n'
       << team.stats << '\n'
       << team.forwardersCount << '\n'
       << team.midfieldersCount << '\n'
       << team.goalkeepersCount << '\n'
       << team.defendersCount << '\n'
       << team.wingersCount << '\n'
       << team.players.size() << '\n';

    for(const auto& p : team.players)
        os << p;

    return os;
}

std::istream& operator>>(std::istream& is, DefensiveTeam& team)
{
    std::string typeStr;
    std::string name;
    std::string stadium;

    double budget;
    Team::Statistics stats;

    unsigned f,m,gk,d,w;
    size_t playerCount;

    std::getline(is >> std::ws, typeStr);
    std::getline(is, name);
    std::getline(is, stadium);

    is >> budget
       >> stats
       >> f
       >> m
       >> gk
       >> d
       >> w
       >> playerCount;

    std::vector<Player> players;

    for(size_t i=0;i<playerCount;i++)
    {
        Player p;
        is >> p;
        players.push_back(p);
    }

    team.type = Utils::parseTeamType(typeStr);
    team.name = name;
    team.stadiumName = stadium;
    team.budget = budget;
    team.stats = stats;

    team.forwardersCount = f;
    team.midfieldersCount = m;
    team.goalkeepersCount = gk;
    team.defendersCount = d;
    team.wingersCount = w;

    team.players = std::move(players);

    return is;
}