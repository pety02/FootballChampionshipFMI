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
 *
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
    explicit Championship(const TeamManager& teamManager, const std::vector<Match> &matches);
    ~Championship() = default;

    void increaseRoundNumber();
    /**
     *
     * @return
     */
    [[nodiscard]] const TeamManager& getTeamManager() const;

    /**
     *
     * @return
     */
    [[nodiscard]] const std::vector<Match>& getMatches() const;

    /**
     *
     * @return
     */
    [[nodiscard]] unsigned getCurrentRoundNumber() const;

    /**
     *
     * @return
     */
    [[nodiscard]] bool isFinished() const;

    [[nodiscard]] unsigned getYear() const;

    void addMatch(const Match& match);

    void finish();
};

#endif //CHAMPIONSHIP_H