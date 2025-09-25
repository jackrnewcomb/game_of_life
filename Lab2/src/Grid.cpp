#include "Grid.hpp"

Grid::Grid(int xLen, int yLen)
{
    for (int i = 0; i < xLen; i++)
    {
        // Make a new column
        std::vector<bool> col;
        for (int j = 0; j < yLen; j++)
        {
            col.emplace_back(randomStart());
        }
        cells_.emplace_back(col);
    }
}

void Grid::update()
{
    auto cellsCopy = cells_;
    int rows = cellsCopy.size();
    int cols = cellsCopy.at(0).size();

    for (int i = 0; i < cellsCopy.size(); i++)
    {
        auto colCopy = cellsCopy.at(i);
        for (int j = 0; j < colCopy.size(); j++)
        {
            int livingNeighbors = 0;

            for (int iDelta = -1; iDelta <= 1; iDelta++)
            {
                for (int jDelta = -1; jDelta <= 1; jDelta++)
                {
                    if (iDelta == 0 && jDelta == 0)
                    {
                        continue;
                    }
                    int ni = i + iDelta;
                    int nj = j + jDelta;

                    // Boundary check
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols)
                    {
                        if (cellsCopy[ni][nj]) // assuming bool or 0/1
                            livingNeighbors++;
                    }
                }
            }

            // life giveth and life taketh away
            if (cellsCopy.at(i).at(j) == true)
            {
                if (livingNeighbors != 2 && livingNeighbors != 3)
                {
                    cells_.at(i).at(j) = false;
                }
            }
            else
            {
                if (livingNeighbors == 3)
                {
                    cells_.at(i).at(j) = true;
                }
            }
        }
    }
}

bool Grid::randomStart()
{
    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(generator);
}
