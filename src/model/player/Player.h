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
        UNKNOWN, ///< Undefined player position.
        GOALKEEPER, ///< Goalkeeper position.
        DEFENDER, ///< Defender position.
        MIDFIELDER, ///< Midfielder position.
        WINGER, ///< Winger position.
        FORWARD, ///< Forward position.
        COUNT ///< Total number of supported positions.
    };

    /**
     * Represents a player's statistical information.
     */
    struct Statistics {
        unsigned matchesCount; ///< Total number of matches played.
        unsigned scoredGoals; ///< Total number of goals scored.

        /**
         * Constructs a statistics object with all values initialized to zero.
         *
         * @param matchesCount Initial number of matches played (default 0).
         * @param scoredGoals Initial number of goals scored (default 0).
         */
        explicit Statistics(unsigned matchesCount = 0, unsigned scoredGoals = 0);

        /**
         * Increases the number of matches played by one.
         */
        void increaseMatchesCount();

        /**
         * Increases the number of goals scored by one.
         */
        void increaseScoredGoals();

        /**
         * Outputs player statistics to a stream in a formatted representation.
         *
         * @param os The output stream.
         * @param stats The statistics object to output.
         * @return Reference to the output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const Statistics &stats);

        /**
         * Reads player statistics from a stream.
         *
         * @param is The input stream.
         * @param stats The statistics object to populate.
         * @return Reference to the input stream.
         */
        friend std::istream &operator>>(std::istream &is, Statistics &stats);
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
    * Default constructor of Player class.
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
    Player(const std::string &name,
           unsigned number,
           Position position,
           double salary,
           double transferSum);

    Player(const std::string &name,
           unsigned number,
           Position position,
           double salary,
           double transferSum,
           Statistics stats);

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
     * Gets the player's name.
     *
     * @return Constant reference to the player's name.
     */
    [[nodiscard]] const std::string &getName() const;

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
    [[nodiscard]] const Statistics &getStats() const;

    /**
     * Provides mutable access to the player's statistics.
     *
     * @return Reference to the player's statistics.
     */
    [[nodiscard]] Statistics &getStats();

    /**
     * Outputs the player information to a stream in a formatted representation.
     *
     * @param os The output stream.
     * @param player The player to output.
     * @return Reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Player &player);

    /**
     * Reads player information from a stream.
     *
     * @param is The input stream.
     * @param player The player to populate.
     * @return Reference to the input stream.
     */
    friend std::istream &operator>>(std::istream &is, Player &player);
};

#endif //PLAYER_H
