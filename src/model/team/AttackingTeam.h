//
// Created by User on 5/14/2026.
//

#ifndef ATTACKINGTEAM_H
#define ATTACKINGTEAM_H

#include "Team.h"
#include "../player/Player.h"

/**
 * Represents a team with an attacking play style.
 *
 * Attacking teams prioritize offensive gameplay and typically
 * enforce stricter requirements on forward players and goal scoring.
 */
class AttackingTeam final : public Team {
public:
    /**
     * Minimum number of goals required from forwards in evaluation logic.
     */
    static constexpr unsigned FORWARD_MIN_SCORED_GOALS = 6;

    /**
     * Required number of goalkeepers in the team.
     */
    static constexpr unsigned REQUIRED_GOALKEEPERS = 2;

    /**
     * Minimum number of forward players required in the team.
     */
    static constexpr unsigned MIN_FORWARDERS_REQUIRED = 8;

    /**
     * Minimum number of defenders required in the team.
     */
    static constexpr unsigned MIN_DEFENDERS_REQUIRED = 2;

    /**
     * Minimum number of midfielders required in the team.
     */
    static constexpr unsigned MIN_MIDFIELDERS_REQUIRED = 2;

    /**
     * Minimum number of wingers required in the team.
     */
    static constexpr unsigned MIN_WINGERS_REQUIRED = 2;

    /**
     * Default constructor.
     *
     * Creates an empty attacking team with default values.
     */
    AttackingTeam();

    /**
     * Constructs an attacking team with full details.
     *
     * @param name The name of the team.
     * @param coachName The name of the team's coach.
     * @param stadiumName The name of the home stadium.
     * @param budget The initial budget of the team.
     */
    AttackingTeam(const std::string& name,
                  const std::string& coachName,
                  const std::string& stadiumName,
                  double budget);

    /**
     * Copy constructor.
     *
     * @param other The attacking team to copy.
     */
    AttackingTeam(const AttackingTeam& other);

    /**
     * Copy assignment operator.
     */
    AttackingTeam& operator=(const AttackingTeam& other) = default;

    /**
     * Virtual destructor.
     */
    ~AttackingTeam() noexcept override = default;

    /**
     * Creates a polymorphic copy of the team.
     *
     * @return Pointer to a newly allocated copy of this team.
     *
     * @note Caller is responsible for deleting the returned object.
     */
    [[nodiscard]] Team* clone() const override;

    /**
     * Adds a player to the team.
     *
     * This method applies attacking-team-specific rules when adding
     * players, such as enforcing positional constraints or budget limits.
     *
     * @param player The player to add.
     * @param isTransfer Indicates whether the player is being added via transfer.
     */
    void addPlayer(Player& player, bool isTransfer) override;
 friend std::ostream& operator<<(std::ostream& os, const AttackingTeam& team)
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
 friend std::istream& operator>>(std::istream& is, AttackingTeam& team)
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

#endif //ATTACKINGTEAM_H