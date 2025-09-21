/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 9/21/2025

Description:

Provides utility constants and enums for use throughout the codebase. For example, const information about window size,
travel speeds, etc.

*/

#pragma once

const int leftBound = 0;      // The left pixel bound of the window
const int rightBound = 1152;  // The right pixel bound of the window
const int topBound = 0;       // The top pixel bound of the window
const int bottomBound = 1030; // The bottom pixel bound of the window

const double buzzySpeed = 0.1; // A default speed for buzzy based on play-testing

/**
 * @brief Provides enum values for possible enemy marching direction
 * @return Left, Right, or Up
 */
enum class MarchDirection
{
    Left,
    Right,
    Up
};
