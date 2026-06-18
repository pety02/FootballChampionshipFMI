//
// Created by User on 6/18/2026.
//

#ifndef TEAMTYPE_H
#define TEAMTYPE_H

/**
 * Enumerates the supported team strategies.
 *
 * The selected type determines the concrete team implementation
 * created by the TeamFactory.
 */
enum class TeamType {
    UNKNOWN,
    ATTACKING, ///< Creates a team focused on offensive play.
    DEFENSIVE, ///< Creates a team focused on defensive play.
    BALANCED   ///< Creates a team with a balanced strategy.
   };

#endif //TEAMTYPE_H