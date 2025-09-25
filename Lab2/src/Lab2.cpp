#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <random>
#include <string>

int main(int argc, char *argv[])
{
    std::map<std::string, std::string> argMap; // maps arg types to their arg. Example: <"-t","SEQ">

    for (int i = 1; i < argc; i += 2)
    {
        std::string arg = argv[i];

        argMap[arg] = argv[i + 1];
    }

    if (argMap.find("-n") == argMap.end())
    {
        argMap["-n"] = std::to_string(8);
    }

    if (argMap.find("-c") == argMap.end())
    {
        argMap["-c"] = std::to_string(5);
    }

    if (argMap.find("-x") == argMap.end())
    {
        argMap["-x"] = std::to_string(800);
    }

    if (argMap.find("-y") == argMap.end())
    {
        argMap["-y"] = std::to_string(600);
    }

    if (argMap.find("-t") == argMap.end())
    {
        argMap["-t"] = "THRD";
    }

    // Testing

    auto xWindowSize = std::stoi(argMap["-x"]);
    auto yWindowSize = std::stoi(argMap["-y"]);
    auto cellSize = std::stoi(argMap["-c"]);

    Game game(xWindowSize, yWindowSize, cellSize);
    auto grid = game.getGrid();

    int tracker = 0;
    auto start_time = std::chrono::steady_clock::now();
    // General execution loop. Each iteration represents a playthrough of the game
    while (game.isRunning())
    {
        if (argMap["-t"] == "SEQ")
        {
            grid->updateSEQ();
        }
        else if (argMap["-t"] == "THRD")
        {
            grid->updateTHRD(std::stoi(argMap["-n"]));
        }
        game.update();

        tracker++;

        if (tracker % 100)
        {
            auto end_time = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end_time - start_time;
            start_time = std::chrono::steady_clock::now();
            std::cout << "100 generations took " << elapsed_seconds.count() << " with style " << argMap["-t"] << "\n";
        }
    }

    return 0;
}
