/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 9/21/2025

Description:

Provides utility constants and enums for use throughout the codebase. For example, const information about window size,
travel speeds, etc.

*/

#pragma once

// The left pixel bound of the window
const int kLeftBound = 0;

// The right pixel bound of the window
const int kRightBound = 1152;

// The top pixel bound of the window
const int kTopBound = 0;

// The bottom pixel bound of the window
const int kBottomBound = 1030;

// A default speed for buzzy based on play-testing
const float kBuzzySpeed = 200.0f;

// The odds of a random blast occuring for an enemy. Based on play-testing
const int kRandomBlastProbability = static_cast<int>(1e6);

const int kEnemyRows = 2; // Developer preference based on play-tests and performance

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
