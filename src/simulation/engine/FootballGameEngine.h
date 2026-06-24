#ifndef FOOTBALLGAMEENGINE_H
#define FOOTBALLGAMEENGINE_H

#include <string>

#include "../../model/championship/history/ChampionshipHistory.h"
#include "../../model/match/Match.h"
#include "../../model/player/Player.h"

/**
 * Core simulation engine for running football championships.
 *
 * This class is responsible for:
 * - Creating and managing a championship lifecycle
 * - Simulating matches
 * - Tracking results and statistics
 * - Determining final rankings (champion, vice-champion, etc.)
 */
class FootballGameEngine {
private:
    ChampionshipHistory championshipHistory = ChampionshipHistory();
    Championship currentChampionship = Championship();

    std::string champion = std::string();
    std::string viceChampion = std::string();
    std::string bronzeTeam = std::string();
    std::string goalMaster = std::string();

    /**
     * Retrieves the list of championship winners across history.
     *
     * @return Vector of champion team names.
     */
    [[nodiscard]] std::vector<std::string> getChampions() const;

public:
    /**
     * Default constructor.
     */
    FootballGameEngine();

    /**
     * Determines the player with the highest number of goals
     * across the championship.
     *
     * @return Name of the top scorer.
     */
    std::string findGoalMaster();

    /**
     * Initializes and creates a new championship.
     *
     * Allocates and prepares all required data structures for simulation.
     */
    void simulate();

    /**
     * Adds a match to the current championship.
     *
     * @param match Match to be added.
     * @param championship the current championship.
     *
     * @throws std::invalid_argument If no championship is active.
     */
    static void addMatch(const Match &match, Championship &championship);

    /**
     * Advances the championship to the next round.
     */
    //void updateChampionshipRound();

    /**
     * Finalizes the current championship and computes final rankings.
     */
    void finishChampionship();

    /**
     * Simulates a single match.
     *
     * @param match Pointer to the match to simulate.
     * @param championship the current championship.
     */
    static void play(Match &match, const Championship& championship);

    /**
     * Records a goal scored by a player in a match.
     *
     * @param player Pointer to the scoring player.
     * @param match Reference to the match where the goal occurred.
     */
    void addScorer(const Player &player, Match &match) const;

    /**
     * Increments the home team's goal count in a match.
     *
     * @param match The match to update.
     */
    static void increaseHostGoals(const Match &match);

    /**
     * Increments the guest team's goal count in a match.
     *
     * @param match The match to update.
     */
    static void increaseGuestGoals(const Match &match);

    /**
     * Marks a match as finished and finalizes its result.
     *
     * @param match Match to finalize.
     */
    void finishMatch(Match &match);

    /**
     * Gets the currently active championship.
     *
     * @return Constant reference to the championship.
     */
    [[nodiscard]] const Championship &getCurrentChampionship() const;

    /**
   * Returns all past championships stored in history.
   *
   * @param championshipHistory Championship history container.
   * @return Vector of all championships.
   */
    static std::vector<Championship> listSeasons(const ChampionshipHistory &championshipHistory);

    /**
    * Simulates all matches in a championship using a temporary engine instance.
    *
    * @param championship Championship to simulate.
    */
    static void playAllMatches(Championship &championship); // used in the simulation of the season

    /**
    * Displays the champion team of a championship.
    *
    * @param championship The championship to analyze.
    */
    static void showPodium(const Championship &championship);

    /**
    * Simulates a season, simulates all matches, and stores results in history.
    *
    * @param history Championship history.
    * @param championship Championship to finalize.
    */
    static void simulateSeason(ChampionshipHistory &history,
                             Championship &championship);

    /**
    * Displays all matches in a championship.
    *
    * @param championship The championship to display.
    */
    static void viewMatches(const Championship &championship);

    /**
    * Interactive input function for entering match results manually.
    *
    * @param match The match to populate with results.
    */
    static void enterMatchResult(const Match &match);

    /**
    * Returns all teams in the given championship.
    *
    * @param championship The championship instance.
    * @return Vector of team pointers.
    */
    static std::vector<Team *> listTeams(Championship &championship);

    /**
    * Adds a new team to a championship using provided arguments.
    *
    * @param args Command-line style arguments describing the team.
    * @param championship The championship to modify.
    */
    static void addTeam(const std::vector<std::string> &args,
                        Championship &championship);

    /**
    * Removes a team from a championship.
    *
    * @param teamName Name of the team to remove.
    * @param championship The championship to modify.
    */
    static void removeTeam(const std::string &teamName,
                           Championship &championship);

    /**
    * Automatically generates and assigns lineups for a match.
    *
    * @param match The match to configure.
    */
    //static void autoSelectLineups(Match &match, Team *host, Team *guest);

    /**
    * Clears the lineups of a match.
    *
    * @param match The match whose lineups are cleared.
    */
    static void deleteLineups(Match &match);

    /**
    * Returns a list of players considered top scorers (currently unfiltered).
    *
    * @param team The team to analyze.
    * @return Vector of players.
    */
    static std::vector<Player> listTopScorers(const Team &team);

    /**
    * Simulates a single goal event interactively.
    *
    * @param match The match in which the goal occurs.
    */
    static void simulateGoal(const Match &match);

    /**
 * Assigns a team manager to a team and registers it in the manager.
 *
 * @param team The team to assign.
 * @param teamManager The manager managing the team.
 */
    static void addManager(Team *team, TeamManager &teamManager);
};

#endif // FOOTBALLGAMEENGINE_H
