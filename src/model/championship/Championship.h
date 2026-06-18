//
// Created by User on 5/14/2026.
//

#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include "../match/Match.h"
#include "../team/manager/TeamManager.h"
#include <vector>
#include "accountingManager/AccountingManager.h"

/**
 * A class that describes a championship.
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
    * Default constructor of Championship class.
    */
    Championship() = default;
    explicit Championship(const TeamManager& manager) : teamManager(manager), accountingManager(AccountingManager()) {}
    /**
    * A constructor with parameters of the Championship class.
    * Before to create the championship it validates the passed parameters' values.
    * @param teamManager the team manager of the championship
    * @param matches the matches of the championship
    */
    Championship(const TeamManager &teamManager, const std::vector<Match> &matches);

    /**
    * The default destructor of the championship.
    */
    ~Championship() = default;

    /**
    * Validates the next round number and if it is valid, the methods increases the
    * current round number. If not - the method throws an exception.
    */
    void increaseRoundNumber();

    [[nodiscard]] TeamManager& getTeamManager();

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
     * Returns a vector of the matches.
     * @return a const reference to the current championship's matches' vector.
     */
    [[nodiscard]] std::vector<Match> &getMatches();

    /**
     * @return the current round number.
     */
    [[nodiscard]] unsigned getCurrentRoundNumber() const;

    /**
     * @return a reference to the account manager assigned to this championship.
    */
    [[nodiscard]] AccountingManager &getAccountingManager();

    /**
     * @return a const reference to the account manager assigned to this championship .
    */
    [[nodiscard]] const AccountingManager &getAccountingManager() const;

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

   friend std::ostream& operator<<(std::ostream& os, const Championship& championship) {
      os << championship.getYear() << '\n'
         << championship.getCurrentRoundNumber() << '\n'
         << championship.isFinished() << '\n'
         << championship.getTeamManager() << '\n'
         << championship.getMatches().size() << '\n';

      for(const auto &match : championship.getMatches()) {
         os << match << '\n';
      }

      return os;
   }
   friend std::istream& operator>>(std::istream& is, Championship& championship) {
      unsigned year, currentRoundNumber;
      bool isFinished;
      TeamManager teamManager;
      int matchesCount;
      std::vector<Match> matches;

      is >> year >> currentRoundNumber >> isFinished >> teamManager >> matchesCount;
    for(int i=0;i<matchesCount;i++)
    {
     Match match;
     is >> match;
     matches.push_back(match);
    }

      championship.year = year;
      championship.currentRoundNumber = currentRoundNumber;
      championship.finished = isFinished;
      championship.teamManager = teamManager;
      championship.matches = matches;

      return is;
   }
};

#endif //CHAMPIONSHIP_H