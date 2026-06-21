#ifndef LINEUP_H
#define LINEUP_H

#include "../../team/Team.h"
#include "../../player/Player.h"
#include <vector>
#include <string>

/**
* A class that describes the lineups, formed by a team in the championships.
*/
class Lineup final {
private:
    Team* team = nullptr; // non-owning pointer
    std::vector<Player> players;

    /**
    * Generates a random lineup with players from a definite team.
    */
    static std::vector<Player> generateRandomLineup(const Team& team);

    bool canAdd(const Player& p, const std::vector<Player>& result);
    bool tryAdd(const Player& p, std::vector<Player>& result,
        int& gk, int& def, int& mid, int& wing, int& fwd);
public:
    static constexpr unsigned LINEUP_SIZE = 11;

    Lineup() = default;

    explicit Lineup(Team* team);

    Lineup(const Lineup& other);
    Lineup& operator=(const Lineup& other);

    Lineup(Lineup&& other) noexcept;
    Lineup& operator=(Lineup&& other) noexcept;

    ~Lineup() = default;

    void setTeam(Team* team);

    void addPlayer(const Player& player);

    [[nodiscard]] bool isValid() const;

    void removePlayer(const std::string& playerName);

    [[nodiscard]] const Team* getTeam() const;

    [[nodiscard]] const std::vector<Player>& getPlayers() const;

    friend std::ostream& operator<<(std::ostream& os, const Lineup& lineup) {
        os << (lineup.team ? lineup.team->getName() : "NULL") << '\n';
        os << lineup.players.size() << '\n';

        for (const Player& p : lineup.players)
            os << p;

        return os;
    }

    friend std::istream& operator>>(std::istream& is, Lineup& lineup) {
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

        lineup.team = nullptr; // resolved externally
        lineup.players = std::move(players);

        return is;
    }
};

#endif // LINEUP_H