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

void Grid::updateSEQ()
{
    auto cellsCopy = cells_;
    int rows = cellsCopy.size();
    int cols = cellsCopy.at(0).size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            updateCell(i, j, cellsCopy, rows, cols);
        }
    }
}

void Grid::updateCell(int i, int j, const std::vector<std::vector<bool>> &cellsCopy, int rows, int cols)
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
void Grid::updateTHRD(int numThreads)
{
    auto cellsCopy = cells_;
    int rows = cellsCopy.size();
    int cols = cellsCopy.at(0).size();

    auto worker = [&](int startRow, int endRow) {
        for (int i = startRow; i < endRow; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                updateCell(i, j, cellsCopy, rows, cols);
            }
        }
    };

    std::vector<std::thread> threads;
    int chunk = rows / numThreads;
    for (int t = 0; t < numThreads; t++)
    {
        int start = t * chunk;
        int end = (t == numThreads - 1) ? rows : start + chunk;
        threads.emplace_back(worker, start, end);
    }
    for (auto &th : threads)
        th.join();
}
void Grid::updateMP()
{
}

bool Grid::randomStart()
{
    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(generator);
}
