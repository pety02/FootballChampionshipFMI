//
// Created by User on 5/14/2026.
//

#include "Lineup.h"
#include <stdexcept>

std::vector<Player*> Lineup::generateRandomLineup(const Team& team)
{
    const auto& allPlayers = team.getPlayers();
    std::vector<Player*> result;

    int gk = 0, def = 0, mid = 0, wing = 0, fwd = 0;

    // helper lambda-like logic (no <algorithm>)
    auto canAdd = [&](const Player* p) -> bool
    {
        if (!p) return false;

        // uniqueness
        for (auto x : result)
            if (x == p) return false;

        return true;
    };

    auto tryAdd = [&](Player* p) -> bool
    {
        if (!canAdd(p)) return false;

        Player::Position pos = p->getPosition();

        // enforce position limits
        if (pos == Player::Position::GOALKEEPER && gk >= 1) return false;
        if (pos == Player::Position::DEFENDER && def >= 4) return false;
        if (pos == Player::Position::MIDFIELDER && mid >= 4) return false;
        if (pos == Player::Position::WINGER && wing >= 3) return false;
        if (pos == Player::Position::FORWARD && fwd >= 3) return false;

        // add player
        result.push_back(p);

        switch (pos)
        {
            case Player::Position::GOALKEEPER: gk++; break;
            case Player::Position::DEFENDER: def++; break;
            case Player::Position::MIDFIELDER: mid++; break;
            case Player::Position::WINGER: wing++; break;
            case Player::Position::FORWARD: fwd++; break;
            default: break; // TODO: can be thrown an exception
        }

        return true;
    };

    // =========================================================
    // 1. PRIORITY PASS: players with < 3 matches
    // =========================================================
    for (auto p : allPlayers)
    {
        if (result.size() >= LINEUP_SIZE)
            break;

        if (p->getStats().matchesCount < 3)
        {
            tryAdd(p);
        }
    }

    // =========================================================
    // 2. SECOND PASS: fill remaining slots
    // =========================================================
    for (auto p : allPlayers)
    {
        if (result.size() >= LINEUP_SIZE)
            break;

        tryAdd(p);
    }

    // =========================================================
    // 3. FINAL VALIDATION (optional but recommended)
    // =========================================================
    if (result.size() != LINEUP_SIZE ||
        gk != 1 ||
        def < 2 ||
        mid < 2 ||
        wing < 2 ||
        fwd < 2)
    {
        throw std::runtime_error("Failed to generate valid lineup");
    }

    return result;
}

Lineup::Lineup(Team* team) {
    this->team = team;
    this->players = Lineup::generateRandomLineup(*team);
}

Lineup::Lineup(const Lineup &other)
    : team(other.team), players(other.players)
{}

Lineup & Lineup::operator=(const Lineup &other) {
    if (this != &other) {
        team = other.team;
        players = other.players;
    }
    return *this;
}

Lineup::~Lineup() {
    players.clear();
    team = nullptr;
}

void Lineup::setTeam(Team* team) {
    this->team = team;
}

void Lineup::addPlayer(Player* player)
{
    if (!player) return;

    if (players.size() >= LINEUP_SIZE)
        throw std::runtime_error("Lineup already full");

    // check duplicates
    for (auto p : players)
    {
        if (p == player || p->getName() == player->getName())
            throw std::runtime_error("Player already in lineup"); // use PlayerValidator::validateName(currentPlayer->getName(), player->getName());
    }

    players.push_back(player);
}

bool Lineup::isValid() const
{
    if (players.size() != LINEUP_SIZE)
        return false;

    int gk = 0, def = 0, mid = 0, wing = 0, fwd = 0;

    for (auto p : players)
    {
        switch (p->getPosition())
        {
            case Player::Position::GOALKEEPER: gk++; break;
            case Player::Position::DEFENDER: def++; break;
            case Player::Position::MIDFIELDER: mid++; break;
            case Player::Position::WINGER: wing++; break;
            case Player::Position::FORWARD: fwd++; break;
            default: break; // TODO: can be thrown an exception
        }
    }

    return gk == 1 &&
           def >= 2 &&
           mid >= 2 &&
           wing >= 2 &&
           fwd >= 2;
}

void Lineup::removePlayer(const std::string& playerName) {
    for (int i = 0; i < this->players.size(); ++i) {
        if(this->players[i]->getName() == playerName) {
            this->players.erase(this->players.begin() + i);
        }
    }
}

const Team* Lineup::getTeam() const {
    return this->team;
}

const std::vector<Player *> & Lineup::getPlayers() const {
    return this->players;
}