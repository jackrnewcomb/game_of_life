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
    Grid grid(xWindowSize / cellSize, yWindowSize / cellSize);

    // General execution loop. Each iteration represents a playthrough of the game
    while (game.isRunning())
    {
        grid.update();
        game.update();
    }

    return 0;
}
