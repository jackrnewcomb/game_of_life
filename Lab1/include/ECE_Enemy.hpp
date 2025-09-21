#pragma once

#include "utils.hpp"
#include <SFML/Graphics.hpp>

class ECE_Enemy : public sf::Sprite
{
  public:
    ECE_Enemy(sf::Texture &texture, float xPos, float yPos, MarchDirection marchDirection);
    void march();
    bool getSurvivalStatus();

  private:
    bool isAlive{true};
    MarchDirection marchDirection_;
};
