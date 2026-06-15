//
// Created by User on 5/14/2026.
//

#ifndef MATCH_H
#define MATCH_H

#include "lineup/Lineup.h"

/**
*
*/
class Match final {
public:
    struct MatchResult {
        Team* home;
        Team* guest;
        unsigned homeGoals;
        unsigned guestGoals;

        struct Scorer {
            Player* player;
            bool isHome;
        };

        std::vector<Scorer*> goals;
    };
private:
    Team* host;
    Team* guest;

    Lineup hostLineup;
    Lineup guestLineup;

    unsigned hostGoals;
    unsigned guestGoals;

    unsigned roundNumber;

    MatchResult matchResult;
    bool finished;

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

    void setHost(Team* host);

    void setGuest(Team* guest);

    void addGoal(Player* scorer, bool isHostPlayer);

    [[nodiscard]] bool isFinished() const;

    static unsigned calculateAttackStrength(const Lineup& lineup);

    static unsigned calculateDefenseStrength(const Lineup& lineup);

    static Player *chooseScorer(const std::vector<Player *> &players);

    MatchResult play();
};

#endif //MATCH_H