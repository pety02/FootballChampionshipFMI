//
// Created by User on 5/14/2026.
//

#include "Lineup.h"

#include <stdexcept>

#include "PlayerValidator.h"

std::vector<Player*> Lineup::generateRandomLineup() {
    // TODO: add validational rules for generating random lineup
    return std::vector<Player*>();
}

Lineup::Lineup(Team* team) {
    this->team = team;
    this->players = this->generateRandomLineup();
}

Lineup::Lineup(const Lineup &other) : team(other.team) {
    for (int i = 0; i < other.players.size(); ++i) {
        this->players.push_back(other.players[i]);
    }
}

Lineup & Lineup::operator=(const Lineup &other) {
    if(this !=&other) {
        for (int i = 0; i < this->players.size(); ++i) {
            delete this->players[i];
        }
        this->players.clear();

        delete this->team; this->team = nullptr;

        this->team = other.team->clone();
        for (int i = 0; i < other.players.size(); ++i) {
            this->players.push_back(other.players[i]);
        }
    }

    return *this;
}

Lineup::~Lineup() {
    for (int i = 0; i < this->players.size(); ++i) {
        delete this->players[i];
    }
    this->players.clear();

    delete this->team; this->team = nullptr;
}

void Lineup::setTeam(Team* team) {
    this->team = team;
}

void Lineup::addPlayer(Player* player) {
    for (auto & currentPlayer : this->players) {
        PlayerValidator::validateName(currentPlayer->getName(), player->getName());
    }

    this->players.push_back(player);
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