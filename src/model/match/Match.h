//
// Created by User on 5/14/2026.
//

#ifndef MATCH_H
#define MATCH_H

#include "lineup/Lineup.h"

/**
* A class that represents a football match.
*/
class Match final {
public:
    /**
    * A class that represents a football match result. It contains pointers to the home and guest teams, their scored
    * goals and which goal from whom is scored (a pointer to the scorer player).
    */
    struct MatchResult {
        Team* home = nullptr;
        Team* guest = nullptr;
        unsigned homeGoals = 0;
        unsigned guestGoals = 0;

        /**
        * A struct that represents the scorer as a struct that contains a pointer to a definite player
        * and a flag for his/her state - if he/she is a home player or a guest player.
        */
        struct Scorer {
            Player* player = nullptr;
            bool isHome = false;

            /**
            * Default constructor, constructor with one param (player or his/her flag) and all args constructor at once.
            */
            explicit Scorer(Player* player = nullptr, bool isHome = false) : player(player), isHome(isHome) {}
        };

        std::vector<Scorer*> goals = std::vector<Scorer*>();

        /**
        * All variant of constructor at once.
        */
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
    /**
    * Constructs a match object with its lineups.
    */
    Match(const Lineup& hostLineup, const Lineup& guestLineup);

    /**
    * Constructs a match object as a copy of an already existing match.
    */
    Match(const Match& other);

    /**
    * Assigns another already existing match object to the current match.
    */
    Match& operator=(const Match& other);

    /**
    * Destructs the current match object.
    */
    ~Match();

        /**
     * Increases the current round number of the match by one.
     */
    void increaseRoundNumber();

    /**
     * Gets the home (host) team participating in the match.
     *
     * @return Pointer to the host team.
     */
    [[nodiscard]] Team* getHost() const;

    /**
     * Gets the guest (away) team participating in the match.
     *
     * @return Pointer to the guest team.
     */
    [[nodiscard]] Team* getGuest() const;

    /**
     * Gets the lineup selected for the host team.
     *
     * @return Constant reference to the host lineup.
     */
    [[nodiscard]] const Lineup& getHostLineup() const;

    /**
     * Gets the lineup selected for the guest team.
     *
     * @return Constant reference to the guest lineup.
     */
    [[nodiscard]] const Lineup& getGuestLineup() const;

    /**
     * Gets the number of goals scored by the host team.
     *
     * @return The host team's goal count.
     */
    [[nodiscard]] unsigned getHostGoals() const;

    /**
     * Gets the number of goals scored by the guest team.
     *
     * @return The guest team's goal count.
     */
    [[nodiscard]] unsigned getGuestGoals() const;

    /**
     * Gets the current round number of the match.
     *
     * @return The round number.
     */
    [[nodiscard]] unsigned getRoundNumber() const;

    /**
     * Retrieves all players who scored during the match.
     *
     * @return A vector containing pointers to the scoring players.
     */
    [[nodiscard]] std::vector<Player*> getScorers() const;

    /**
     * Sets the host team participating in the match.
     *
     * @param host Pointer to the new host team.
     */
    void setHost(Team* host);

    /**
     * Sets the guest team participating in the match.
     *
     * @param guest Pointer to the new guest team.
     */
    void setGuest(Team* guest);

    /**
     * Replaces the current host lineup.
     *
     * @param hostLineup The lineup to assign to the host team.
     */
    void setHostLineup(const Lineup& hostLineup);

    /**
     * Replaces the current guest lineup.
     *
     * @param guestLineup The lineup to assign to the guest team.
     */
    void setGuestLineup(const Lineup& guestLineup);

    /**
     * Registers a goal scored during the match.
     *
     * Updates the corresponding team's goal count and records
     * the player responsible for the goal.
     *
     * @param scorer Pointer to the player who scored.
     * @param isHostPlayer True if the scorer belongs to the host team;
     *                     false if the scorer belongs to the guest team.
     */
    void addGoal(Player* scorer, bool isHostPlayer);

    /**
     * Checks whether the match has been completed.
     *
     * @return True if the match is finished; otherwise false.
     */
    [[nodiscard]] bool isFinished() const;

    /**
     * Removes all players from both lineups associated with this match.
     */
    void clearLineups();

    /**
     * Calculates the attacking strength of a lineup.
     *
     * The exact formula depends on the implementation and may
     * take into account player positions, ratings, or statistics.
     *
     * @param lineup The lineup whose attacking strength is evaluated.
     * @return The calculated attack strength value.
     */
    static unsigned calculateAttackStrength(const Lineup& lineup);

    /**
     * Calculates the defensive strength of a lineup.
     *
     * The exact formula depends on the implementation and may
     * take into account player positions, ratings, or statistics.
     *
     * @param lineup The lineup whose defensive strength is evaluated.
     * @return The calculated defense strength value.
     */
    static unsigned calculateDefenseStrength(const Lineup& lineup);

    /**
     * Randomly selects a scorer from a collection of eligible players.
     *
     * @param players Vector containing pointers to potential scorers.
     * @return Pointer to the selected player, or nullptr if the vector is empty.
     */
    static Player* chooseScorer(const std::vector<Player*>& players);

    /**
     * Simulates the match and generates the final result.
     *
     * The simulation determines the number of goals scored by each team
     * and records the players responsible for those goals.
     *
     * @return A MatchResult object describing the outcome of the match.
     */
    [[nodiscard]] MatchResult play() const;
};

#endif //MATCH_H