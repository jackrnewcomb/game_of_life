#include "Grid.hpp"

Grid::Grid(int xLen, int yLen)
{

    rows_ = xLen;
    cols_ = yLen;

    cells_.resize(rows_ * cols_);
    newCells_.resize(rows_ * cols_);
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            cells_[index(i, j)] = randomStart();
        }
    }
}

void Grid::updateSEQ()
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            updateCell(i, j);
        }
    }
    cells_.swap(newCells_);
}

inline void Grid::updateCell(int i, int j)
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
            if (ni >= 0 && ni < rows_ && nj >= 0 && nj < cols_)
            {
                livingNeighbors += cells_[index(ni, nj)];
            }
        }
    }

    // life giveth and life taketh away
    int cur = cells_[index(i, j)];
    char &next = newCells_[index(i, j)];

    if (cur == 1)
    {
        next = (livingNeighbors == 2 || livingNeighbors == 3) ? 1 : 0;
    }
    else
    {
        next = (livingNeighbors == 3) ? 1 : 0;
    }
}
void Grid::updateTHRD(int numThreads)
{
    auto worker = [&](int startRow, int endRow) {
        for (int i = startRow; i < endRow; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
                updateCell(i, j);
            }
        }
    };

    std::vector<std::thread> threads;
    int chunk = rows_ / numThreads;
    for (int t = 0; t < numThreads; t++)
    {
        int start = t * chunk;
        int end = (t == numThreads - 1) ? rows_ : start + chunk;
        threads.emplace_back(worker, start, end);
    }
    for (auto &th : threads)
        th.join();

    cells_.swap(newCells_);
}
void Grid::updateOMP()
{

#pragma omp parallel for schedule(static)
    for (int idx = 0; idx < rows_ * cols_; idx++)
    {
        int i = idx / cols_;
        int j = idx % cols_;
        updateCell(i, j);
    }

    cells_.swap(newCells_);
}

char Grid::randomStart()
{
    std::uniform_int_distribution<int> distribution(0, 1);
    auto result = distribution(generator);
    return static_cast<char>(result);
}
