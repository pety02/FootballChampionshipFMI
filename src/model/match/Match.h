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
        Team* home = nullptr;
        Team* guest = nullptr;
        unsigned homeGoals = 0;
        unsigned guestGoals = 0;

        struct Scorer {
            Player* player = nullptr;
            bool isHome = false;

            explicit Scorer(Player* player = nullptr, bool isHome = false) : player(player), isHome(isHome) {}
        };

        std::vector<Scorer*> goals = std::vector<Scorer*>();

        explicit MatchResult(Team* home = nullptr, Team* guest = nullptr, unsigned homeGoals = 0,
            unsigned guestGoals = 0, const std::vector<Scorer*>& goals = std::vector<Scorer*>())
        : home(home), guest(guest), homeGoals(homeGoals), guestGoals(guestGoals), goals(goals) {};
    };
private:
    Team* host = nullptr;
    Team* guest = nullptr;

    Lineup hostLineup = Lineup(nullptr);
    Lineup guestLineup = Lineup(nullptr);

    unsigned hostGoals = 0;
    unsigned guestGoals = 0;

    unsigned roundNumber = 0;

    MatchResult matchResult = MatchResult();
    bool finished = false;

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
    [[nodiscard]] std::vector<Player*> getScorers() const;

    void setHost(Team* host);

    void setGuest(Team* guest);

    void setHostLineup(const Lineup& hostLineup);

    void setGuestLineup(const Lineup& guestLineup);

    void addGoal(Player* scorer, bool isHostPlayer);

    [[nodiscard]] bool isFinished() const;

    void clearLineups();

    static unsigned calculateAttackStrength(const Lineup& lineup);

    static unsigned calculateDefenseStrength(const Lineup& lineup);

    static Player *chooseScorer(const std::vector<Player *> &players);

    [[nodiscard]] MatchResult play() const;
};

#endif //MATCH_H