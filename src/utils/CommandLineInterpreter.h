//
// Created by User on 6/4/2026.
//

#ifndef COMMANDLINEINTERPRETER_H
#define COMMANDLINEINTERPRETER_H
#include <string>

class CommandLineInterpreter {
private:
    static void showMenu();

    static void startSeason();

    static void listSeasons();

    static void loadSeasons();

    static void saveSeasons();

    static void loadSeason();

    static void saveSeason();

    static void playRound();

    static void playAllRounds();

public:
    static void execute(const std::string& commandValue);
};

#endif //COMMANDLINEINTERPRETER_H