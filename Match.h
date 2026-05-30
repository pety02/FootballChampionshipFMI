//
// Created by User on 5/14/2026.
//

#ifndef MATCH_H
#define MATCH_H

#include "Lineup.h"

/**
*
*/
class Match final {
public:
    struct Goal {
        Player* scorer;
        bool hostGoal;
    };
private:
    Team* host;
    Team* guest;

    Lineup hostLineup;
    Lineup guestLineup;

    unsigned hostGoals;
    unsigned guestGoals;

    unsigned roundNumber;

    std::vector<Goal> goals;

public:
    Match(const Lineup& hostLineup, const Lineup& guestLineup);
    Match(const Match& other);
    Match& operator=(const Match& other);
    ~Match();

    void increaseRoundNumber();

    /**
    *
    */
    [[nodiscard]] Team* getHost() const;

    /**
    *
    */
    [[nodiscard]] Team* getGuest() const;

    /**
    *
    */
    [[nodiscard]] const Lineup& getHostLineup() const;

    /**
    *
    */
    [[nodiscard]] const Lineup& getGuestLineup() const;

    /**
    *
    */
    [[nodiscard]] unsigned getHostGoals() const;

    /**
    *
    */
    [[nodiscard]] unsigned getGuestGoals() const;

    /**
    *
    */
    [[nodiscard]] unsigned getRoundNumber() const;

    /**
    *
    */
    [[nodiscard]] const std::vector<Player*> getScorers() const;
};

#endif //MATCH_H