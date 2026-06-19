//
// Created by User on 5/14/2026.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <fstream>
#include <string>

/**
 * Represents a football player participating in a team.
 *
 * A player has personal information such as name, squad number,
 * playing position, salary, transfer value, and accumulated
 * career statistics within the simulation.
 */
class Player final {
public:
    /**
     * Enumerates the supported football positions.
     */
    enum class Position {
        UNKNOWN,     ///< Undefined player position.
        GOALKEEPER,  ///< Goalkeeper position.
        DEFENDER,    ///< Defender position.
        MIDFIELDER,  ///< Midfielder position.
        WINGER,      ///< Winger position.
        FORWARD,     ///< Forward position.
        COUNT        ///< Total number of supported positions.
    };

    /**
     * Represents a player's statistical information.
     */
    struct Statistics {
        unsigned matchesCount; ///< Total number of matches played.
        unsigned scoredGoals;  ///< Total number of goals scored.

        /**
         * Constructs a statistics object with all values initialized to zero.
         */
        explicit Statistics(unsigned matchesCount = 0, unsigned scoredGoals = 0)
                    : matchesCount(matchesCount), scoredGoals(scoredGoals) {};

        /**
         * Increases the number of matches played by one.
         */
        void increaseMatchesCount();

        /**
         * Increases the number of goals scored by one.
         */
        void increaseScoredGoals();

        friend std::ostream& operator<<(std::ostream& os, const Statistics& stats) {
           os << stats.matchesCount << "\n" << stats.scoredGoals << "\n";

           return os;
        }
        friend std::istream& operator>>(std::istream& is, Statistics& stats) {
           unsigned matchesCount, scoredGoals;

           is >> matchesCount >> scoredGoals;
           stats = Statistics(matchesCount, scoredGoals);

           return is;
        }
    };

private:
    std::string name = std::string();
    unsigned number = 0;
    Position position = Position::UNKNOWN;
    double salary = 0.0;
    double transferSum = 0.0;
    Statistics stats = Statistics();

public:
    /**
    * Default constructo of Player class.
    */
    Player() = default;
    /**
     * Constructs a player with the specified properties.
     *
     * @param name The player's full name.
     * @param number The player's squad number.
     * @param position The player's field position.
     * @param salary The player's salary.
     * @param transferSum The player's transfer value.
     */
    Player(const std::string& name,
           unsigned number,
           Position position,
           double salary,
           double transferSum);

    /**
     * Constructs a player as a copy of another player.
     *
     * @param other The player to copy.
     */
    Player(const Player& other);

    /**
     * Copy assignment operator.
     */
    Player& operator=(const Player& other);

    /**
     * Destroys the player object.
     */
    ~Player() noexcept = default;

    /**
     * Changes the player's squad number.
     *
     * @param number The new squad number.
     */
    void setNumber(unsigned number);

    /**
     * Changes the player's position.
     *
     * @param position The new playing position.
     */
    void setPosition(Position position);

    /**
     * Changes the player's salary.
     *
     * @param salary The new salary value.
     */
    void setSalary(double salary);

    /**
     * Changes the player's transfer value.
     *
     * @param transferSum The new transfer value.
     */
    void setTransferSum(double transferSum);

    /**
     * Gets the player's name.
     *
     * @return Constant reference to the player's name.
     */
    [[nodiscard]] const std::string& getName() const;

    /**
     * Gets the player's squad number.
     *
     * @return The player's squad number.
     */
    [[nodiscard]] unsigned getNumber() const;

    /**
     * Gets the player's current position.
     *
     * @return The player's playing position.
     */
    [[nodiscard]] Position getPosition() const;

    /**
     * Gets the player's salary.
     *
     * @return The player's salary.
     */
    [[nodiscard]] double getSalary() const;

    /**
     * Gets the player's transfer value.
     *
     * @return The player's transfer value.
     */
    [[nodiscard]] double getTransferSum() const;

    /**
     * Provides read-only access to the player's statistics.
     *
     * @return Constant reference to the player's statistics.
     */
    [[nodiscard]] const Statistics& getStats() const;

    /**
     * Provides mutable access to the player's statistics.
     *
     * @return Reference to the player's statistics.
     */
    [[nodiscard]] Statistics& getStats();

 friend std::ostream& operator<<(std::ostream& os, const Player& player)
 {
  os << player.name << '\n'
     << player.number << '\n'
     << static_cast<int>(player.position) << '\n'
     << player.salary << '\n'
     << player.transferSum << '\n'
     << player.stats << '\n';

  return os;
 }
 friend std::istream& operator>>(std::istream& is, Player& player)
 {
  std::string name;
  unsigned number;
  int pos;
  double salary;
  double transferSum;
  Statistics stats;

  std::getline(is >> std::ws, name);

  is >> number
     >> pos
     >> salary
     >> transferSum
     >> stats;

  player.name = name;
  player.number = number;
  player.setPosition(static_cast<Position>(pos));
  player.salary = salary;
  player.transferSum = transferSum;
  player.stats = stats;

  return is;
 }
};

#endif //PLAYER_H