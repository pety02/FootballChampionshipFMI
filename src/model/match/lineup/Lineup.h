//
// Created by User on 5/14/2026.
//
#ifndef LINEUP_H
#define LINEUP_H

#include "../../team/Team.h"
#include "../../player/Player.h"

/**
* A class that describes the lineups, formed by a team in the championships.
*/
class Lineup final {
private:
    Team* team = nullptr;
    std::vector<Player> players = std::vector<Player>();

    /**
    * Generates a random lineup with players from a definite team.
    *
    * @param team - the parent team of a lineup.
    * @return a vector of Players' pointers part of a lineup.
    */
    static std::vector<Player> generateRandomLineup(const Team& team);
public:
    static constexpr unsigned LINEUP_SIZE = 11;

    Lineup() = default;
    /**
    * Creates a lineup with a parent team.
    *
    * @param team a parental team.
    */
    explicit Lineup(Team* team);

    /**
    * Creates a lineup as a copy of another lineup.
    *
    * @param other the lineup that should be copied.
    */
    Lineup(const Lineup& other);

    /**
    * Assigns a lineup to the current lineup.
    *
    * @param other the lineup that should be assigned to the current pointer.
    * @return the current lineup with the newly assigned value.
    */
    Lineup& operator=(const Lineup& other);

    /**
    * Destructs the current lineup.
    */
    ~Lineup();

    /**
    * Sets a parental team to the current lineup.
    *
    * @param team the parental lineup.
    */
    void setTeam(Team* team);

    /**
    * Adds a player in the current lineup.
    *
    * @param player the player who should be added in the current lineup.
    */
    void addPlayer(const Player&);

    /**
    * Checks whether the lineup is valid configuration.
    * The valid lineup should contain:
    *   - 1 goalkeeper
    *   - at least 2 defenders
    *   - at least 2 midfielders
    *   - at least 2 wingers
    *   - at least 2 forwarders
    *
    * @return a boolean value - true if the lineup is valid and false otherwise
    */
    [[nodiscard]] bool isValid() const;

    /**
    * Removes a player from the current lineup on the base of his/her name.
    *
    * @param playerName the name of the player who should be removed.
    */
    void removePlayer(const std::string& playerName);

    /**
    * @return a const pointer to the parental team.
    */
    [[nodiscard]] const Team* getTeam() const;

    /**
    * @return a const reference to the players in the lineup.
    */
    [[nodiscard]] const std::vector<Player>& getPlayers() const;

    friend std::ostream& operator<<(std::ostream& os,
                                const Lineup& lineup)
    {
        os << lineup.team->getName() << '\n';

        os << lineup.players.size() << '\n';

        for(const auto& p : lineup.players)
            os << p;

        return os;
    }
    friend std::istream& operator>>(std::istream& is,
                                Lineup& lineup)
    {
        std::string teamName;

        size_t count;

        std::getline(is >> std::ws, teamName);

        is >> count;

        std::vector<Player> players;

        for(size_t i=0;i<count;i++)
        {
            Player p;
            is >> p;

            players.push_back(p);
        }

        lineup.team = nullptr; // resolve later
        lineup.players = std::move(players);

        return is;
    }
};

#endif //LINEUP_H