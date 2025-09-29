#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <random>
#include <string>

int main(int argc, char *argv[])
{
    std::map<std::string, std::string> argMap; // maps arg types to their arg. Example: <"-t","SEQ">

    for (int i = 1; i < argc; i++)
    {

        std::string arg = argv[i];

        if (arg.find("-") != std::string::npos)
        {
            argMap[arg] = argv[i + 1];
        }
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
    long long accumulated_us = 0; // total time in microseconds
    auto start_time = std::chrono::steady_clock::now();
    // General execution loop. Each iteration represents a playthrough of the game
    while (game.isRunning())
    {
        auto start_update = std::chrono::steady_clock::now();
        if (argMap["-t"] == "SEQ")
        {
            grid->updateSEQ();
        }
        else if (argMap["-t"] == "THRD")
        {
            grid->updateTHRD(std::stoi(argMap["-n"]));
        }
        else if (argMap["-t"] == "OMP")
        {
            grid->updateMP();
        }
        auto end_update = std::chrono::steady_clock::now();
        accumulated_us += std::chrono::duration_cast<std::chrono::microseconds>(end_update - start_update).count();
        game.update();

        tracker++;

        if (tracker % 100 == 0)
        {
            std::cout << "100 generations took " << accumulated_us << " with style " << argMap["-t"] << "\n";
            accumulated_us = 0; // reset
        }
    }

    return 0;
}
