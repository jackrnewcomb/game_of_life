#pragma once

#include <SFML/Graphics.hpp>

const int leftBound = 0;
const int rightBound = 1152;

const int topBound = 0;
const int bottomBound = 1030;

const int xLen = 1152;
const int yLen = 1030;

const double buzzySpeed = 0.1;

enum class MarchDirection
{
    Left,
    Right,
    Up
};
