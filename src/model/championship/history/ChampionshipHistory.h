//
// Created by User on 5/14/2026.
//

#ifndef CHAMPIONSHIPCOLLECTION_H
#define CHAMPIONSHIPCOLLECTION_H

#include "../../championship/Championship.h"

/**
 * A class that represents the history of the championships as a vector of Championship objects.
 */
class ChampionshipHistory final {
private:
    std::vector<Championship> championships = std::vector<Championship>();

public:
   static constexpr unsigned CURRENT_YEAR = 2026;

   /**
   * The default constructor of ChampionshipHistory class.
   */
   ChampionshipHistory();

   /**
   * The default destructor of the ChampionshipHistory class.
   */
   ~ChampionshipHistory() = default;

   /**
    * Adds a championship in the history log of past championships with the year when it has been held.
    * Before-hands the methods validate the passed year argument if it is at least 1900 and at most the current year.
    * @param championship - the championship that should be added in the history log
    */
   void addChampionship(const Championship& championship);

   /**
    * Returns all championships held in the past.
    * @return a map of the held championships.
    */
   [[nodiscard]] const std::vector<Championship>& getChampionships() const;

   /**
    * Returns a definite championship by its year.
    * @param year - the held year of the championship
    * @return a reference to the definite championship
    */
   const Championship& operator[](unsigned year);
};

#endif //CHAMPIONSHIPCOLLECTION_H