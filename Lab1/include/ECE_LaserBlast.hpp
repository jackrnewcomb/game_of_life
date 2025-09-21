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
    bool getTravelStatus();
    bool isFriendly();

  private:
    bool isTraveling{false};
    bool isFriendly_{false};
};
