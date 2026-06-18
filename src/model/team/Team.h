//
// Created by User on 5/14/2026.
//

#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>

#include "TeamType.h"
#include "../../utils/Utils.h"
//#include "manager/TeamManager.h"

class TeamManager;

#include "../player/Player.h"

/**
 * Base class representing a football team.
 *
 * This class defines the core properties and behavior shared by all
 * team types (Attacking, Defensive, Balanced, etc.).
 *
 * It manages players, financial data, and match statistics.
 *
 * Derived classes must implement specific behavior for player
 * management and formation rules.
 */
class Team {
public:
    /**
     * Represents statistical performance of a team.
     */
    struct Statistics {
        unsigned winsCount = 0;
        unsigned drawsCount = 0;
        unsigned lossesCount = 0;
        unsigned scoredGoals = 0;
        unsigned concededGoals = 0;

        /**
         * Initializes all statistics to zero.
         */
        Statistics();

        /**
         * Increases the number of wins by a given value.
         */
        void increaseWinsCount(unsigned wins);

        /**
         * Increases the number of draws by a given value.
         */
        void increaseDrawsCount(unsigned draws);

        /**
         * Increases the number of losses by a given value.
         */
        void increaseLossesCount(unsigned losses);

        /**
         * Increases the number of goals scored.
         */
        void increaseScoredGoals(unsigned scoredGoals);

        /**
         * Increases the number of goals conceded.
         */
        void increaseConcededGoals(unsigned concededGoals);

        friend std::ostream& operator<<(std::ostream& os, const Statistics& stats) {
         os << stats.concededGoals << ' '
            << stats.scoredGoals << ' '
            << stats.drawsCount << ' '
            << stats.winsCount << ' '
            << stats.lossesCount;

         return os;
        }
        friend std::istream& operator>>(std::istream& is, Statistics& stats) {
           unsigned concededGoals, scoredGoals, drawsCount, winsCount, lossesCount;
           is >> concededGoals >> scoredGoals >> drawsCount >> winsCount >> lossesCount;

           stats.concededGoals = concededGoals;
           stats.scoredGoals = scoredGoals;
           stats.drawsCount = drawsCount;
           stats.winsCount = winsCount;
           stats.lossesCount = lossesCount;

           return is;
        }
    };

    /**
     * Maximum number of players allowed in a team.
     */
    static constexpr unsigned MAX_TEAM_SIZE = 20;

protected:
    TeamType type = TeamType::UNKNOWN;
    std::string name = std::string();
    std::string stadiumName = std::string();

    /**
     * Collection of players belonging to the team.
     *
     * Team owns these Player pointers and is responsible for deleting them.
     */
    std::vector<Player> players = std::vector<Player>();

    double budget = 0.0;
    Statistics stats = Statistics();

    /**
     * Pointer to the manager responsible for this team.
     *
     * Non-owning reference.
     */
    TeamManager* teamManager = nullptr;

    unsigned forwardersCount = 0;
    unsigned midfieldersCount = 0;
    unsigned goalkeepersCount = 0;
    unsigned defendersCount = 0;
    unsigned wingersCount = 0;

    /**
     * Copies all data from another team (deep copy).
     *
     * @param other The team to copy from.
     */
    void copy(const Team& other);

    /**
     * Releases all dynamically allocated resources.
     */
    void destroy();

public:
    /**
     * Default constructor.
     */
    Team();

    /**
     * Constructs a team with basic information.
     *
     * @param name The team name.
     * @param coachName The coach name.
     * @param stadiumName The stadium name.
     * @param budget The initial budget.
     */
    Team(TeamType type,
         const std::string& name,
         const std::string& coachName,
         std::string stadiumName,
         double budget);

    /**
     * Copy constructor.
     *
     * Performs a deep copy of all team resources.
     */
    Team(const Team& other);

    /**
     * Copy assignment operator.
     */
    Team& operator=(const Team& other);

    /**
     * Virtual destructor.
     *
     * Ensures proper cleanup of derived classes.
     */
    virtual ~Team() noexcept;

    /**
     * Creates a polymorphic copy of the team.
     *
     * @return Pointer to a newly allocated copy of the team.
     *
     * @note Caller is responsible for deleting the returned object.
     */
    [[nodiscard]] virtual Team* clone() const = 0;

    /**
     * Sets the team name.
     *
     * @param name New team name.
     */
    void setTeamName(const std::string& name);

    /**
     * Sets the stadium name.
     *
     * @param stadiumName New stadium name.
     */
    void setStadiumName(const std::string& stadiumName);

    /**
     * Sets the team budget.
     *
     * @param budget New budget value.
     */
    void setBudget(double budget);

    /**
     * Gets the team name.
     *
     * @return Constant reference to the team name.
     */
    [[nodiscard]] const std::string& getName() const;

    /**
     * Gets the coach name.
     *
     * @return Constant reference to the coach name.
     */
    [[nodiscard]] const std::string& getCoachName() const;

    /**
     * Gets the stadium name.
     *
     * @return Constant reference to the stadium name.
     */
    [[nodiscard]] const std::string& getStadiumName() const;

    /**
     * Gets all players in the team.
     *
     * @return Constant reference to the player list.
     */
    [[nodiscard]] const std::vector<Player>& getPlayers() const;

    /**
     * Gets the current budget of the team.
     *
     * @return Team budget.
     */
    [[nodiscard]] double getBudget() const;

    /**
     * Gets mutable access to team statistics.
     *
     * @return Reference to team statistics.
     */
    [[nodiscard]] Statistics& getStats();

    /**
     * Adds a player to the team (team-type specific rules apply).
     *
     * @param player Player to add.
     * @param isTransfer True if added via transfer, false otherwise.
     */
    virtual void addPlayer(Player& player, bool isTransfer) = 0;

    /**
     * Buys a player for the team.
     *
     * @param player Player to buy.
     * @param playerPos Player position.
     * @param remainingBudget Current available budget.
     * @param isTransfer Whether this operation is part of a transfer.
     */
    void buyPlayer(Player& player,
                   Player::Position playerPos,
                   double remainingBudget,
                   bool isTransfer);

    /**
     * Removes a player from the team.
     *
     * @param playerName Name of the player to remove.
     *
     * @throws std::invalid_argument If player is not found.
     */
    void removePlayer(const std::string& playerName);

 friend std::ostream& operator<<(std::ostream& os, const Team& team)
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
 friend std::istream& operator>>(std::istream& is, Team& team)
 {
  std::string typeStr;
  std::string name;
  std::string stadium;

  double budget;
  Statistics stats;

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
};

#endif //TEAM_H