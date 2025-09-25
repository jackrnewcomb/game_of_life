#include "Game.hpp"

Game::Game(int xWin, int yWin, int cellSize)
{
    vm_ = std::make_shared<sf::VideoMode>(xWin, yWin);
    window_ = std::make_shared<sf::RenderWindow>(*vm_, "Game of Life", sf::Style::Default);
    cellSize_ = cellSize;
    grid_ = std::make_shared<Grid>(xWin / cellSize, yWin / cellSize);

    int xPixelsPerCell = cellSize;
    int yPixelsPerCell = cellSize;

    int runningX = 0;
    int runningY = 0;

    textures_["dead"].loadFromFile("graphics/dead.png");
    textures_["alive"].loadFromFile("graphics/alive.png");
}

void Game::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        isRunning_ = false;
        window_->close();
    }

    // Redraw the map with new movements and entity updates
    window_->clear();

    auto &cells = grid_->getCells();
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[i].size(); j++)
        {
            sf::Sprite sprite;
            sprite.setTexture(cells[i][j] ? textures_["alive"] : textures_["dead"]);
            sprite.setPosition(i * cellSize_, j * cellSize_);
            sprite.setScale(cellSize_ / 100.f, cellSize_ / 100.f); //???
            window_->draw(sprite);
        }
    }

    window_->display();
}
