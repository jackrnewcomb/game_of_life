#pragma once

#include <SFML/Graphics.hpp>

class ECE_LaserBlast : public sf::Sprite
{
  public:
    ECE_LaserBlast();
    void fire(float xPos, float yPos);
    void propagate();
    bool getTravelStatus();

  private:
    sf::Texture texture;
    bool textureLoaded{false};
    bool isTraveling{false};
};
