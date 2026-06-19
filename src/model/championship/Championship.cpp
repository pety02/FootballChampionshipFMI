#include "../championship/Championship.h"

#include <stdexcept>
#include "history/ChampionshipHistory.h"
#include "validator/ChampionshipValidator.h"
#include "../match/validator/MatchValidator.h"
#include "../../utils/ExceptionMessages.h"

Championship::Championship(const TeamManager& teamManager,
                           const std::vector<Match> &matches)
    : teamManager(teamManager),
      matches(matches),
      currentRoundNumber(0),
      year(ChampionshipHistory::CURRENT_YEAR),
      finished(false)
{
    unsigned teamsCount = teamManager.getTeams().size();

    if (matches.size() < teamsCount * (teamsCount - 1))
        throw std::invalid_argument(toString(ExceptionMessages::NOT_ENOUGH_MATCHES));

    MatchValidator::validateLineups(this->matches);
}

// --------------------
// ROUND CONTROL
// --------------------

void Championship::increaseRoundNumber()
{
    ChampionshipValidator::validateCurrentRoundNumber(this->currentRoundNumber + 1);
    ++this->currentRoundNumber;
}

// --------------------
// GETTERS
// --------------------

TeamManager& Championship::getTeamManager()
{
    return this->teamManager;
}

const TeamManager& Championship::getTeamManager() const
{
    return this->teamManager;
}

const std::vector<Match>& Championship::getMatches() const
{
    return this->matches;
}

std::vector<Match>& Championship::getMatches()
{
    return this->matches;
}

unsigned Championship::getCurrentRoundNumber() const
{
    return this->currentRoundNumber;
}

AccountingManager& Championship::getAccountingManager()
{
    return this->accountingManager;
}

const AccountingManager& Championship::getAccountingManager() const
{
    return this->accountingManager;
}

bool Championship::isFinished() const
{
    return this->finished;
}

unsigned Championship::getYear() const
{
    return this->year;
}

// --------------------
// MATCH MANAGEMENT
// --------------------

void Championship::addMatch(const Match &match)
{
    unsigned teamsCount = this->teamManager.getTeams().size();

    MatchValidator::validateMatchesCount(
        this->matches.size(),
        teamsCount * (teamsCount - 1)
    );

    this->matches.push_back(match);
}

void Championship::finish()
{
    this->finished = true;
}

// --------------------
// STREAM OUTPUT
// --------------------

std::ostream& operator<<(std::ostream& os, const Championship& championship)
{
    os << championship.year << '\n'
       << championship.currentRoundNumber << '\n'
       << championship.finished << '\n'
       << championship.teamManager << '\n'
       << championship.matches.size() << '\n';

    for (const Match& match : championship.matches)
        os << match << '\n';

    return os;
}

// --------------------
// STREAM INPUT (FIXED SAFETY)
// --------------------

std::istream& operator>>(std::istream& is, Championship& championship)
{
    unsigned year;
    unsigned currentRoundNumber;
    bool isFinished;
    TeamManager tm;
    size_t matchesCount;

    is >> year >> currentRoundNumber >> isFinished >> tm >> matchesCount;

    std::vector<Match> matches;
    matches.reserve(matchesCount);

    for (size_t i = 0; i < matchesCount; i++)
    {
        Match match;
        is >> match;
        matches.push_back(match);
    }

    championship.year = year;
    championship.currentRoundNumber = currentRoundNumber;
    championship.finished = isFinished;

    // safe assignment (avoids partial overwrite issues)
    championship.teamManager = tm;

    championship.matches = std::move(matches);

    return is;
}