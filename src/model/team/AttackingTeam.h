//
// Created by User on 5/14/2026.
//

#ifndef ATTACKINGTEAM_H
#define ATTACKINGTEAM_H

#include "Team.h"
#include "../player/Player.h"

/**
 *
 */
class AttackingTeam final : public Team {
public:
    static constexpr unsigned FROWARD_MIN_SCORED_GOALS = 6;
    static constexpr unsigned REQUIRED_GOALKEEPERS = 2;
    static constexpr unsigned MIN_FORWARDERS_REQUIRED = 8;
    static constexpr unsigned MIN_DEFENDERS_REQUIRED = 2;
    static constexpr unsigned MIN_MIDFIELDERS_REQUIRED = 2;
    static constexpr unsigned MIN_WINGERS_REQUIRED = 2;

    AttackingTeam();
    AttackingTeam(const std::string& name, const std::string& coachName, const std::string& stadiumName, double budget);
    AttackingTeam(const AttackingTeam& other);
    AttackingTeam& operator=(const AttackingTeam& other);
    ~AttackingTeam() noexcept override = default;

    /**
     *
     * @return
     */
    [[nodiscard]] Team* clone() const override;

    /**
     *
     * @param player
     */
    void addPlayer(Player* player, bool isTransfer) override;
};

#endif //ATTACKINGTEAM_H