//
// Created by User on 6/19/2026.
//

#ifndef SYSTEMCOMMANDSENGINE_H
#define SYSTEMCOMMANDSENGINE_H

#include "../../model/championship/history/ChampionshipHistory.h"

class SystemCommandsEngine {
public:
    static void help(const std::string& command);

    static void menu();

    static void terminateProgram();

    static void exportData(const ChampionshipHistory& history, const std::string& filename);

    static void importData(ChampionshipHistory& history, const std::string& filename);
};

#endif //SYSTEMCOMMANDSENGINE_H
