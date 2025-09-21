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
    ECE_Buzzy();
    void move(float offsetX);

  private:
    sf::Texture texture;
    bool textureLoaded{false};
};
