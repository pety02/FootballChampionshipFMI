//
// Created by User on 5/14/2026.
//

#ifndef CHAMPIONSHIPCOLLECTION_H
#define CHAMPIONSHIPCOLLECTION_H

#include "Championship.h"
#include "Map.h"

/**
 *
 */
class ChampionshipHistory final {
private:
    Map<unsigned, Championship> championships; // key: year, value: championship

public:
   static unsigned CURRENT_YEAR;

    ChampionshipHistory();
    ~ChampionshipHistory() = default;

    /**
     *
     * @param championship
     */
    void addChampionship(unsigned year, const Championship& championship);

    /**
     *
     * @return
     */
     [[nodiscard]] const Map<unsigned, Championship>& getChampionships() const;

    /**
     *
     * @param year
     * @return
     */
    Championship& operator[](unsigned year);

    static void setCurrentYear(unsigned year);
};

unsigned ChampionshipHistory::CURRENT_YEAR = 2026;

#endif //CHAMPIONSHIPCOLLECTION_H