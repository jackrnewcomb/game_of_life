#pragma once

#include <iostream>
#include <omp.h>
#include <random>
#include <thread>
#include <vector>

class Grid
{
  public:
    Grid(int xLen, int yLen);
    void updateCell(int i, int j);
    void updateSEQ();
    void updateTHRD(int numThreads);
    void updateMP();
    std::vector<char> getCells()
    {
        return cells_;
    }

    int getRows()
    {
        return rows_;
    }
    int getCols()
    {
        return cols_;
    }

    int index(int i, int j)
    {
        return i * cols_ + j;
    }

  private:
    char randomStart();
    int rows_;
    int cols_;
    std::vector<char> cells_;
    std::vector<char> newCells_;
    std::default_random_engine generator;
};
