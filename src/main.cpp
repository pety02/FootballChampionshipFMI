#include "utils/ExceptionMessages.h"
#include <iostream>
#include "utils/CommandLineInterpreter.h"

int main()
{
    ChampionshipHistory history;
    AccountingManager accountingManager;
    Championship championship =
        Championship(TeamManager(), std::vector<Match>(), CURRENT_YEAR, accountingManager);

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

        // ---- manual parsing ----
        size_t pos = 0;

        // extract command (first token)
        while (pos < line.size() && line[pos] == ' ')
            ++pos;

        size_t start = pos;

        while (pos < line.size() && line[pos] != ' ')
            ++pos;

        std::string commandValue = line.substr(start, pos - start);

        Command cmd = parseCommand(commandValue);

        // extract arguments
        std::vector<std::string> args;

        while (pos < line.size())
        {
            // skip spaces
            while (pos < line.size() && line[pos] == ' ')
                ++pos;

            if (pos >= line.size())
                break;

            start = pos;

            while (pos < line.size() && line[pos] != ' ')
                ++pos;

            args.push_back(line.substr(start, pos - start));
        }

        // ---- exit handling ----
        if (commandValue == "exit")
        {
            if (!args.empty())
            {
                std::cout
                    << "EXIT command does not need any args. Do you want to exit the program anyway? Y/N\n> ";

                std::string answer;

                while (answer != "Y" && answer != "y" &&
                       answer != "N" && answer != "n")
                {
                    std::getline(std::cin, answer);
                }

                if (answer == "Y" || answer == "y")
                {
                    cli.execute(Command::EXIT, args);
                    return 0;
                }
            }
            else
            {
                cli.execute(Command::EXIT, args);
                return 0;
            }
        }

        // ---- command execution ----
        try
        {
            if (cmd != Command::EXIT)
            {
                cli.execute(cmd, args);
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Command Error: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Unknown command error occurred!" << std::endl;
        }
    }

    return 0;
}