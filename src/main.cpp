#include <iostream>

#include "CommandLineInterpreter.h"

#include <sstream>

int main()
{
    ChampionshipHistory history;
    Championship championship = Championship(TeamManager());
    FootballGameSimulator simulator;

    CommandLineInterpreter cli(history, championship, simulator);

    cli.execute(Command::MENU, {});

    std::string line;

    while (true)
    {
        std::cout << "> ";

        if (!std::getline(std::cin, line))
            break;

        if (line.empty())
            continue;

        std::stringstream ss(line);

        std::string commandValue;
        ss >> commandValue;

        if (commandValue == "exit")
            break;

        Command cmd = parseCommand(commandValue);

        std::vector<std::string> args;
        std::string arg;

        while (ss >> arg)
        {
            args.push_back(arg);
        }

        try
        {
            cli.execute(cmd, args);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Command Error: "
                      << e.what()
                      << std::endl;
        }
        catch (...)
        {
            std::cerr << "Unknown command error occurred!"
                      << std::endl;
        }
    }

    return 0;
}