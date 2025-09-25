#pragma once
#include <SFML/Graphics.hpp>

#include "Grid.hpp"

class Game
{
  public:
    Game(int xWin, int yWin, int cellSize);
    void update(int numThreads = 1);
    bool isRunning()
    {
        return isRunning_;
    }

  private:
    void redraw();
    std::shared_ptr<sf::VideoMode> vm_;

    std::shared_ptr<sf::RenderWindow> window_;

    std::map<std::string, sf::Texture> textures_;

    std::shared_ptr<Grid> grid_;

    std::vector<std::vector<sf::Sprite>> cells_; // feels wasteful, fix this

    bool isRunning_{true};
};
