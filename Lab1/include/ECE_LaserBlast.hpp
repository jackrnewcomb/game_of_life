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

class ECE_LaserBlast : public sf::Sprite
{
  public:
    ECE_LaserBlast(sf::Texture &texture, float xPos, float yPos, bool isFriendly);
    void propagate();
    bool getTravelStatus();
    bool isFriendly();

  private:
    bool isTraveling{false};
    bool isFriendly_{false};
};
