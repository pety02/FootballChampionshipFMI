#include "Match.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Match::MatchResult::Scorer::Scorer(Player player, bool isHome)
    : player(player), isHome(isHome)
{}

// =========================
// MatchResult RULE OF FIVE
// =========================

Match::MatchResult::~MatchResult()
{
    for (Scorer* s : goals)
        delete s;
}

Match::MatchResult::MatchResult(const MatchResult& other)
    : home(other.home),
      guest(other.guest),
      homeGoals(other.homeGoals),
      guestGoals(other.guestGoals)
{
    for (Scorer* s : other.goals)
        goals.push_back(new Scorer(*s));
}

Match::MatchResult& Match::MatchResult::operator=(const MatchResult& other)
{
    if (this == &other)
        return *this;

    for (Scorer* s : goals)
        delete s;

    goals.clear();

    home = other.home;
    guest = other.guest;
    homeGoals = other.homeGoals;
    guestGoals = other.guestGoals;

    for (Scorer* s : other.goals)
        goals.push_back(new Scorer(*s));

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

// =========================
// MATCH IMPLEMENTATION
// =========================

Match::Match() = default;

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

// -------------------------
// COPY CONSTRUCTOR
// -------------------------

Match::Match(const Match &other)
    : hostLineup(other.hostLineup),
      guestLineup(other.guestLineup),
      hostGoals(other.hostGoals),
      guestGoals(other.guestGoals),
      roundNumber(other.roundNumber),
      matchResult(other.matchResult),
      finished(other.finished)
{
    host = other.host ? other.host->clone() : nullptr;
    guest = other.guest ? other.guest->clone() : nullptr;
}

// -------------------------
// COPY ASSIGNMENT
// -------------------------

Match& Match::operator=(const Match &other)
{
    if (this == &other)
        return *this;

    delete host;
    delete guest;

    host = other.host ? other.host->clone() : nullptr;
    guest = other.guest ? other.guest->clone() : nullptr;

    hostLineup = other.hostLineup;
    guestLineup = other.guestLineup;

    hostGoals = other.hostGoals;
    guestGoals = other.guestGoals;
    roundNumber = other.roundNumber;
    finished = other.finished;

    matchResult = other.matchResult;

    return *this;
}

// -------------------------
// DESTRUCTOR
// -------------------------

Match::~Match()
{
    delete host;
    delete guest;
}

// =========================
// CORE LOGIC
// =========================

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
unsigned Match::getRoundNumber() const { return roundNumber; }

std::vector<Player> Match::getScorers() const
{
    std::vector<Player> scorers;

    for (auto* g : matchResult.goals)
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

// =========================
// STRATEGY FUNCTIONS
// =========================

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

// =========================
// MATCH SIMULATION
// =========================

Match::MatchResult Match::play() const
{
    if (finished)
        return matchResult;

    static bool seeded = false;
    if (!seeded)
    {
        std::srand((unsigned)std::time(nullptr));
        seeded = true;
    }

    MatchResult result;
    result.home = host;
    result.guest = guest;

    unsigned hostGoalsTmp = 0;
    unsigned guestGoalsTmp = 0;

    std::vector<MatchResult::Scorer*> goals;

    unsigned hostAttack = calculateAttackStrength(hostLineup);
    unsigned guestAttack = calculateAttackStrength(guestLineup);
    unsigned hostDefense = calculateDefenseStrength(hostLineup);
    unsigned guestDefense = calculateDefenseStrength(guestLineup);

    for (int i = 0; i < 10; i++)
    {
        unsigned chance = std::clamp(hostAttack + 30 - guestDefense + 5, 5u, 80u);

        if ((std::rand() % 100) < chance)
        {
            hostGoalsTmp++;
            goals.push_back(new MatchResult::Scorer(
                chooseScorer(hostLineup.getPlayers()), true));
        }
    }

    for (int i = 0; i < 10; i++)
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

    return result;
}

std::ostream& operator<<(std::ostream& os, const Match::MatchResult& mr)
{
    os << (mr.home ? mr.home->getName() : "null") << '\n'
       << (mr.guest ? mr.guest->getName() : "null") << '\n'
       << mr.homeGoals << '\n'
       << mr.guestGoals << '\n'
       << mr.goals.size() << '\n';

    for (const auto* g : mr.goals)
        os << *g;

    return os;
}

std::istream& operator>>(std::istream& is, Match::MatchResult& mr)
{
    for (auto* g : mr.goals)
        delete g;

    mr.goals.clear();

    std::string homeName, guestName;
    size_t goalCount;

    std::getline(is >> std::ws, homeName);
    std::getline(is, guestName);

    is >> mr.homeGoals >> mr.guestGoals >> goalCount;

    mr.home = nullptr;
    mr.guest = nullptr;

    for (size_t i = 0; i < goalCount; i++)
    {
        auto* s = new Match::MatchResult::Scorer();
        is >> *s;
        mr.goals.push_back(s);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Match& m)
{
    os << (m.host ? m.host->getName() : "null") << '\n'
       << (m.guest ? m.guest->getName() : "null") << '\n'
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
    std::string hostName, guestName;

    std::getline(is >> std::ws, hostName);
    std::getline(is, guestName);

    is >> m.hostLineup
       >> m.guestLineup
       >> m.hostGoals
       >> m.guestGoals
       >> m.roundNumber
       >> m.matchResult
       >> m.finished;

    m.host = nullptr;
    m.guest = nullptr;

    return is;
}