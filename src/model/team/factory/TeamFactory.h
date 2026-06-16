//
// Created by User on 5/16/2026.
//

#ifndef TEAMFACTORY_H
#define TEAMFACTORY_H

#include "../Team.h"
#include <string>

/**
 * Enumerates the supported team strategies.
 *
 * The selected type determines the concrete team implementation
 * created by the TeamFactory.
 */
enum class TeamType {
    ATTACKING, ///< Creates a team focused on offensive play.
    DEFENSIVE, ///< Creates a team focused on defensive play.
    BALANCED   ///< Creates a team with a balanced strategy.
};

/**
 * A factory class responsible for creating team instances.
 *
 * This class encapsulates the creation logic for the different
 * types of teams supported by the application and returns
 * dynamically allocated Team objects.
 */
class TeamFactory {
public:
    /**
     * Creates a team of the specified type.
     *
     * Depending on the provided TeamType value, an instance of the
     * corresponding Team-derived class is dynamically allocated
     * and initialized with the supplied information.
     *
     * @param type The type of team to create.
     * @param name The name of the team.
     * @param coachName The name of the team's coach.
     * @param stadiumName The name of the team's home stadium.
     * @param budget The initial budget assigned to the team.
     *
     * @return Pointer to the newly created Team object.
     *
     * @throws std::invalid_argument If the specified team type is invalid.
     *
     * @note The caller assumes ownership of the returned pointer and is
     * responsible for releasing the allocated memory.
     */
    static Team* createTeam(TeamType type,
                            const std::string& name,
                            const std::string& coachName,
                            const std::string& stadiumName,
                            double budget);
};

#endif //TEAMFACTORY_H