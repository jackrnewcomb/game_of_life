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
