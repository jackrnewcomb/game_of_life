#pragma once

#include "SFML/Graphics.hpp"

class GameController
{
  public:
    GameController(std::shared_ptr<sf::RenderWindow> window);
    bool Update();
    void setIsRunning(const bool &update);

  private:
    bool isRunning_{false};
    std::shared_ptr<sf::RenderWindow> window_;
};
