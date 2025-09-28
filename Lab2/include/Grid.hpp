#pragma once

#include <random>
#include <thread>
#include <vector>
#include <omp.h>
#include <iostream>

class Grid
{
  public:
    Grid(int xLen, int yLen);
    void updateCell(int i, int j, int rows, int cols);
    void updateSEQ();
    void updateTHRD(int numThreads);
    void updateMP();
    std::vector<std::vector<bool>> getCells()
    {
        return cells_;
    }

  private:
    bool randomStart();
    std::vector<std::vector<bool>> cells_;
    std::vector<std::vector<bool>> newCells_;
    std::default_random_engine generator;
};
