#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include "../match/Match.h"
#include "../team/manager/TeamManager.h"
#include <vector>
#include "accountingManager/AccountingManager.h"

/**
* A class that represents the football championship.
*/
class Championship final {
private:
    TeamManager teamManager = TeamManager();
    AccountingManager accountingManager = AccountingManager();
    std::vector<Match> matches = std::vector<Match>();
    unsigned currentRoundNumber = 0;
    unsigned year = 0;
    bool finished = false;

public:
    /**
    * Default constructor of the Championship class.
    */
    Championship() = default;

    /**
    * Constructor that initializes the team manager of the championship and sets the matches in it.
    *
    * @param teamManager the team manager responsible for all the teams in the championship.
    * @param matches the matches that are played in this football championship.
    * @param year the year of the current championship.
    * @param accountingManager the accounting manager of the current championship.
    */
    Championship(const TeamManager &teamManager,
                 const std::vector<Match> &matches,
                 int year,
                 const AccountingManager& accountingManager);

    Championship(const TeamManager &teamManager,
                 const std::vector<Match> &matches,
                 int year,
                 const AccountingManager& accountingManager,
                 unsigned currentRoundNumber, bool finished);

    /**
    * Increases the round number of the current championship.
    */
    void increaseRoundNumber();

    /**
    * @return the team manager of the current championship as a reference.
    */
    [[nodiscard]] TeamManager& getTeamManager();

    /**
    * @return the team manager of the current championship as a const reference.
    */
    [[nodiscard]] const TeamManager &getTeamManager() const;

    /**
    * @return the matches of the current championship as a const reference to a vector of Match objects.
    */
    [[nodiscard]] const std::vector<Match> &getMatches() const;

    /**
    * @return the matches of the current championship as a reference to a vector of Match objects.
    */
    [[nodiscard]] std::vector<Match> &getMatches();

    /**
    * @return the round number of the current championship.
    */
    [[nodiscard]] unsigned getCurrentRoundNumber() const;

    /**
    * Adds a definite match to the matches of the championship.
    *
    * @param match the match that should be added in the current championship.
    */
    void addMatch(const Match &match);

    /**
    * Finishes the current championship.
    */
    void finish();

    /**
    * Sets a definite teamManager to the current championship.
    *
    * @param teamManager the team manager of the current championship.
    */
    void setTeamManager(const TeamManager &teamManager);

    /**
    * Operator that writes the championship in a binary file.
    *
    * @param os the stream of writing.
    * @param championship the championship that should be stored in the binary file.
    *
    * @return the stream of writing.
    */
    friend std::ostream& operator<<(std::ostream& os, const Championship& championship);

    /**
    * Operator that reads the championship from a binary file.
    *
    * @param is the stream of reading.
    * @param championship the championship that should be inited with the read data.
    *
    * @return the stream of reading.
    */
    friend std::istream& operator>>(std::istream& is, Championship& championship);
};

#endif