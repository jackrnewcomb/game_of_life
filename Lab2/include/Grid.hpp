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
    void updateCell(int i, int j, int rows, int cols);
    void updateSEQ();
    void updateTHRD(int numThreads);
    void updateMP();
    std::vector<std::vector<char>> getCells()
    {
        return cells_;
    }

  private:
    char randomStart();
    std::vector<std::vector<char>> cells_;
    std::vector<std::vector<char>> newCells_;
    std::default_random_engine generator;
};
