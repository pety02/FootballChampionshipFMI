#include "Lineup.h"
#include <stdexcept>

bool Lineup::canAdd(const Player& player, const std::vector<Player>& teamPlayersList)
{
    for (const Player& x : teamPlayersList)
    {
        if (x.getName() == player.getName())
            return false;
    }
    return true;
}

bool Lineup::tryAdd(
    const Player& player,
    std::vector<Player>& teamPlayersList,
    int& gk,
    int& def,
    int& mid,
    int& wing,
    int& fwd)
{
    if (!canAdd(player, teamPlayersList))
        return false;

    Player::Position pos = player.getPosition();

    if (pos == Player::Position::GOALKEEPER && gk >= 1) return false;
    if (pos == Player::Position::DEFENDER && def >= 4) return false;
    if (pos == Player::Position::MIDFIELDER && mid >= 4) return false;
    if (pos == Player::Position::WINGER && wing >= 3) return false;
    if (pos == Player::Position::FORWARD && fwd >= 3) return false;

    teamPlayersList.push_back(player);

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

    bool sucessfullyAdded = false;
    for (const Player& p : allPlayers)
        if (result.size() < LINEUP_SIZE && p.getStats().matchesCount < 3)
            sucessfullyAdded = Lineup::tryAdd(p, result, gk, def, mid, wing, fwd) && isValid(result);

    for (const Player& p : allPlayers)
        if (result.size() < LINEUP_SIZE)
            sucessfullyAdded = Lineup::tryAdd(p, result, gk, def, mid, wing, fwd) && isValid(result);

    if(!sucessfullyAdded) return std::vector<Player>();

    return result;
}

Lineup::Lineup(Team* team)
    : team(team),
      players(team ? generateRandomLineup(*team) : std::vector<Player>()) {}

Lineup::Lineup(const Lineup& other)
    : team(other.team),
      players(other.players) {}

Lineup& Lineup::operator=(const Lineup& other)
{
    if (this != &other)
    {
        team = other.team;
        players = other.players;
    }
    return *this;
}

Lineup::Lineup(Lineup&& other) noexcept
    : team(other.team),
      players(std::move(other.players))
{
    other.team = nullptr;
}

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

bool Lineup::isValid(const std::vector<Player>& players)
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

// TODO: add variant for removing a player from the lineup - maybe on transfer if he/she is part of a lineup
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

std::ostream& operator<<(std::ostream& os, const Lineup& lineup) {
    os << (lineup.team ? lineup.team->getName() : "NULL") << '\n';
    os << lineup.players.size() << '\n';

    for (const Player& p : lineup.players)
        os << p;

    return os;
}

std::istream& operator>>(std::istream& is, Lineup& lineup) {
    std::string teamName;
    size_t count;

    std::getline(is >> std::ws, teamName);
    is >> count;

    std::vector<Player> players;

    for (size_t i = 0; i < count; i++) {
        Player p;
        is >> p;
        players.push_back(p);
    }

    lineup.team = nullptr;
    lineup.players = std::move(players);

    return is;
}