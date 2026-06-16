//
// Created by User on 5/14/2026.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

/**
*
*/
class Player final {
public:
    /**
    *
    */
    enum class Position {
        UNKNOWN, GOALKEEPER, DEFENDER, MIDFIELDER, WINGER, FORWARD, COUNT
    };

    /**
    *
    */
    struct Statistics {
        unsigned matchesCount;
        unsigned scoredGoals;

        Statistics();

        /**
        *
        */
        void increaseMatchesCount();

        /**
        *
        */
        void increaseScoredGoals();
    };

private:
    std::string name = std::string();
    unsigned number = 0;
    Position position = Position::UNKNOWN;
    double salary = 0.0;
    double transferSum = 0.0;
    Statistics stats = Statistics();

public:
    Player(const std::string& name, unsigned number, Position position, double salary, double transferSum);
    Player(const Player& other);
    Player& operator=(const Player& other) = delete;
    Player(Player&& other) = delete;
    Player& operator=(Player&& other) = delete;
    ~Player() noexcept = default;

    /**
    *
    */
    void setNumber(unsigned number);

    /**
    *
    */
    void setPosition(Position position);

    /**
    *
    */
    void setSalary(double salary);

    /**
    *
    */
    void setTransferSum(double transferSum);

    /**
    *
    */
    [[nodiscard]] const std::string& getName() const;

    /**
    *
    */
    [[nodiscard]] unsigned getNumber() const;

    /**
    *
    */
    [[nodiscard]] Position getPosition() const;

    /**
    *
    */
    [[nodiscard]] double getSalary() const;

    /**
    *
    */
    [[nodiscard]] double getTransferSum() const;

    /**
    *
    */
    [[nodiscard]] const Statistics& getStats() const;
    [[nodiscard]] Statistics& getStats();
};
#endif //PLAYER_H