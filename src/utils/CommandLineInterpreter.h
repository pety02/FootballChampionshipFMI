//
// Created by User on 6/4/2026.
//

#ifndef COMMANDLINEINTERPRETER_H
#define COMMANDLINEINTERPRETER_H

#include <string>
#include <vector>

#include "Command.h"
#include "../model/championship/history/ChampionshipHistory.h"

/**
 * Main CLI controller responsible for interpreting commands
 * and delegating execution to the simulation logic.
 *
 * IMPORTANT:
 * - This class uses raw pointers but does NOT own the objects
 *   passed into its constructor.
 */
class CommandLineInterpreter {
private:
    ChampionshipHistory history = ChampionshipHistory();
    Championship championship = Championship();

public:
    /**
     * Creates interpreter with external ownership.
     *
     * @param h Championship history (owned externally)
     * @param c Active championship (owned externally)
     */
    CommandLineInterpreter(
        const ChampionshipHistory& h,
        const Championship& c
    ) : history(h), championship(c) {}

    /**
     * Executes a parsed command with arguments.
     *
     * @param command Parsed command enum
     * @param args Command arguments
     */
    void execute(Command command, const std::vector<std::string> &args);
};

#endif // COMMANDLINEINTERPRETER_H