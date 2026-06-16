//
// Created by User on 5/14/2026.
//

#ifndef BALANCEDTEAM_H
#define BALANCEDTEAM_H

#include "Team.h"
#include <string>

/**
 *
 */
class BalancedTeam final : public Team {
public:
    static constexpr unsigned REQUIRED_GOALKEEPERS = 2;
    static constexpr unsigned MIN_FORWARDERS_REQUIRED = 4;
    static constexpr unsigned MIN_DEFENDERS_REQUIRED = 4;
    static constexpr unsigned MIN_MIDFIELDERS_REQUIRED = 4;
    static constexpr unsigned MIN_WINGERS_REQUIRED = 4;

    BalancedTeam();
    BalancedTeam(const std::string& name, const std::string& coachName, const std::string& stadiumName, double budget);
    BalancedTeam(const BalancedTeam& other);
    BalancedTeam& operator=(const BalancedTeam& other);
    ~BalancedTeam() noexcept override = default;

    /**
     *
     * @return
     */
    [[nodiscard]] Team* clone() const override;

    /**
     *
     * @param player
     */
    void addPlayer(Player& player, bool isTransfer) override;
};

#endif //BALANCEDTEAM_H