#ifndef SYSTEMCOMMANDSENGINE_H
#define SYSTEMCOMMANDSENGINE_H

#include "../../model/championship/history/ChampionshipHistory.h"

class SystemCommandsEngine {
public:
    /**
   * Terminates the program execution.
   *
   * Prints a message indicating that the application is exiting.
   * Actual shutdown logic is expected to be handled by the caller.
   */
   static void terminateProgram();

    /**
   * Displays help information for a specific command.
   *
   * This function parses the provided command string and prints
   * detailed usage instructions, arguments, and examples depending
   * on the command type.
   *
   * @param command The command name for which help is requested.
   */
   static void help(const std::string &command);

    /**
    * Prints the main menu with all available system commands grouped by category.
    */
    static void menu();

    /**
    * Saves all championships from history into a file.
    *
    * @param history The championship history to export.
    * @param filename Output file name.
    */
    static void exportData(const ChampionshipHistory &history, const std::string &filename);

    /**
    * Loads championships from a file into history.
    *
    * @param history The history object to populate.
    * @param filename Input file name.
    */
    static void importData(ChampionshipHistory &history, const std::string &filename);
};

#endif //SYSTEMCOMMANDSENGINE_H