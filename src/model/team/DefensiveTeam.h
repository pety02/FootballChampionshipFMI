//
// Created by User on 5/14/2026.
//

#ifndef DEFENSIVETEAM_H
#define DEFENSIVETEAM_H

#include "Team.h"
#include "../../player/Player.h"
#include <string>

/**
 *
 */
class DefensiveTeam final : public Team {
public:
    static constexpr unsigned REQUIRED_GOALKEEPERS = 2;
    static constexpr unsigned MIN_DEFENDERS_REQUIRED = 6;
    static constexpr unsigned MIN_MIDFIELDERS_REQUIRED = 6;
    static constexpr unsigned MIN_WINGERS_REQUIRED = 2;
    static constexpr unsigned MIN_FORWARDERS_REQUIRED = 2;

    DefensiveTeam();
    DefensiveTeam(const std::string& name, const std::string& coachName, const std::string& stadiumName, double budget);
    DefensiveTeam(const DefensiveTeam& other);
    DefensiveTeam& operator=(const DefensiveTeam& other);
    ~DefensiveTeam() noexcept override = default;

    /**
     *
     * @return
     */
    [[nodiscard]] Team* clone() const override;

    /**
     *
     * @param player
     * @param isTransfer
     */
    void addPlayer(Player& player, bool isTransfer) override;
};

#endif //DEFENSIVETEAM_H