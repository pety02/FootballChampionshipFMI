#include "Match.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <validator/MatchValidator.h>
#include "../../utils/ExceptionMessages.h"

Match::MatchResult::Scorer::Scorer(const Player &player, bool isHome)
    : player(player), isHome(isHome)
{}

Match::MatchResult::~MatchResult() noexcept
{
    delete home;
    delete guest;

    for (Scorer* s : goals)
        delete s;
}

Match::MatchResult::MatchResult(const MatchResult& other)
    : home(other.home ? other.home->clone() : nullptr),
      guest(other.guest ? other.guest->clone() : nullptr),
      homeGoals(other.homeGoals),
      guestGoals(other.guestGoals)
{
    for (Scorer* s : other.goals)
        goals.push_back(new Scorer(*s));
}

Match::MatchResult::MatchResult(Team *home, Team *guest, unsigned homeGoals, unsigned guestGoals)
    : home(home),guest(guest),homeGoals(homeGoals), guestGoals(guestGoals) {
}

Match::MatchResult::MatchResult(MatchResult&& other) noexcept
    : home(other.home),
      guest(other.guest),
      homeGoals(other.homeGoals),
      guestGoals(other.guestGoals),
      goals(std::move(other.goals))
{
    other.home = nullptr;
    other.guest = nullptr;
}

Match::MatchResult& Match::MatchResult::operator=(MatchResult&& other) noexcept
{
    if (this != &other)
    {
        delete home;
        delete guest;

        for (Scorer* s : goals)
            delete s;

        home = other.home;
        guest = other.guest;
        homeGoals = other.homeGoals;
        guestGoals = other.guestGoals;
        goals = std::move(other.goals);

        other.home = nullptr;
        other.guest = nullptr;
    }

    return *this;
}

Match::MatchResult& Match::MatchResult::operator=(const MatchResult& other)
{
    if (this == &other)
        return *this;

    MatchResult temp(other);
    std::swap(home, temp.home);
    std::swap(guest, temp.guest);
    std::swap(homeGoals, temp.homeGoals);
    std::swap(guestGoals, temp.guestGoals);
    std::swap(goals, temp.goals);

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Match::MatchResult::Scorer& scorer)
{
    os << scorer.player << '\n'
       << scorer.isHome << '\n';
    return os;
}

std::istream& operator>>(std::istream& is, Match::MatchResult::Scorer& scorer)
{
    Player p;
    bool isHome;

    is >> p >> isHome;
    scorer = Match::MatchResult::Scorer(p, isHome);

    return is;
}

Match::Match(const Lineup &hostLineup, const Lineup &guestLineup)
    : hostLineup(hostLineup),
      guestLineup(guestLineup),
      host(nullptr),
      guest(nullptr),
      hostGoals(0),
      guestGoals(0),
      roundNumber(0),
      matchResult(),
      finished(false)
{
    try {
        host = hostLineup.getTeam()->clone();
        guest = guestLineup.getTeam()->clone();
    }
    catch (...) {
        delete host;
        delete guest;
        throw;
    }
}

Match::Match(Team* host, Team* guest, const Lineup& hostLineup, const Lineup& guestLineup, unsigned hostGoals,
        unsigned guestGoals, unsigned roundNumber, const MatchResult& result, bool isFinished)
: host(host), guest(guest), hostLineup(hostLineup), guestLineup(guestLineup),
hostGoals(hostGoals), guestGoals(guestGoals), roundNumber(roundNumber), finished(isFinished) {

}

Match::Match(const Match& other)
    : hostLineup(other.hostLineup),
      guestLineup(other.guestLineup),
      hostGoals(other.hostGoals),
      guestGoals(other.guestGoals),
      roundNumber(other.roundNumber),
      matchResult(other.matchResult),
      finished(other.finished),
      host(other.host ? other.host->clone() : nullptr),
      guest(other.guest ? other.guest->clone() : nullptr)
{
}

Match& Match::operator=(const Match& other)
{
    if (this == &other)
        return *this;

    Match temp(other);

    std::swap(host, temp.host);
    std::swap(guest, temp.guest);
    std::swap(hostLineup, temp.hostLineup);
    std::swap(guestLineup, temp.guestLineup);
    std::swap(hostGoals, temp.hostGoals);
    std::swap(guestGoals, temp.guestGoals);
    std::swap(roundNumber, temp.roundNumber);
    std::swap(matchResult, temp.matchResult);
    std::swap(finished, temp.finished);

    return *this;
}

Match::Match(Match&& other) noexcept
    : host(other.host),
      guest(other.guest),
      hostLineup(std::move(other.hostLineup)),
      guestLineup(std::move(other.guestLineup)),
      hostGoals(other.hostGoals),
      guestGoals(other.guestGoals),
      roundNumber(other.roundNumber),
      matchResult(std::move(other.matchResult)),
      finished(other.finished)
{
    other.host = nullptr;
    other.guest = nullptr;
    other.hostGoals = 0;
    other.guestGoals = 0;
    other.roundNumber = 0;
    other.finished = false;
}

Match& Match::operator=(Match&& other) noexcept
{
    if (this != &other)
    {
        delete host;
        delete guest;

        hostLineup = std::move(other.hostLineup);
        guestLineup = std::move(other.guestLineup);
        matchResult = std::move(other.matchResult);

        host = other.host;
        guest = other.guest;

        hostGoals = other.hostGoals;
        guestGoals = other.guestGoals;
        roundNumber = other.roundNumber;
        finished = other.finished;

        other.host = nullptr;
        other.guest = nullptr;
        other.hostGoals = 0;
        other.guestGoals = 0;
        other.roundNumber = 0;
        other.finished = false;
    }

    return *this;
}

Match::~Match() noexcept
{
    delete host;
    delete guest;
}

void Match::increaseRoundNumber()
{
    roundNumber++;
}

Team* Match::getHost() const { return host; }
Team* Match::getGuest() const { return guest; }

const Lineup& Match::getHostLineup() const { return hostLineup; }
const Lineup& Match::getGuestLineup() const { return guestLineup; }

unsigned Match::getHostGoals() const { return hostGoals; }
unsigned Match::getGuestGoals() const { return guestGoals; }

std::vector<Player> Match::getScorers() const
{
    std::vector<Player> scorers;

    for (MatchResult::Scorer* g : matchResult.goals)
        scorers.push_back(g->player);

    return scorers;
}

void Match::setHost(Team* h) { host = h; }
void Match::setGuest(Team* g) { guest = g; }

void Match::setHostLineup(const Lineup& l) { hostLineup = l; }
void Match::setGuestLineup(const Lineup& l) { guestLineup = l; }

void Match::addGoal(Player scorer, bool isHostPlayer)
{
    matchResult.goals.push_back(
        new MatchResult::Scorer(scorer, isHostPlayer)
    );
}

bool Match::isFinished() const
{
    return finished;
}

void Match::clearLineups()
{
    hostLineup = Lineup(nullptr);
    guestLineup = Lineup(nullptr);
}

unsigned Match::calculateAttackStrength(const Lineup& lineup)
{
    unsigned strength = 0;

    for (const Player& p : lineup.getPlayers())
    {
        switch (p.getPosition())
        {
            case Player::Position::FORWARD: strength += 4; break;
            case Player::Position::WINGER: strength += 3; break;
            case Player::Position::MIDFIELDER: strength += 2; break;
            case Player::Position::DEFENDER: strength += 1; break;
            default: break;
        }
    }

    return strength;
}

unsigned Match::calculateDefenseStrength(const Lineup& lineup)
{
    unsigned strength = 0;

    for (const Player& p : lineup.getPlayers())
    {
        switch (p.getPosition())
        {
            case Player::Position::GOALKEEPER: strength += 5; break;
            case Player::Position::DEFENDER: strength += 4; break;
            case Player::Position::MIDFIELDER: strength += 2; break;
            case Player::Position::WINGER: strength += 1; break;
            default: break;
        }
    }

    return strength;
}

Player Match::chooseScorer(const std::vector<Player>& players)
{
    std::vector<Player> pool;

    for (const Player& p : players)
    {
        int weight = 1;

        if (p.getPosition() == Player::Position::FORWARD) weight = 5;
        else if (p.getPosition() == Player::Position::WINGER) weight = 4;
        else if (p.getPosition() == Player::Position::MIDFIELDER) weight = 2;

        for (int i = 0; i < weight; i++)
            pool.push_back(p);
    }

    if (pool.empty())
        return players[std::rand() % players.size()];

    return pool[std::rand() % pool.size()];
}

void Match::playHalfTime(MatchResult& result) {
    static bool seeded = false;
    if (!seeded)
    {
        std::srand((unsigned)std::time(nullptr));
        seeded = true;
    }
    result.home = host;
    result.guest = guest;

    unsigned hostGoalsTmp = 0;
    unsigned guestGoalsTmp = 0;

    std::vector<MatchResult::Scorer*> goals;

    unsigned hostAttack = calculateAttackStrength(hostLineup);
    unsigned guestAttack = calculateAttackStrength(guestLineup);
    unsigned hostDefense = calculateDefenseStrength(hostLineup);
    unsigned guestDefense = calculateDefenseStrength(guestLineup);

    for (int i = 0; i < 5; i++)
    {
        unsigned chance = std::clamp(hostAttack + 30 - guestDefense + 5, 5u, 80u);

        if ((std::rand() % 100) < chance)
        {
            hostGoalsTmp++;
            goals.push_back(new MatchResult::Scorer(
                chooseScorer(hostLineup.getPlayers()), true));
        }
    }

    for (int i = 0; i < 5; i++)
    {
        unsigned chance = std::clamp(30 + guestAttack - hostDefense, 5u, 80u);

        if ((std::rand() % 100) < chance)
        {
            guestGoalsTmp++;
            goals.push_back(new MatchResult::Scorer(
                chooseScorer(guestLineup.getPlayers()), false));
        }
    }

    result.homeGoals = std::min(hostGoalsTmp, 8u);
    result.guestGoals = std::min(guestGoalsTmp, 8u);
    result.goals = goals;

    ++roundNumber;
}

Match::MatchResult Match::play()
{
    if (finished)
        return matchResult;

    MatchResult result;

    // plays first halftime
    MatchValidator::validateRoundNumber(roundNumber);
    playHalfTime(result);

    // plays second halftime
    MatchValidator::validateRoundNumber(roundNumber);
    playHalfTime(result);

    return result;
}

std::ostream& operator<<(std::ostream& os, const Match::MatchResult& mr)
{
    os << mr.home << '\n'
       << mr.guest << '\n'
       << mr.homeGoals << '\n'
       << mr.guestGoals << '\n'
       << mr.goals.size() << '\n';

    for (const Match::MatchResult::Scorer* s : mr.goals)
        os << *s;

    return os;
}

std::istream& operator>>(std::istream& is, Match::MatchResult& mr)
{
    size_t goalsCount, homeGoals, guestGoals;

    is >> std::ws;
    Team* ht = TeamFactory::createEmptyTeam(TeamType::UNKNOWN);
    is >> *ht;
    Team* gt = TeamFactory::createEmptyTeam(TeamType::UNKNOWN);
    is >> *gt;
    is >> homeGoals >> guestGoals >> goalsCount;

    std::vector<Match::MatchResult::Scorer*> goals;
    for (size_t i = 0; i < goalsCount; i++)
    {
        try {
            Match::MatchResult::Scorer* s = new Match::MatchResult::Scorer();
            is >> *s;
            goals.push_back(s);
        } catch (...) {
            throw;
        }
    }

    try {
        mr = Match::MatchResult(ht, gt, homeGoals, guestGoals);
    } catch (...) {
        throw;
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Match& m)
{
    os << m.host  << '\n'
       << m.guest  << '\n'
       << m.hostLineup << '\n'
       << m.guestLineup << '\n'
       << m.hostGoals << '\n'
       << m.guestGoals << '\n'
       << m.roundNumber << '\n'
       << m.matchResult << '\n'
       << m.finished << '\n';

    return os;
}

std::istream& operator>>(std::istream& is, Match& m)
{
    Lineup hostLineup, guestLineup;
    unsigned hostGoals, guestGoals, roundNumber;
    Match::MatchResult matchResult;
    bool isFinished;

    Team* ht = TeamFactory::createEmptyTeam(TeamType::UNKNOWN);
    is >> *ht;
    Team* gt = TeamFactory::createEmptyTeam(TeamType::UNKNOWN);
    is >> *gt;
    is >> hostLineup
       >> guestLineup
       >> hostGoals
       >> guestGoals
       >> roundNumber
       >> matchResult
       >> isFinished;

    try {
        m = Match(ht, gt, hostLineup, guestLineup, hostGoals, guestGoals, roundNumber, matchResult, isFinished);
    } catch (...) {
        throw;
    }

    return is;
}