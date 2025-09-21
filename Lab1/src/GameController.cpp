#include "GameController.hpp"
#include <iostream>
GameController::GameController(std::shared_ptr<sf::RenderWindow> window)
{
    window_ = window; // Update our member window_ with the shared pointer to the window

    // Initialize the textures map with all the textures we'll need. This allows us to avoid re-loading textures, which
    // would impact performance
    textures_["blank"].loadFromFile("graphics/Blank.png");
    textures_["start"].loadFromFile("graphics/Start_Screen.png");
    textures_["laser"].loadFromFile("graphics/Laser_blast.png");
    textures_["bulldog"].loadFromFile("graphics/bulldog.png");
    textures_["tiger"].loadFromFile("graphics/clemson_tigers.png");
    textures_["buzzy"].loadFromFile("graphics/Buzzy_blue.png");

    // Set texture on the background
    background_.setTexture(textures_["blank"]);

    // Add buzzy to the buzzies_ list
    buzzies_.emplace_back(textures_["buzzy"]);

    // Add enemies to the field
    addEnemies();
}

void GameController::update()
{
    // If the user presses escape, end the window and game
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window_->close();
    }

    // If the user presses enter at the start screen, begin the game
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        isRunning_ = true;
    }

    // If the game has begun...
    if (isRunning_)
    {
        // If the user presses the left key, move buzzy left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            buzzies_.front().move(-buzzySpeed);
        }

        // If the user presses the right key, move buzzy right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            buzzies_.front().move(buzzySpeed);
        }

        // Slightly more complicated logic for laser firing. The spacePressedRecently_ member tracks whether the space
        // bar was just pressed; This prevents users from spamming lasers by holding down the space bar, and also solves
        // a bug in which even short taps of the space bar resulted in a large number of lasers being generated due to a
        // high framerate
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressedRecently_)
        {
            // Find the ideal x position of the laser (centered at buzzy)
            auto xPos = buzzies_.front().getPosition().x + buzzies_.front().getGlobalBounds().width / 2.0;

            // Find the ideal y position of the laser (just under buzzy)
            auto yPos = buzzies_.front().getGlobalBounds().top + buzzies_.front().getGlobalBounds().height;

            // Add the laser to the lasers_ list
            lasers_.emplace_back(textures_["laser"], xPos, yPos, true);
        }

        // Update the aforementioned member to ensure no space bar spamming
        spacePressedRecently_ = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

        // For each enemy in the active enemies_ list...
        for (auto enemy = enemies_.begin(); enemy != enemies_.end();)
        {
            // Update based on marching movement logic
            enemy->march();

            // Check if this enemy should fire a random laser blast. If so...
            if (enemy->randomBlast())
            {
                // Find the ideal x position of the laser (centered at the enemy)
                auto xPos = enemy->getPosition().x + enemy->getGlobalBounds().width / 2.0;

                // Find the ideal y position of the laer (just above the enemy)
                auto yPos = enemy->getGlobalBounds().top;

                // Add the laser to the lasers_ list
                lasers_.emplace_back(textures_["laser"], xPos, yPos, false);
            }

            ++enemy;
        }

        // This block will handle collision interactions between lasers and entities. For each laser...
        for (auto laser = lasers_.begin(); laser != lasers_.end();)
        {
            // Propagate laser movements
            laser->propagate();

            // For each enemy in the active enemies_ list...
            bool hit = false;
            for (auto enemy = enemies_.begin(); enemy != enemies_.end();)
            {
                // If the laser intersects with the enemy, and originated from buzzy...
                if (laser->getGlobalBounds().intersects(enemy->getGlobalBounds()) && laser->isFriendly())
                {
                    // Destroy the enemy
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
