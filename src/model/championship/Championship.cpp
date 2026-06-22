#include "../championship/Championship.h"

#include <stdexcept>
#include "validator/ChampionshipValidator.h"
#include "../match/validator/MatchValidator.h"
#include "../../utils/ExceptionMessages.h"

Championship::Championship(const TeamManager& teamManager,
const std::vector<Match> &matches, int year,
const AccountingManager& accountingManager)
    : teamManager(teamManager),
      accountingManager(accountingManager),
      matches(matches),
      currentRoundNumber(0),
      year(year),
      finished(false)
{
    unsigned teamsCount = teamManager.getTeams().size();

    if (matches.size() < teamsCount * (teamsCount - 1))
        throw std::invalid_argument(toString(ExceptionMessages::NOT_ENOUGH_MATCHES));
    if(teamsCount * (teamsCount - 1) < matches.size()) {
        throw std::invalid_argument(toString(ExceptionMessages::MORE_MATCHES_THAN_IT_IS_POSSIBLE));
    }

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

void Championship::addMatch(const Match &match)
{
    unsigned teamsCount = this->teamManager.getTeams().size();

    MatchValidator::validateHasEnoughMatches(
        this->matches.size(),
        teamsCount * (teamsCount - 1)
    );

    this->matches.push_back(match);
}

void Championship::finish()
{
    this->finished = true;
}

void Championship::setTeamManager(const TeamManager &teamManager) {
    this->teamManager = teamManager;
}

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