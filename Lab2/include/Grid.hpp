/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 09/29/2025

Description:

Provides a class that handles the heavy computational work involved in updating cells based on the rules of the game.

*/

#pragma once

#include <iostream>
#include <omp.h>
#include <random>
#include <thread>
#include <vector>

class Grid
{
  public:
    /**
     * @brief Constructor
     * @param xLen: The number of elements (cells) contained in the X axis
     * @param yLen: The number of elements (cells) contained in the Y axis
     */
    Grid(int xLen, int yLen);

    /**
     * @brief Updates the cell located at coordinates (i,j)
     * @param i: The row indicator of the cell
     * @param j: The column indicator of the cell
     */
    void updateCell(int i, int j);

    /**
     * @brief Updates all cells sequentially using a single thread
     */
    void updateSEQ();

    /**
     * @brief Updates all cells using std::thread multi-threading
     * @param numThreads: The number of threads to use
     */
    void updateTHRD(int numThreads);

    /**
     * @brief Updates all cells using OpenMP
     */
    void updateMP();

    /**
     * @brief Getter
     * @returns Returns the cells_ array
     */
    std::vector<char> getCells()
    {
        return cells_;
    }

    /**
     * @brief Getter
     * @returns Returns the number of rows
     */
    int getRows()
    {
        return rows_;
    }

    /**
     * @brief Getter
     * @returns Returns the number of columns
     */
    int getCols()
    {
        return cols_;
    }

    /**
     * @brief An indexer. Since we're using a flattened, 1D vector to store cell status, this takes in a row and column
     * and provides the actual index of the cells_ vector
     * @param i: The desired row
     * @param j: The desired column
     * @returns Index given row and column
     */
    int index(int i, int j)
    {
        return i * cols_ + j;
    }

  private:
    /**
     * @brief RNG function that provides a "random" assignment to each cell to start
     * @returns A char describing status ("0" for dead, "1" for alive")
     */
    char randomStart();

    // The number of rows in the grid
    int rows_;

    // The number of columns in the grid
    int cols_;

    // The flattened 1D vector of cells
    std::vector<char> cells_;

    // The "next" vector after the update (required to avoid overlapping cell statuses)
    std::vector<char> newCells_;

    // Random Number Generator
    std::default_random_engine generator;
};
