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

class ECE_Enemy : public sf::Sprite
{
  public:
    ECE_Enemy(sf::Texture &texture, float xPos, float yPos, MarchDirection marchDirection);
    void march();
    bool getSurvivalStatus();
    bool randomBlast();

  private:
    bool isAlive{true};
    MarchDirection marchDirection_;
};
