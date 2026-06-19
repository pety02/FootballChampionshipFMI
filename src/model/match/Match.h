#ifndef MATCH_H
#define MATCH_H

#include "lineup/Lineup.h"
#include <vector>
#include <ostream>
#include <istream>

class Match final {
public:

    struct MatchResult {
        Team* home = nullptr;
        Team* guest = nullptr;
        unsigned homeGoals = 0;
        unsigned guestGoals = 0;

        struct Scorer {
            Player player;
            bool isHome;

            explicit Scorer(Player player = Player(), bool isHome = false);

            friend std::ostream& operator<<(std::ostream& os, const Scorer& scorer);
            friend std::istream& operator>>(std::istream& is, Scorer& scorer);
        };

        std::vector<Scorer*> goals;

        MatchResult() = default;

        ~MatchResult();
        MatchResult(const MatchResult& other);
        MatchResult& operator=(const MatchResult& other);

        friend std::ostream& operator<<(std::ostream& os, const MatchResult& mr);
        friend std::istream& operator>>(std::istream& is, MatchResult& mr);
    };

private:
    Team* host = nullptr;
    Team* guest = nullptr;

    Lineup hostLineup;
    Lineup guestLineup;

    unsigned hostGoals = 0;
    unsigned guestGoals = 0;
    unsigned roundNumber = 0;

    MatchResult matchResult;
    bool finished = false;

public:
    Match();
    Match(const Lineup& hostLineup, const Lineup& guestLineup);

    Match(const Match& other);
    Match& operator=(const Match& other);

    ~Match();

    void increaseRoundNumber();

    [[nodiscard]] Team* getHost() const;
    [[nodiscard]] Team* getGuest() const;

    [[nodiscard]] const Lineup& getHostLineup() const;
    [[nodiscard]] const Lineup& getGuestLineup() const;

    [[nodiscard]] unsigned getHostGoals() const;
    [[nodiscard]] unsigned getGuestGoals() const;
    [[nodiscard]] unsigned getRoundNumber() const;

    [[nodiscard]] std::vector<Player> getScorers() const;

    void setHost(Team* host);
    void setGuest(Team* guest);

    void setHostLineup(const Lineup& hostLineup);
    void setGuestLineup(const Lineup& guestLineup);

    void addGoal(Player scorer, bool isHostPlayer);

    [[nodiscard]] bool isFinished() const;

    void clearLineups();

    static unsigned calculateAttackStrength(const Lineup& lineup);
    static unsigned calculateDefenseStrength(const Lineup& lineup);
    static Player chooseScorer(const std::vector<Player>& players);

    [[nodiscard]] MatchResult play() const;

    friend std::ostream& operator<<(std::ostream& os, const Match& match);
    friend std::istream& operator>>(std::istream& is, Match& match);
};

#endif