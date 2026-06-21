#include "Lineup.h"
#include <stdexcept>

bool Lineup::canAdd(const Player& p, const std::vector<Player>& result)
{
    for (const Player& x : result)
    {
        if (x.getName() == p.getName())
            return false;
    }
    return true;
}

bool Lineup::tryAdd(
    const Player& p,
    std::vector<Player>& result,
    int& gk,
    int& def,
    int& mid,
    int& wing,
    int& fwd)
{
    if (!canAdd(p, result))
        return false;

    Player::Position pos = p.getPosition();

    if (pos == Player::Position::GOALKEEPER && gk >= 1) return false;
    if (pos == Player::Position::DEFENDER && def >= 4) return false;
    if (pos == Player::Position::MIDFIELDER && mid >= 4) return false;
    if (pos == Player::Position::WINGER && wing >= 3) return false;
    if (pos == Player::Position::FORWARD && fwd >= 3) return false;

    result.push_back(p);

    switch (pos)
    {
        case Player::Position::GOALKEEPER: ++gk; break;
        case Player::Position::DEFENDER:   ++def; break;
        case Player::Position::MIDFIELDER: ++mid; break;
        case Player::Position::WINGER:     ++wing; break;
        case Player::Position::FORWARD:    ++fwd; break;
        default: break;
    }

    return true;
}

std::vector<Player> Lineup::generateRandomLineup(const Team& team)
{
    const std::vector<Player>& allPlayers = team.getPlayers();
    std::vector<Player> result;

    int gk = 0, def = 0, mid = 0, wing = 0, fwd = 0;

    for (const Player& p : allPlayers)
        if (result.size() < LINEUP_SIZE && p.getStats().matchesCount < 3)
            tryAdd(p, result, gk, def, mid, wing, fwd);

    for (const Player& p : allPlayers)
        if (result.size() < LINEUP_SIZE)
            tryAdd(p, result, gk, def, mid, wing, fwd);

    return result;
}

// ===================== CONSTRUCTORS =====================

Lineup::Lineup(Team* team)
    : team(team),
      players(team ? generateRandomLineup(*team) : std::vector<Player>()) {}

// COPY
Lineup::Lineup(const Lineup& other)
    : team(other.team),
      players(other.players) {}

// COPY ASSIGNMENT
Lineup& Lineup::operator=(const Lineup& other)
{
    if (this != &other)
    {
        team = other.team;
        players = other.players;
    }
    return *this;
}

// MOVE CONSTRUCTOR
Lineup::Lineup(Lineup&& other) noexcept
    : team(other.team),
      players(std::move(other.players))
{
    other.team = nullptr;
}

// MOVE ASSIGNMENT
Lineup& Lineup::operator=(Lineup&& other) noexcept
{
    if (this != &other)
    {
        team = other.team;
        players = std::move(other.players);
        other.team = nullptr;
    }
    return *this;
}

// ===================== METHODS =====================

void Lineup::setTeam(Team* team)
{
    this->team = team;
}

void Lineup::addPlayer(const Player& player)
{
    if (players.size() >= LINEUP_SIZE)
        throw std::runtime_error("Lineup already full");

    for (const Player& p : players)
        if (p.getName() == player.getName())
            throw std::runtime_error("Player already in lineup");

    players.push_back(player);
}

bool Lineup::isValid() const
{
    if (players.size() != LINEUP_SIZE)
        return false;

    int gk = 0, def = 0, mid = 0, wing = 0, fwd = 0;

    for (const Player& p : players)
    {
        switch (p.getPosition())
        {
            case Player::Position::GOALKEEPER: gk++; break;
            case Player::Position::DEFENDER: def++; break;
            case Player::Position::MIDFIELDER: mid++; break;
            case Player::Position::WINGER: wing++; break;
            case Player::Position::FORWARD: fwd++; break;
            default: break;
        }
    }

    return gk == 1 &&
           def >= 2 &&
           mid >= 2 &&
           wing >= 2 &&
           fwd >= 2;
}

void Lineup::removePlayer(const std::string& playerName)
{
    for (std::vector<Player>::iterator it = players.begin(); it != players.end(); )
    {
        if (it->getName() == playerName)
            it = players.erase(it);
        else
            ++it;
    }
}

const Team* Lineup::getTeam() const
{
    return team;
}

const std::vector<Player>& Lineup::getPlayers() const
{
    return players;
}