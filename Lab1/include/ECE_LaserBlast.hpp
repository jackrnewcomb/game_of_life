#pragma once

#include <SFML/Graphics.hpp>

class ECE_LaserBlast : public sf::Sprite
{
  public:
    ECE_LaserBlast(sf::Texture &texture, float xPos, float yPos, bool isFriendly);
    void propagate();
    bool getTravelStatus();

  private:
    bool isTraveling{false};
    bool isFriendly_{false};
};
