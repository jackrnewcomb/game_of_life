/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 9/21/2025

Description:

Provides an sf::Sprite inheritor for laser blasts, which includes travel propagation logic, decision-making for
collision, etc.

*/

#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Inherits from sf::Sprite to define a custom LaserBlast class
 */
class ECE_LaserBlast : public sf::Sprite
{
  public:
    /**
     * @brief Constructor. Sets attributes of the sprite like texture, scale, rotation, etc., along with initializing
     * members
     * @param A sf::Texture&
     * @param The x position of the ECE_LaserBlast
     * @param The y position of the ECE_LaserBlast
     * @param A bool describing the originating side of the laser blast (true for Buzzy-aligned, false for
     * enemy-aligned)
     */
    ECE_LaserBlast(sf::Texture &texture, float xPos, float yPos, bool isFriendly);

    /**
     * @brief Defines movement logic for the laser blast
     */
    void propagate();

    /**
     * @brief Returns a bool based on the alignment of the laser blast
     * @returns True if the laser originated from buzzy, false if the laser originated from an enemy
     */
    bool isFriendly();

    /**
     * @brief Returns a bool describing whether the laser is within the bounds of the window
     * @returns True if in bounds, false otherwise
     */
    bool isInBounds();

  private:
    // Describes whether the laser object is within the bounds of the window
    bool isInBounds_{true};

    // Describes whether the laser originated from buzzy (true) or from an enemy (false)
    bool isFriendly_{false};
};
