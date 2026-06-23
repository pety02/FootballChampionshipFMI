//
// Created by User on 5/14/2026.
//

#include "BalancedTeam.h"
#include "../player/validator/PlayerValidator.h"
#include "validator/TeamValidator.h"
#include "../../utils/Utils.h"

BalancedTeam::BalancedTeam(TeamType type,
                 const std::string &name,
                 const std::string &stadiumName,
                 const std::vector<Player> &players,
                 double budget,
                 unsigned forwardersCount,
                 unsigned midfieldersCount,
                 unsigned goalkeepersCount,
                 unsigned defendersCount,
                 unsigned wingersCount)
:Team(type, name, stadiumName, players, budget, forwardersCount, midfieldersCount,
    goalkeepersCount, defendersCount, wingersCount) {}

BalancedTeam::BalancedTeam() : Team() {
}

BalancedTeam::BalancedTeam(const std::string &name, const std::string &stadiumName,
    double budget) : Team(TeamType::BALANCED, name, stadiumName, budget) {
}

BalancedTeam::BalancedTeam(const BalancedTeam &other)
    : Team(other)
{
}

BalancedTeam & BalancedTeam::operator=(const BalancedTeam &other) {
    if(this !=&other) {
        BalancedTeam temp(other);
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

BalancedTeam::BalancedTeam(BalancedTeam&& other) noexcept
    : Team(std::move(other))
{
}

BalancedTeam& BalancedTeam::operator=(BalancedTeam&& other) noexcept
{
    if (this != &other)
    {
        Team::operator=(std::move(other));
    }
    return *this;
}

Team * BalancedTeam::clone() const {
    return new BalancedTeam(*this);
}

void BalancedTeam::addPlayer(Player& player, bool isTransfer) {
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
    size_t missingGK = (this->goalkeepersCount < BalancedTeam::REQUIRED_GOALKEEPERS) ? (BalancedTeam::REQUIRED_GOALKEEPERS - this->goalkeepersCount) : 0;
    size_t missingFW = (this->forwardersCount < BalancedTeam::MIN_FORWARDERS_REQUIRED) ? (BalancedTeam::MIN_FORWARDERS_REQUIRED - this->forwardersCount) : 0;
    size_t missingDF = (this->defendersCount < BalancedTeam::MIN_DEFENDERS_REQUIRED) ? (BalancedTeam::MIN_DEFENDERS_REQUIRED - this->defendersCount) : 0;
    size_t missingMF = (this->midfieldersCount < BalancedTeam::MIN_MIDFIELDERS_REQUIRED) ? (BalancedTeam::MIN_MIDFIELDERS_REQUIRED - this->midfieldersCount) : 0;
    size_t missingWG = (this->wingersCount < BalancedTeam::MIN_WINGERS_REQUIRED) ? (BalancedTeam::MIN_WINGERS_REQUIRED - this->wingersCount) : 0;

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