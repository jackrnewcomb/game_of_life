/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 9/21/2025

Description:

Provides an sf::Sprite inheritor for enemies, which includes marching logic, decision-making for
collision, laser firings, etc.

*/

#pragma once

#include "utils.hpp"
#include <SFML/Graphics.hpp>

/**
 * @brief Inherits from sf::Sprite to define a custom Enemy class
 */
class ECE_Enemy : public sf::Sprite
{
  public:
    /**
     * @brief Constructor. Sets attributes of the sprite like texture, position, etc., along with initializing
     * members
     * @param A sf::Texture&
     * @param The x position of the ECE_Enemy
     * @param The y position of the ECE_Enemy
     * @param An enum describing the initial marching direction of the ECE_Enemy (Left, Right, or Up)
     */
    ECE_Enemy(sf::Texture &texture, float xPos, float yPos, MarchDirection marchDirection);

    /**
     * @brief Defines marching (movement) logic for the enemy
     * @params A time delta to make movement framerate-agnostic
     */
    void march(float &deltaSeconds);

    /**
     * @brief Provides logic for determining if a random blast should be sent
     * @returns True if a blast should be sent at this timestep, false otherwise
     */
    bool randomBlast();

  private:
    // The current marching direction of the enemy (Right, Left, or Up)
    MarchDirection marchDirection_;
};
