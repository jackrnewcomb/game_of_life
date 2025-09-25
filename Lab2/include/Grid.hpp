#pragma once

#include <random>
#include <vector>

class Grid
{
  public:
    Grid(int xLen, int yLen);
    void update();
    std::vector<std::vector<bool>> getCells()
    {
        return cells_;
    }

  private:
    bool randomStart();
    std::vector<std::vector<bool>> cells_;
    std::default_random_engine generator;
};
