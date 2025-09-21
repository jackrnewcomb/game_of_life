/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 9/21/2025

Description:

Provides a "controller" for each game, delegating authority away from main. The GameController is responsible for
updating all entities in the game on a frame-to-frame basis.

*/

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
    bool isGameFinished();
    void addEnemies();

  private:
    bool spacePressedRecently_{false};
    bool isRunning_{false};
    std::shared_ptr<sf::RenderWindow> window_;
    std::map<std::string, sf::Texture> textures_;
    ECE_Buzzy buzzy_;
    std::list<ECE_LaserBlast> lasers_;
    sf::Sprite background_;
    std::list<ECE_Enemy> enemies_;
    bool gameFinished_{false};
};
