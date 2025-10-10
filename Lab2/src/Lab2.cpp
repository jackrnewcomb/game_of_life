#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <string>

const std::vector<std::string> kValidThreadModes = {"SEQ", "THRD", "OMP"};

bool sanitizeArgMap(std::map<std::string, std::string> &map)
{

    // Check for each pair in the map...
    for (auto &pair : map)
    {
        // All values should cast to an int besides the one paired to "-t"
        if (pair.first != "-t")
        {
            // Try casting it to an int
            try
            {
                auto test = std::stoi(pair.second);
            }
            // If it fails, print an error message and abort
            catch (...)
            {
                std::cerr << "Invalid input for " << pair.first << ": Value must cast to an int. Aborting!\n";
                return false;
            }
        }
        else
        {
            // If this is the value associated with "-t", find it in the kValidThreadModes vector
            auto iterator = std::find(kValidThreadModes.begin(), kValidThreadModes.end(), pair.second);

            // If it doesn't exist in that vector, print an error message to console and abort
            if (iterator == kValidThreadModes.end())
            {
                std::cerr << "Invalid input for " << pair.first << ": Value must be SEQ, THRD, or OMP. Aborting!\n";
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    // maps arg types to their arg
    std::map<std::string, std::string> argMap = {
        {"-n", "8"},   // default number of threads
        {"-c", "5"},   // default cell size
        {"-x", "800"}, // default x-axis width
        {"-y", "600"}, // default y-axis height
        {"-t", "THRD"} // default threading mode
    };

    // For each arg passed to the command line...
    for (int i = 1; i < argc; i++)
    {
        // Cast to a string
        std::string arg = argv[i];

        // If the arg contains a "-", the next arg should specify a value. Add it to the map and increment the argc
        // counter
        if (arg.find("-") != std::string::npos)
        {
            argMap[arg] = argv[i + 1];
            i++;
        }
        // If the arg doesn't contain "-", the user did not format their arguments correctly. Pass a message to the
        // console and move on
        else
        {
            std::cerr << "Unexpected input " << arg << ", ignoring...\n";
        }
    }

    // Check for clean inputs
    bool clean = sanitizeArgMap(argMap);
    if (!clean)
    {
        return 0;
    }

    // Initialize window sizes and cell sizes with the now-sanitized user input map
    auto xWindowSize = std::stoi(argMap["-x"]);
    auto yWindowSize = std::stoi(argMap["-y"]);
    auto cellSize = std::stoi(argMap["-c"]);

    // Initialize the Game and get a shared pointer to the grid
    Game game(xWindowSize, yWindowSize, cellSize);
    auto grid = game.getGrid();

    // Initialize some timing trackers so we can accurately report runtime statistics to the console
    int iteration = 0;
    long long accumulated_us = 0; // total time accumulated in microseconds

    // The update function being called will never change during runtime. We should generate a std::function to it now
    // so we don't have to check the map each frame
    std::function<void()> updateGrid;

    // Determine which update function to assign to updateGrid
    if (argMap["-t"] == "SEQ")
    {
        updateGrid = [&]() { grid->updateSEQ(); };
    }
    else if (argMap["-t"] == "THRD")
    {
        int n = std::stoi(argMap["-n"]);
        updateGrid = [&, n]() { grid->updateTHRD(n); };
    }
    else if (argMap["-t"] == "OMP")
    {
        updateGrid = [&]() { grid->updateOMP(); };
    }

    // General execution loop. Each iteration represents a frame
    while (game.isRunning())
    {
        // Update the grid first, grabbing the time elapsed during that update call so we can report accurate runtime
        // stats
        auto start_update = std::chrono::steady_clock::now();
        updateGrid();
        auto end_update = std::chrono::steady_clock::now();
        accumulated_us += std::chrono::duration_cast<std::chrono::microseconds>(end_update - start_update).count();

        // Update the visuals
        game.update();

        // Increment iteration
        iteration++;

        // Print runtime stats every 100 frames
        if (iteration % 100 == 0)
        {
            if (argMap["-t"] == "SEQ")
            {
                std::cout << "100 generations took " << accumulated_us << " microseconds with single thread." << "\n";
            }
            else if (argMap["-t"] == "THRD")
            {
                std::cout << "100 generations took " << accumulated_us << " microseconds with " << argMap["-n"]
                          << " std::threads." << "\n";
            }
            else if (argMap["-t"] == "OMP")
            {
                std::cout << "100 generations took " << accumulated_us << " microseconds with "
                          << grid->getOpenMpThreads() << " OMP threads." << "\n";
            }

            accumulated_us = 0; // reset accumulated_us
        }
    }

    return 0;
}
