#include "Grid.hpp"

Grid::Grid(int xLen, int yLen)
{
    // Initialize row/column members
    rows_ = xLen;
    cols_ = yLen;

    // Set the size of cells_ and newCells_ to be the correct size of the grid
    cells_.resize(rows_ * cols_);
    newCells_.resize(rows_ * cols_);

    // For each cell...
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            // Assign a random start
            cells_[index(i, j)] = randomStart();
        }
    }
}

void Grid::updateSEQ()
{
    // For single threading, simply go through each cell and call updateCell()
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            updateCell(i, j);
        }
    }
    // Swap content so cells_ now holds the most up to date data
    cells_.swap(newCells_);
}

inline void Grid::updateCell(int i, int j)
{
    // Initialize a living neighbors counter
    int livingNeighbors = 0;

    // The goal of this block is to go through each neighbor of the given cell at i,j. So, for the row below, equal to,
    // and above the cell...
    for (int iDelta = -1; iDelta <= 1; iDelta++)
    {
        // And for each column left of, equal to, and right of the cell...
        for (int jDelta = -1; jDelta <= 1; jDelta++)
        {
            // If this is our cell (i,j), we can disregard
            if (iDelta == 0 && jDelta == 0)
            {
                continue;
            }

            // Get the absolute position within the grid of the cell we're checking so we can do bounds testing
            int ni = i + iDelta;
            int nj = j + jDelta;

            // Boundary check
            if (ni >= 0 && ni < rows_ && nj >= 0 && nj < cols_)
            {
                // If its within bounds, increment the living neighbors counter by the value of the cell (0 for dead, 1
                // for alive)
                livingNeighbors += cells_[index(ni, nj)];
            }
        }
    }

    // Get the current and next iterations of the cell
    int cur = cells_[index(i, j)];
    char &next = newCells_[index(i, j)];

    // If the cell is currently alive...
    if (cur == 1)
    {
        // Assign the next iteration of this cell to be alive if it has 2 or 3 living neighbors, and dead otherwise
        next = (livingNeighbors == 2 || livingNeighbors == 3) ? 1 : 0;
    }
    // If the cell is currently dead...
    else
    {
        // Assign the next iteration of this cell to be alive if it has 3 living neighbors, and dead otherwise
        next = (livingNeighbors == 3) ? 1 : 0;
    }
}
void Grid::updateTHRD(int numThreads)
{
    // Define a "worker", which specifies a task that a thread will execute
    auto worker = [&](int startRow, int endRow) {
        for (int i = startRow; i < endRow; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
                updateCell(i, j);
            }
        }
    };

    // Initialize the threads vector
    std::vector<std::thread> threads;

    // Define a chunking method, by which certain threads handle the update of certain rows.
    // This prevents threads from performing overlapping tasks
    int chunk = rows_ / numThreads;
    for (int thr = 0; thr < numThreads; thr++)
    {
        int start = thr * chunk;
        int end = (thr == numThreads - 1) ? rows_ : start + chunk;
        threads.emplace_back(worker, start, end);
    }
    for (auto &thr : threads)
    {
        thr.join();
    }
    // Swap content so cells_ now holds the most up to date data
    cells_.swap(newCells_);
}
void Grid::updateOMP()
{
// Tells the compiler to parallelize the for loop with multiple threads using openMP.
// schedule(static) ensures that iterations are divided into roughly even sized chunks, which is best for when
// iterations take roughly the same amount of time
#pragma omp parallel for schedule(static)
    for (int idx = 0; idx < rows_ * cols_; idx++)
    {
        openMpThreads_ = omp_get_num_threads();
        int i = idx / cols_;
        int j = idx % cols_;
        updateCell(i, j);
    }
    // Swap content so cells_ now holds the most up to date data
    cells_.swap(newCells_);
}

char Grid::randomStart()
{
    // Define the random generator
    std::uniform_int_distribution<int> distribution(0, 1);

    // Return a result (0 or 1)
    auto result = distribution(generator);
    return static_cast<char>(result);
}
