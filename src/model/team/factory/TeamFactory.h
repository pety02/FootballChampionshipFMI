#ifndef TEAMFACTORY_H
#define TEAMFACTORY_H

#include "../TeamType.h"
#include "../../player/Player.h"
#include <string>
#include <vector>

class Team;

/**
 * A factory class responsible for creating team instances.
 *
 * This class encapsulates the creation logic for the different
 * types of teams supported by the application and returns
 * dynamically allocated Team objects.
 */
class TeamFactory {
public:
    static Team* fullyInitializeTeam(TeamType type,
         const std::string &name,
         const std::string &stadiumName,
         const std::vector<Player> &players,
         double budget,
         unsigned forwardersCount,
         unsigned midfieldersCount,
         unsigned goalkeepersCount,
         unsigned defendersCount,
         unsigned wingersCount);

    /**
     * Creates a team of the specified type.
     *
     * Depending on the provided TeamType value, an instance of the
     * corresponding Team-derived class is dynamically allocated
     * and initialized with the supplied information.
     *
     * @param type The type of team to create.
     * @param name The name of the team.
     * @param stadiumName The name of the team's home stadium.
     * @param budget The initial budget assigned to the team.
     *
     * @return Pointer to the newly created Team object or nullptr if the object is not created.
     *
     * @note The caller assumes ownership of the returned pointer and is
     * responsible for releasing the allocated memory.
     */
    static Team* createTeam(TeamType type,
                            const std::string& name,
                            const std::string& stadiumName,
                            double budget);

    /**
    * Creates a default empty team needed for creating a team pointer before
    * starting reading its fields' values from a binary file.
    *
    * @param type The type of team to create.
    *
    * @return Pointer to the newly created Team object or nullptr if the object is not created.
    *
    * @note The caller assumes ownership of the returned pointer and is
    * responsible for releasing the allocated memory.
    */
    static Team* createEmptyTeam(TeamType type);
};

#endif //TEAMFACTORY_H