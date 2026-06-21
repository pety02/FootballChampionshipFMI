#include <ExceptionMessages.h>
#include <iostream>
#include "utils/CommandLineInterpreter.h"
#include <sstream>

int main()
{
    ChampionshipHistory history;
    AccountingManager accountingManager;
    Championship championship = Championship(TeamManager(), std::vector<Match>(), CURRENT_YEAR, accountingManager);

    CommandLineInterpreter cli(history, championship);
    history.addChampionship(championship);

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

        Command cmd = parseCommand(commandValue);

        std::vector<std::string> args;
        std::string arg;

        while (ss >> arg)
        {
            args.push_back(arg);
        }

        if (commandValue == "exit") {
            if(!args.empty()) {
                std::cout << "EXIT command does not need any args. Do you want to exit the program anyway? Y/N\n> ";
                std::string answer;
                while(answer != "Y" && answer != "y" && answer != "N" && answer != "n") {
                    std::getline(std::cin, answer);
                }
                if(answer == "Y" || answer == "y") {
                    cli.execute(Command::EXIT, args);
                    return 0;
                }
            } else {
                cli.execute(Command::EXIT, args);
                return 0;
            }
        }

        try
        {
            if(cmd != Command::EXIT) {
                cli.execute(cmd, args);
            }
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