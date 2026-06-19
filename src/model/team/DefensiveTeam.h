//
// Created by User on 5/14/2026.
//

#ifndef DEFENSIVETEAM_H
#define DEFENSIVETEAM_H

#include "Team.h"
#include "../player/Player.h"
#include <string>

/**
 * Represents a team with a defensive play style.
 *
 * Defensive teams prioritize strong defensive structure and
 * typically allocate more players to defensive and midfield roles
 * while minimizing attacking emphasis.
 */
class DefensiveTeam final : public Team {
public:
    /**
     * Required number of goalkeepers in the team.
     */
    static constexpr unsigned REQUIRED_GOALKEEPERS = 2;

    /**
     * Minimum number of defenders required in the team.
     */
    static constexpr unsigned MIN_DEFENDERS_REQUIRED = 6;

    /**
     * Minimum number of midfielders required in the team.
     */
    static constexpr unsigned MIN_MIDFIELDERS_REQUIRED = 6;

    /**
     * Minimum number of wingers required in the team.
     */
    static constexpr unsigned MIN_WINGERS_REQUIRED = 2;

    /**
     * Minimum number of forward players required in the team.
     */
    static constexpr unsigned MIN_FORWARDERS_REQUIRED = 2;

    /**
     * Default constructor.
     *
     * Creates a defensive team with default configuration.
     */
    DefensiveTeam();

    /**
     * Constructs a defensive team with full configuration.
     *
     * @param name The name of the team.
     * @param coachName The name of the team's coach.
     * @param stadiumName The name of the home stadium.
     * @param budget The initial budget of the team.
     */
    DefensiveTeam(const std::string& name,
                   const std::string& coachName,
                   const std::string& stadiumName,
                   double budget);

    /**
     * Copy constructor.
     *
     * @param other The defensive team to copy.
     */
    DefensiveTeam(const DefensiveTeam& other);

    /**
     * Copy assignment operator.
     *
     * @param other The defensive team to assign from.
     * @return Reference to the current object.
     */
    DefensiveTeam& operator=(const DefensiveTeam& other);

    /**
     * Destructor.
     */
    ~DefensiveTeam() noexcept override = default;

    /**
     * Creates a polymorphic copy of the team.
     *
     * @return Pointer to a newly allocated copy of this team.
     *
     * @note The caller is responsible for deleting the returned object.
     */
    [[nodiscard]] Team* clone() const override;

    /**
     * Adds a player to the team using defensive-team rules.
     *
     * This method enforces constraints that favor defensive structure,
     * ensuring a stronger defensive lineup compared to other team types.
     *
     * @param player The player to add.
     * @param isTransfer Indicates whether the player is added via transfer.
     */
    void addPlayer(Player& player, bool isTransfer) override;
 friend std::ostream& operator<<(std::ostream& os, const DefensiveTeam& team)
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
 friend std::istream& operator>>(std::istream& is, DefensiveTeam& team)
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

#endif //DEFENSIVETEAM_H