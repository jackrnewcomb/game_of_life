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
    newCells_ = cells_;
}

void Grid::updateSEQ()
{
    int rows = cells_.size();
    int cols = cells_.at(0).size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            updateCell(i, j, rows, cols);
        }
    }
    cells_.swap(newCells_);
}

void Grid::updateCell(int i, int j, int rows, int cols)
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
                if (cells_[ni][nj]) // assuming bool or 0/1
                    livingNeighbors++;
            }
        }
    }

    // life giveth and life taketh away
    if (cells_.at(i).at(j) == true)
    {
        if (livingNeighbors != 2 && livingNeighbors != 3)
        {
            newCells_.at(i).at(j) = false;
        }
    }
    else
    {
        if (livingNeighbors == 3)
        {
            newCells_.at(i).at(j) = true;
        }
    }
}
void Grid::updateTHRD(int numThreads)
{
    int rows = cells_.size();
    int cols = cells_.at(0).size();

    auto worker = [&](int startRow, int endRow) {
        for (int i = startRow; i < endRow; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                updateCell(i, j, rows, cols);
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

    cells_.swap(newCells_);
}
void Grid::updateMP()
{
    int rows = cells_.size();
    int cols = cells_[0].size();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            updateCell(i, j, rows, cols);
        }
    }

    cells_.swap(newCells_);
}

bool Grid::randomStart()
{
    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(generator);
}
