#ifndef MATCH_H
#define MATCH_H

#include "lineup/Lineup.h"
#include <vector>

/**
* A class representing a football match between two teams, including lineups,
* scoring events, and match progression state.
*/
class Match final {
public:

    /**
    * Represents the final result and events of a match.
    */
    struct MatchResult final {
        Team* home = nullptr;
        Team* guest = nullptr;
        unsigned homeGoals = 0;
        unsigned guestGoals = 0;

        /**
        * Represents a single goal-scoring event in the match.
        */
        struct Scorer final {
            Player player;
            bool isHome;

            /**
            * Constructs a scorer event for a given player.
            *
            * @param player The player who scored the goal.
            * @param isHome Indicates whether the goal was scored by the home team.
            */
            explicit Scorer(const Player &player = Player(), bool isHome = false);

            /**
            * Outputs the scorer information to a stream.
            *
            * @param os The output stream.
            * @param scorer The scorer event to output.
            * @return Reference to the output stream.
            */
            friend std::ostream& operator<<(std::ostream& os, const Scorer& scorer);

            /**
            * Reads scorer information from a stream.
            *
            * @param is The input stream.
            * @param scorer The scorer event to populate.
            * @return Reference to the input stream.
            */
            friend std::istream& operator>>(std::istream& is, Scorer& scorer);
        };

        std::vector<Scorer*> goals;

        /**
        * Default constructor. Initializes an empty match result.
        */
        MatchResult() = default;

        MatchResult(MatchResult&& other) noexcept;
        MatchResult& operator=(MatchResult&& other) noexcept;

        /**
        * Destructor. Cleans up dynamically allocated scorer events.
        */
        ~MatchResult() noexcept;

        /**
        * Copy constructor. Performs a deep copy of the match result, including goals.
        *
        * @param other The match result to copy from.
        */
        MatchResult(const MatchResult& other);

        /**
        * Copy assignment operator. Copies match result data from another instance.
        *
        * @param other The match result to copy from.
        * @return Reference to this match result.
        */
        MatchResult& operator=(const MatchResult& other);

        /**
        * Outputs the match result to a stream in a formatted way.
        *
        * @param os The output stream.
        * @param mr The match result to output.
        * @return Reference to the output stream.
        */
        friend std::ostream& operator<<(std::ostream& os, const MatchResult& mr);

        /**
        * Reads match result data from a stream.
        *
        * @param is The input stream.
        * @param mr The match result to populate.
        * @return Reference to the input stream.
        */
        friend std::istream& operator>>(std::istream& is, MatchResult& mr);
    };

private:
    Team* host = nullptr;
    Team* guest = nullptr;

    Lineup hostLineup;
    Lineup guestLineup;

    unsigned hostGoals = 0;
    unsigned guestGoals = 0;
    unsigned roundNumber = 0; // something like halftime in a match

    MatchResult matchResult;
    bool finished = false;

public:
    /**
    * Default constructor. Creates an uninitialized match.
    */
    Match() = default;

    /**
    * Constructs a match using the provided home and away lineups.
    *
    * @param hostLineup The lineup of the home team.
    * @param guestLineup The lineup of the guest team.
    */
    Match(const Lineup& hostLineup, const Lineup& guestLineup);

    /**
    * Copy constructor. Creates a deep copy of the match state.
    *
    * @param other The match to copy from.
    */
    Match(const Match& other);

    /**
    * Copy assignment operator. Copies match state from another match.
    *
    * @param other The match to copy from.
    * @return Reference to this match.
    */
    Match& operator=(const Match& other);

    Match(Match&& other) noexcept;

    Match& operator=(Match&& other) noexcept;

    /**
    * Destructor. Cleans up resources associated with the match.
    */
    ~Match() noexcept;

    /**
    * Advances the match by incrementing the round counter.
    */
    void increaseRoundNumber();

    /**
    * Retrieves the home team.
    *
    * @return Pointer to the home team.
    */
    [[nodiscard]] Team* getHost() const;

    /**
    * Retrieves the guest team.
    *
    * @return Pointer to the guest team.
    */
    [[nodiscard]] Team* getGuest() const;

    /**
    * Retrieves the lineup of the home team.
    *
    * @return Const reference to the home lineup.
    */
    [[nodiscard]] const Lineup& getHostLineup() const;

    /**
    * Retrieves the lineup of the guest team.
    *
    * @return Const reference to the guest lineup.
    */
    [[nodiscard]] const Lineup& getGuestLineup() const;

    /**
    * Retrieves the number of goals scored by the home team.
    *
    * @return Number of home goals.
    */
    [[nodiscard]] unsigned getHostGoals() const;

    /**
    * Retrieves the number of goals scored by the guest team.
    *
    * @return Number of guest goals.
    */
    [[nodiscard]] unsigned getGuestGoals() const;

    /**
    * Retrieves all players who scored in the match.
    *
    * @return Vector of players who scored goals.
    */
    [[nodiscard]] std::vector<Player> getScorers() const;

    /**
    * Sets the home team for the match.
    *
    * @param host Pointer to the home team.
    */
    void setHost(Team* host);

    /**
    * Sets the guest team for the match.
    *
    * @param guest Pointer to the guest team.
    */
    void setGuest(Team* guest);

    /**
    * Sets the lineup for the home team.
    *
    * @param hostLineup The lineup to assign to the home team.
    */
    void setHostLineup(const Lineup& hostLineup);

    /**
    * Sets the lineup for the guest team.
    *
    * @param guestLineup The lineup to assign to the guest team.
    */
    void setGuestLineup(const Lineup& guestLineup);

    /**
    * Records a goal scored by a player and updates match state.
    *
    * @param scorer The player who scored.
    * @param isHostPlayer True if the scorer belongs to the home team.
    */
    void addGoal(Player scorer, bool isHostPlayer);

    /**
    * Checks whether the match has finished.
    *
    * @return true if the match is finished; false otherwise.
    */
    [[nodiscard]] bool isFinished() const;

    /**
    * Clears both team lineups and resets associated match state if needed.
    */
    void clearLineups();

    /**
    * Calculates the attacking strength of a lineup based on its players.
    *
    * @param lineup The lineup to evaluate.
    * @return Numeric attack strength value.
    */
    static unsigned calculateAttackStrength(const Lineup& lineup);

    /**
    * Calculates the defensive strength of a lineup based on its players.
    *
    * @param lineup The lineup to evaluate.
    * @return Numeric defense strength value.
    */
    static unsigned calculateDefenseStrength(const Lineup& lineup);

    /**
    * Selects a player from a list to act as a scorer.
    *
    * @param players The list of eligible players.
    * @return The chosen scoring player.
    */
    static Player chooseScorer(const std::vector<Player>& players);

    void playHalfTime(MatchResult& result);
    /**
    * Simulates and executes the match, producing the final result.
    *
    * @return The final MatchResult after simulation.
    */
    [[nodiscard]] MatchResult play();

    /**
    * Outputs the match details to a stream.
    *
    * @param os The output stream.
    * @param match The match to output.
    * @return Reference to the output stream.
    */
    friend std::ostream& operator<<(std::ostream& os, const Match& match);

    /**
    * Reads match details from a stream.
    *
    * @param is The input stream.
    * @param match The match to populate.
    * @return Reference to the input stream.
    */
    friend std::istream& operator>>(std::istream& is, Match& match);
};

#endif