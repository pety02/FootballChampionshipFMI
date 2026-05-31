//
// Created by User on 5/14/2026.
//

#ifndef CHAMPIONSHIPCOLLECTION_H
#define CHAMPIONSHIPCOLLECTION_H

#include "../../championship/Championship.h"
#include "../../../utils/Map.h"

enum class ExceptionMessage;

/**
 * A class that represents the history of the championships as a map of key-value pairs where:
 * - The key is the year of the championship.
 * - The value is the definite championship.
 */
class ChampionshipHistory final {
private:
    Map<unsigned, Championship> championships; // key: year, value: championship

public:
   static unsigned CURRENT_YEAR;

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
    * @param year - the year when the championship has been held
    * @param championship - the championship that should be added in the history log
    */
   void addChampionship(unsigned year, const Championship& championship);

   /**
    * Returns all championships held in the past.
    * @return a map of the held championships.
    */
   [[nodiscard]] const Map<unsigned, Championship>& getChampionships() const;

   /**
    * Returns a definite championship by its year.
    * @param year - the held year of the championship
    * @return a reference to the definite championship
    */
   Championship& operator[](unsigned year);

   /**
   * Sets a year as a current year after a validation of it.
   * The passed year should be at least 1900 and at most the current year.
   */
   static void setCurrentYear(unsigned year);
};

unsigned ChampionshipHistory::CURRENT_YEAR = 2026;

#endif //CHAMPIONSHIPCOLLECTION_H