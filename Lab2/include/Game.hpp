#pragma once
#include <SFML/Graphics.hpp>

#include "Grid.hpp"

class Game
{
  public:
    Game(int xWin, int yWin, int cellSize);
    void update();
    bool isRunning()
    {
        return isRunning_;
    }

    std::shared_ptr<Grid> getGrid()
    {
        return grid_;
    }

  private:
    std::shared_ptr<sf::VideoMode> vm_;

    std::shared_ptr<sf::RenderWindow> window_;

    std::map<std::string, sf::Texture> textures_;

    std::shared_ptr<Grid> grid_;

    int cellSize_;

    bool isRunning_{true};
};
