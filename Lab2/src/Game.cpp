#include "Game.hpp"

Game::Game(int xWin, int yWin, int cellSize)
{
    // Initialize members
    vm_ = std::make_shared<sf::VideoMode>(xWin, yWin);
    window_ = std::make_shared<sf::RenderWindow>(*vm_, "Game of Life", sf::Style::Default);
    cellSize_ = cellSize;
    grid_ = std::make_shared<Grid>(xWin / cellSize, yWin / cellSize);

    // Populate the textures_ map so we only have to load textures once
    textures_["dead"].loadFromFile("graphics/dead.png");
    textures_["alive"].loadFromFile("graphics/alive.png");
}

void Game::update()
{
    // If the user presses escape, close the window
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        isRunning_ = false;
        window_->close();
    }

    // Redraw the map with new movements and entity updates
    window_->clear();

    // Get the cells from our grid
    auto &cells = grid_->getCells();

    // For each row and column in the grid...
    for (int i = 0; i < grid_->getRows(); i++)
    {
        for (int j = 0; j < grid_->getCols(); j++)
        {
            // Make a sprite
            sf::Sprite sprite;

            // Set the texture to either alive (white) or dead (black) depending on whether the grid element is alive or
            // dead
            sprite.setTexture(cells[grid_->index(i, j)] == 1 ? textures_["alive"] : textures_["dead"]);

            // Set the position to be the location of the row and column, factoring in cell size
            sprite.setPosition(static_cast<float>(i * cellSize_), static_cast<float>(j * cellSize_));

            // Set the scale dependent on cell size and texture size
            sprite.setScale(cellSize_ / static_cast<float>(sprite.getTexture()->getSize().x),
                            cellSize_ / static_cast<float>(sprite.getTexture()->getSize().y));

            // Draw the sprite
            window_->draw(sprite);
        }
    }

    // Display after drawing all sprites
    window_->display();
}
