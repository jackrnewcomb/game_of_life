/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 9/21/2025

Description:

Provides an sf::Sprite inheritor for Buzzy, which includes movement logic, decision-making for
collision, laser firings, etc.

*/

#pragma once

#include <SFML/Graphics.hpp>

class ECE_Buzzy : public sf::Sprite
{
  public:
    /**
     * @brief Constructor. Sets attributes of the sprite like texture, scale, position, etc.
     * @param A sf::Texture&
     */
    ECE_Buzzy(sf::Texture &texture);

    /**
     * @brief Defines movement logic for buzzy
     * @param The movement offset
     */
    void move(float offsetX);
};
