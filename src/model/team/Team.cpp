#include "Team.h"

#include "../../utils/Utils.h"
#include "validator/TeamValidator.h"
#include "../../utils/validator/StringValidator.h"
#include "manager/TeamManager.h"
#include "../../utils/ExceptionMessages.h"

Team::Statistics::Statistics()
: winsCount(0), drawsCount(0), lossesCount(0), scoredGoals(0), concededGoals(0) {
}

void Team::Statistics::increaseWinsCount(unsigned wins) {
    this->winsCount += wins;
}

void Team::Statistics::increaseDrawsCount(unsigned draws) {
    this->drawsCount += draws;
}

void Team::Statistics::increaseLossesCount(unsigned losses) {
    this->lossesCount += losses;
}

void Team::Statistics::increaseScoredGoals(unsigned scoredGoals) {
    this->scoredGoals += scoredGoals;
}

void Team::Statistics::increaseConcededGoals(unsigned concededGoals) {
    this->concededGoals += concededGoals;
}

void Team::buyPlayer(Player& player, Player::Position playerPos, double remainingBudget, bool isTransfer) {
    this->players.emplace_back(player);
    if(isTransfer) {
        this->budget = remainingBudget;
    }

    if (playerPos == Player::Position::FORWARD) this->forwardersCount++;
    else if (playerPos == Player::Position::WINGER) this->wingersCount++;
    else if (playerPos == Player::Position::DEFENDER) this->defendersCount++;
    else if (playerPos == Player::Position::MIDFIELDER) this->midfieldersCount++;
    else if (playerPos == Player::Position::GOALKEEPER) this->goalkeepersCount++;
}

void Team::removePlayer(const std::string& playerName) {
    for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ) {
        if (it->getName() == playerName) {
            it = players.erase(it);
        } else {
            ++it;
        }
    }
}

void Team::setTeamManager(const TeamManager& teamManager) {
    this->teamManager = new TeamManager(teamManager);
}

Team::Team(TeamType type,
         const std::string &name,
         const std::string &stadiumName,
         const std::vector<Player> &players,
         double budget,
         unsigned forwardersCount,
         unsigned midfieldersCount,
         unsigned goalkeepersCount,
         unsigned defendersCount,
         unsigned wingersCount)
: type(type), name(name), stadiumName(stadiumName), players(players), budget(budget),
stats(Statistics()), teamManager(nullptr), forwardersCount(forwardersCount), midfieldersCount(midfieldersCount),
goalkeepersCount(goalkeepersCount), defendersCount(defendersCount), wingersCount(wingersCount) {
    StringValidator::validate(name, toString(ExceptionMessages::TEAM_NAME_CANNOT_BE_EMPTY), toString(ExceptionMessages::TEAM_NAME_CANNOT_BE_BLANK));
    StringValidator::validate(stadiumName, toString(ExceptionMessages::STADIUM_NAME_CANNOT_BE_EMPTY), toString(ExceptionMessages::STADIUM_NAME_CANNOT_BE_BLANK));
    unsigned maxTeamSize = players.size() * (players.size() - 1);
    TeamValidator::validateTeamSize(players.size(), maxTeamSize);
    TeamValidator::validateBudget(budget);
    TeamValidator::validateForwarders(forwardersCount);
    TeamValidator::validateMidfielders(midfieldersCount);
    TeamValidator::validateGoalkeepers(goalkeepersCount);
    TeamValidator::validateDefenders(defendersCount);
    TeamValidator::validateWingers(wingersCount);
}

Team::Team()
    : type(TeamType::UNKNOWN), name(std::string()), stadiumName(std::string()), players(std::vector<Player>()),
        budget(0.0), stats(Team::Statistics()), teamManager(nullptr), forwardersCount(0),
        midfieldersCount(0), goalkeepersCount(0), defendersCount(0), wingersCount(0) {
}

Team::Team(TeamType type, const std::string& name, const std::string &stadiumName, const double budget)
    : type(type), name(name), stadiumName(stadiumName), players(std::vector<Player>()),
        budget(budget), stats(Team::Statistics()), teamManager(nullptr), forwardersCount(0),
        midfieldersCount(0), goalkeepersCount(0), defendersCount(0), wingersCount(0) {

    StringValidator::validate(name, toString(ExceptionMessages::TEAM_NAME_CANNOT_BE_EMPTY), toString(ExceptionMessages::TEAM_NAME_CANNOT_BE_BLANK));
    StringValidator::validate(stadiumName, toString(ExceptionMessages::STADIUM_NAME_CANNOT_BE_EMPTY), toString(ExceptionMessages::STADIUM_NAME_CANNOT_BE_BLANK));
    TeamValidator::validateBudget(budget);
}

Team::Team(const Team& other)
    : type(other.type),
      name(other.name),
      stadiumName(other.stadiumName),
      players(other.players),
      budget(other.budget),
      stats(other.stats),
      teamManager(other.teamManager ? new TeamManager(*other.teamManager) : nullptr),
      forwardersCount(other.forwardersCount),
      midfieldersCount(other.midfieldersCount),
      goalkeepersCount(other.goalkeepersCount),
      defendersCount(other.defendersCount),
      wingersCount(other.wingersCount)
{
}

Team::Team(Team&& other) noexcept {
    type = other.type;
    name = std::move(other.name);
    stadiumName = std::move(other.stadiumName);
    players = std::move(other.players);
    budget = other.budget;
    stats = other.stats;
    teamManager = other.teamManager;

    forwardersCount = other.forwardersCount;
    midfieldersCount = other.midfieldersCount;
    goalkeepersCount = other.goalkeepersCount;
    defendersCount = other.defendersCount;
    wingersCount = other.wingersCount;

    other.teamManager = nullptr;
}

Team& Team::operator=(Team&& other) noexcept {
    if (this != &other) {
        delete teamManager; teamManager = nullptr;

        type = other.type;
        name = std::move(other.name);
        stadiumName = std::move(other.stadiumName);
        players = std::move(other.players);
        budget = other.budget;
        stats = other.stats;
        teamManager = other.teamManager;

        forwardersCount = other.forwardersCount;
        midfieldersCount = other.midfieldersCount;
        goalkeepersCount = other.goalkeepersCount;
        defendersCount = other.defendersCount;
        wingersCount = other.wingersCount;

        other.teamManager = nullptr;
    }
    return *this;
}

Team::~Team() noexcept
{
    delete teamManager;
}

const std::string & Team::getName() const {
    return this->name;
}

const std::vector<Player>& Team::getPlayers() const {
    return this->players;
}

Team::Statistics& Team::getStats() {
    return this->stats;
}

std::ostream& operator<<(std::ostream& os, const Team& team)
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

std::istream& operator>>(std::istream& is, Team& team)
{
    std::string typeStr;
    std::string name;
    std::string stadium;

    double budget;
    Team::Statistics stats;

    unsigned f, m, gk, d, w;
    size_t playerCount;

    is >> std::ws;
    char ch = is.peek();
    if(ch == EOF) {
        throw std::invalid_argument(toString(ExceptionMessages::CANNOT_READ_TEAM));
    }
    while(ch != '\n' || ch != EOF) {
        ch = is.peek();
        if(ch == EOF) {
            throw std::invalid_argument(toString(ExceptionMessages::CANNOT_READ_TEAM));
        }
    }
    std::getline(is, typeStr);
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

    for (size_t i = 0; i < playerCount; i++)
    {
        Player p;
        is >> p;
        players.push_back(p);
    }

    TeamType tempType = Utils::parseTeamType(typeStr);
    Team* tempTeam = nullptr;
    try {
        tempTeam = TeamFactory::fullyInitializeTeam(tempType, name, stadium, players, budget, f, m, gk, d, w);
        team = std::move(*tempTeam);
    } catch (...) {
        delete tempTeam;
        throw;
    }

    return is;
}