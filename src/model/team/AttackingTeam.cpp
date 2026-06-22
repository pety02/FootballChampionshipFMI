//
// Created by User on 5/14/2026.
//

#include "AttackingTeam.h"

#include "../../utils/ExceptionMessages.h"
#include "../player/validator/PlayerValidator.h"
#include "validator/TeamValidator.h"

AttackingTeam::AttackingTeam() : Team() {
}

AttackingTeam::AttackingTeam(const std::string &name, const std::string &coachName, const std::string &stadiumName,
    double budget) : Team(TeamType::ATTACKING, name, coachName, stadiumName, budget) {
}

AttackingTeam::AttackingTeam(const AttackingTeam &other)
    : Team(other)
{
}

AttackingTeam & AttackingTeam::operator=(const AttackingTeam &other) {
    if(this !=&other) {
        AttackingTeam temp(other);
        std::swap(type, temp.type);
        std::swap(name, temp.name);
        std::swap(stadiumName, temp.stadiumName);
        std::swap(players, temp.players);
        std::swap(budget, temp.budget);
        std::swap(stats, temp.stats);
        std::swap(teamManager, temp.teamManager);
        std::swap(forwardersCount, temp.forwardersCount);
        std::swap(midfieldersCount, temp.midfieldersCount);
        std::swap(goalkeepersCount, temp.goalkeepersCount);
        std::swap(defendersCount, temp.defendersCount);
        std::swap(wingersCount, temp.wingersCount);
    }

    return *this;
}

AttackingTeam::AttackingTeam(AttackingTeam&& other) noexcept
    : Team(std::move(other))
{
}

AttackingTeam& AttackingTeam::operator=(AttackingTeam&& other) noexcept
{
    if (this != &other)
    {
        Team::operator=(std::move(other));
    }
    return *this;
}

Team * AttackingTeam::clone() const {
    return new AttackingTeam(*this);
}

void AttackingTeam::addPlayer(Player& player, bool isTransfer) {
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

    // 4. Specific validation for forwarders (Min 6 scored goals) in an attacking team
    TeamValidator::validatePlayerScoredGoals(playerPosition, Player::Position::FORWARD, player.getStats().scoredGoals,
        AttackingTeam::FORWARD_MIN_SCORED_GOALS, player.getName(), this->name);

    // 5. Calculate remaining positions and their required minimum after inserting the current player
    size_t remainingPlaces = Team::MAX_TEAM_SIZE - (this->players.size() + 1);

    // 6. Calculates how many players are required till the bear minimum for each position
    size_t missingGK = (this->goalkeepersCount < AttackingTeam::REQUIRED_GOALKEEPERS) ? (AttackingTeam::REQUIRED_GOALKEEPERS - this->goalkeepersCount) : 0;
    size_t missingFW = (this->forwardersCount < AttackingTeam::MIN_FORWARDERS_REQUIRED) ? (AttackingTeam::MIN_FORWARDERS_REQUIRED - this->forwardersCount) : 0;
    size_t missingDF = (this->defendersCount < AttackingTeam::MIN_DEFENDERS_REQUIRED) ? (AttackingTeam::MIN_DEFENDERS_REQUIRED - this->defendersCount) : 0;
    size_t missingMF = (this->midfieldersCount < AttackingTeam::MIN_MIDFIELDERS_REQUIRED) ? (AttackingTeam::MIN_MIDFIELDERS_REQUIRED - this->midfieldersCount) : 0;
    size_t missingWG = (this->wingersCount < AttackingTeam::MIN_WINGERS_REQUIRED) ? (AttackingTeam::MIN_WINGERS_REQUIRED - this->wingersCount) : 0;

    // 7. Check if the inserting of the current player blocks the bear minimum for other positions
    std::vector<unsigned> args;
    std::string errorMessage;

    switch (playerPosition) {
        case Player::Position::FORWARD:
            args = {missingGK, missingDF, missingMF, missingWG}; errorMessage = toString(ExceptionMessages::TOO_MANY_FORWARDERS); break;
        case Player::Position::WINGER:
            args = {missingGK, missingFW, missingDF, missingMF}; errorMessage = toString(ExceptionMessages::TOO_MANY_WINGERS); break;
        case Player::Position::DEFENDER:
            args = {missingGK, missingFW, missingMF, missingWG}; errorMessage = toString(ExceptionMessages::TOO_MANY_DEFENDERS); break;
        case Player::Position::MIDFIELDER:
            args = {missingGK, missingFW, missingDF, missingWG}; errorMessage = toString(ExceptionMessages::TOO_MANY_MIDFIELDERS); break;
        case Player::Position::GOALKEEPER:
            args = {missingFW, missingDF, missingMF, missingWG}; errorMessage = toString(ExceptionMessages::TOO_MANY_GOALKEEPERS); break;
        default:
            break;
    }

    TeamValidator::validatePlayersCountByPosition(args, remainingPlaces, errorMessage);

    // 8. Buy player if all validations passed successfully
    this->buyPlayer(player, playerPosition, remainingBudget, isTransfer);
}

std::ostream& operator<<(std::ostream& os, const AttackingTeam& team)
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

std::istream& operator>>(std::istream& is, AttackingTeam& team)
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