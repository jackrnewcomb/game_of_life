#include "GameController.hpp"
#include <iostream>
GameController::GameController(std::shared_ptr<sf::RenderWindow> window)
{
    window_ = window;

    // load and store in the map
    textures_["blank"].loadFromFile("graphics/Blank.png");
    textures_["start"].loadFromFile("graphics/Start_Screen.png");
    textures_["laser"].loadFromFile("graphics/Laser_blast.png");
    textures_["bulldog"].loadFromFile("graphics/bulldog.png");
    textures_["tiger"].loadFromFile("graphics/clemson_tigers.png");
    textures_["buzzy"].loadFromFile("graphics/Buzzy_blue.png");

    // set initial background
    background_.setTexture(textures_["blank"]);

    // Add buzzy to the buzzies_ list
    buzzies_.emplace_back(textures_["buzzy"]);

    addEnemies();
}

void GameController::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window_->close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        isRunning_ = true;
    }

    if (isRunning_)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            buzzies_.front().move(-buzzySpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            buzzies_.front().move(buzzySpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressedRecently_)
        {

            auto xPos = buzzies_.front().getPosition().x + buzzies_.front().getGlobalBounds().width / 2.0;
            auto yPos = buzzies_.front().getGlobalBounds().top + buzzies_.front().getGlobalBounds().height;
            lasers_.emplace_back(textures_["laser"], xPos, yPos, true);
        }
        spacePressedRecently_ = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

        for (auto enemy = enemies_.begin(); enemy != enemies_.end();)
        {
            enemy->march();
            if (enemy->randomBlast())
            {
                auto xPos = enemy->getPosition().x + enemy->getGlobalBounds().width / 2.0;
                auto yPos = enemy->getGlobalBounds().top;
                lasers_.emplace_back(textures_["laser"], xPos, yPos, false);
            }

            ++enemy;
        }

        // --- Update lasers and handle collisions ---
        for (auto laser = lasers_.begin(); laser != lasers_.end();)
        {
            laser->propagate();

            bool hit = false;
            for (auto enemy = enemies_.begin(); enemy != enemies_.end();)
            {
                if (laser->getGlobalBounds().intersects(enemy->getGlobalBounds()) && laser->isFriendly())
                {
                    enemy = enemies_.erase(enemy);
                    hit = true;
                    break; // laser disappears after hitting first enemy
                }
                else
                {
                    ++enemy;
                }
            }

            if (laser->getGlobalBounds().intersects(buzzies_.front().getGlobalBounds()) && !laser->isFriendly())
            {
                isRunning_ = false;
                gameFinished_ = true;
            }

            if (hit || !laser->isInBounds())
                laser = lasers_.erase(laser);
            else
                ++laser;
        }

        if (enemies_.empty())
        {
            isRunning_ = false;
            gameFinished_ = true;
        }

        redraw();
    }
}

void GameController::redraw()
{
    window_->clear();
    window_->draw(background_);
    window_->draw(buzzies_.front());

    for (auto &enemy : enemies_)
    {
        window_->draw(enemy);
    }

    for (auto &laser : lasers_)
    {
        window_->draw(laser);
    }
    window_->display();
}

bool GameController::isGameFinished()
{
    return gameFinished_;
}

void GameController::addEnemies()
{
    // initialize enemies
    int rows = 3;                                                        // ?
    int enemiesPerRow = (rightBound / textures_["bulldog"].getSize().x); // just testing
    bool enemyType = false;                                              // flag to flip enemy types
    MarchDirection marchType = MarchDirection::Left;

    for (int row = 0; row < rows; row++)
    {
        for (int enemy = 0; enemy < enemiesPerRow; enemy++)
        {
            enemyType ? enemies_.emplace_back(textures_["bulldog"], textures_["bulldog"].getSize().x * enemy,
                                              bottomBound - textures_["bulldog"].getSize().y * row, marchType)
                      : enemies_.emplace_back(textures_["tiger"], textures_["tiger"].getSize().x * enemy,
                                              bottomBound - textures_["tiger"].getSize().y * row, marchType);
            enemyType = !enemyType;
        }

        if (marchType == MarchDirection::Left)
        {
            marchType = MarchDirection::Right;
        }
        else
        {
            marchType = MarchDirection::Left;
        }
    }
}
