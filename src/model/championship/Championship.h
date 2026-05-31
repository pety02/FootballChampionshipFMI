//
// Created by User on 5/14/2026.
//

#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include "../match/Match.h"
#include "../team/manager/TeamManager.h"
#include <vector>

#include "../../championship/accountingManager/AccountingManager.h"

/**
 * A class that describes a championship.
 */
class Championship final {
private:
    TeamManager teamManager;
    AccountingManager accountingManager;
    std::vector<Match> matches;
    unsigned currentRoundNumber;
    unsigned year;
    bool finished;

public:
    /**
    * A constructor with parameters of the Championship class.
    * Before to create the championship it validates the passed parameters' values.
    * @param teamManager the team manager of the championship
    * @param matches the matches of the championship
    */
    explicit Championship(const TeamManager &teamManager, const std::vector<Match> &matches);

    /**
    * The default destructor of the championship.
    */
    ~Championship() = default;

    /**
    * Validates the next round number and if it is valid, the methods increases the
    * current round number. If not - the method throws an exception.
    */
    void increaseRoundNumber();

    /**
     * Returns the team manager.
     * @return a const reference to the current championship's team manager.
     */
    [[nodiscard]] const TeamManager &getTeamManager() const;

    /**
     * Returns a vector of the matches.
     * @return a const reference to the current championship's matches' vector.
     */
    [[nodiscard]] const std::vector<Match> &getMatches() const;

    /**
     * @return the current round number.
     */
    [[nodiscard]] unsigned getCurrentRoundNumber() const;

    /**
     * @return if the current championship is finished or not on the basis of
     * if all its matches are finished.
     */
    [[nodiscard]] bool isFinished() const;

    /**
    * @return the year of the current championship - a number between 1900
    * and the current year.
    */
    [[nodiscard]] unsigned getYear() const;

    /**
     * Adds the passed match to the matches' vector if this will not break the rules
     * for the matches count in a definite championship.
     * @param match - the passed match that should be added in the vector.
     */
    void addMatch(const Match &match);

    /**
    * Sets `finished` status to the current championship when all its matches are finished.
    */
    void finish();
};

#endif //CHAMPIONSHIP_H