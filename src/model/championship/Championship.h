#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include "../match/Match.h"
#include "../team/manager/TeamManager.h"
#include <vector>
#include "accountingManager/AccountingManager.h"

class Championship final {
private:
    TeamManager teamManager = TeamManager();
    AccountingManager accountingManager = AccountingManager();
    std::vector<Match> matches = std::vector<Match>();
    unsigned currentRoundNumber = 0;
    unsigned year = 0;
    bool finished = false;

public:
    Championship() = default;

    explicit Championship(const TeamManager& manager)
        : teamManager(manager), accountingManager(AccountingManager()) {}

    Championship(const TeamManager &teamManager,
                 const std::vector<Match> &matches);

    ~Championship() = default;

    void increaseRoundNumber();

    [[nodiscard]] TeamManager& getTeamManager();
    [[nodiscard]] const TeamManager &getTeamManager() const;

    [[nodiscard]] const std::vector<Match> &getMatches() const;
    [[nodiscard]] std::vector<Match> &getMatches();

    [[nodiscard]] unsigned getCurrentRoundNumber() const;

    [[nodiscard]] AccountingManager &getAccountingManager();
    [[nodiscard]] const AccountingManager &getAccountingManager() const;

    [[nodiscard]] bool isFinished() const;
    [[nodiscard]] unsigned getYear() const;

    void addMatch(const Match &match);
    void finish();

    friend std::ostream& operator<<(std::ostream& os, const Championship& championship);
    friend std::istream& operator>>(std::istream& is, Championship& championship);
};

#endif