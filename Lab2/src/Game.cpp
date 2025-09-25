#include "Game.hpp"

Game::Game(int xWin, int yWin, int cellSize)
{
    vm_ = std::make_shared<sf::VideoMode>(xWin, yWin);
    window_ = std::make_shared<sf::RenderWindow>(*vm_, "Game of Life", sf::Style::Default);
    grid_ = std::make_shared<Grid>(xWin / cellSize, yWin / cellSize);

    int xPixelsPerCell = cellSize;
    int yPixelsPerCell = cellSize;

    int runningX = 0;
    int runningY = 0;

    textures_["dead"].loadFromFile("graphics/dead.png");
    textures_["alive"].loadFromFile("graphics/alive.png");

    auto test = grid_->getCells();
    for (auto &col : test)
    {
        std::vector<sf::Sprite> spriteCol;
        for (auto &cell : col)
        {
            auto uh = sf::Sprite();

            cell ? uh.setTexture(textures_["alive"]) : uh.setTexture(textures_["dead"]);
            uh.setPosition(runningX, runningY);
            uh.setScale(xPixelsPerCell / 100.f, yPixelsPerCell / 100.f); // ????
            runningY += yPixelsPerCell;
            spriteCol.emplace_back(uh);
        }
        cells_.emplace_back(spriteCol);
        runningY = 0;
        runningX += xPixelsPerCell;
    }
}

void Game::update(int numThreads = 1)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        isRunning_ = false;
        window_->close();
    }

    grid_->update();

    auto test = grid_->getCells();
    for (int i = 0; i < cells_.size(); i++)
    {
        for (int j = 0; j < cells_.at(0).size(); j++)
        {
            test.at(i).at(j) ? cells_.at(i).at(j).setTexture(textures_["alive"])
                             : cells_.at(i).at(j).setTexture(textures_["dead"]);
        }
    }

    // Redraw the map with new movements and entity updates
    redraw();
}

void Game::redraw()
{
    // First clear the previous drawing
    window_->clear();

    for (auto &col : cells_)
    {
        for (auto cell : col)
        {
            window_->draw(cell);
        }
    }

    // Display the drawings
    window_->display();
}
