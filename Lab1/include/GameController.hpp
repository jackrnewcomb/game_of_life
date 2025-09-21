#pragma once

#include "ECE_Buzzy.hpp"
#include "ECE_Enemy.hpp"
#include "ECE_LaserBlast.hpp"
#include "SFML/Graphics.hpp"
#include "utils.hpp"
#include <list>

class GameController
{
  public:
    GameController(std::shared_ptr<sf::RenderWindow> window);
    bool update();
    void redraw();

  private:
    bool isRunning_{false};
    std::shared_ptr<sf::RenderWindow> window_;
    std::map<std::string, sf::Texture> textures_;
    ECE_Buzzy buzzy_;
    std::list<ECE_LaserBlast> lasers_;
    sf::Sprite background_;
    std::list<ECE_Enemy> enemies_;
};
