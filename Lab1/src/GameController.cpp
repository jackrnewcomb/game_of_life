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
    // Update the clock
    float deltaSeconds = clock_.restart().asSeconds();

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
            buzzies_.front().move(-kBuzzySpeed * deltaSeconds);
        }

        // If the user presses the right key, move buzzy right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            buzzies_.front().move(kBuzzySpeed * deltaSeconds);
        }

        // Slightly more complicated logic for laser firing. The spacePressedRecently_ member tracks whether the space
        // bar was just pressed; This prevents users from spamming lasers by holding down the space bar, and also solves
        // a bug in which even short taps of the space bar resulted in a large number of lasers being generated due to a
        // high framerate
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressedRecently_)
        {
            // Find the ideal x position of the laser (centered at buzzy)
            auto xPos = buzzies_.front().getPosition().x + buzzies_.front().getGlobalBounds().width / 2.0f;

            // Find the ideal y position of the laser (just under buzzy)
            auto yPos = buzzies_.front().getGlobalBounds().top + buzzies_.front().getGlobalBounds().height;

            // Add the laser to the lasers_ list
            lasers_.emplace_back(textures_["laser"], xPos, yPos, true);
        }

        // Update the aforementioned member to ensure no space bar spamming
        spacePressedRecently_ = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

        // For each enemy in the active enemies_ list...
        for (auto &enemy : enemies_)
        {
            // Update based on marching movement logic
            enemy.march(deltaSeconds);

            // Check if this enemy should fire a random laser blast. If so...
            if (enemy.randomBlast())
            {
                // Find the ideal x position of the laser (centered at the enemy)
                auto xPos = enemy.getPosition().x + enemy.getGlobalBounds().width / 2.0f;

                // Find the ideal y position of the laer (just above the enemy)
                auto yPos = enemy.getGlobalBounds().top;

                // Add the laser to the lasers_ list
                lasers_.emplace_back(textures_["laser"], xPos, yPos, false);
            }

            // Check a lose condition: Has any enemy made it to buzzy?
            if (enemy.getGlobalBounds().intersects(buzzies_.front().getGlobalBounds()))
            {
                // Reset the game
                isRunning_ = false;
                gameFinished_ = true;
            }
        }

        // This block will handle collision interactions between lasers and entities. For each laser...
        // (Need to use iterators to loop through this block because we are potentially erasing objects from the list,
        // and we need an iterator to do that)
        for (auto laser = lasers_.begin(); laser != lasers_.end();)
        {
            // Propagate laser movements
            laser->propagate(deltaSeconds);

            bool hit = false;

            // For each enemy in the active enemies_ list...
            // (Need to use iterators to loop through this block because we are potentially erasing objects from the
            // list, and we need an iterator to do that)
            for (auto enemy = enemies_.begin(); enemy != enemies_.end();)
            {
                // If the laser intersects with the enemy, and originated from buzzy...
                if (laser->getGlobalBounds().intersects(enemy->getGlobalBounds()) && laser->isFriendly())
                {
                    // Destroy the enemy and the laser
                    enemy = enemies_.erase(enemy);
                    laser = lasers_.erase(laser);
                    hit = true;
                    break;
                }
                // Otherwise move on to the next enemy in enemies_
                else
                {
                    ++enemy;
                }
            }

            // If we've hit something and destroyed the laser, we can't reference this laser anymore with introducing
            // bugs later. Move on to the next laser
            if (hit)
            {
                continue;
            }

            // Now we check if the laser hit buzzy
            if (laser->getGlobalBounds().intersects(buzzies_.front().getGlobalBounds()) && !laser->isFriendly())
            {
                // If this is the case, the game is over. Update isRunning_ and gameFinished_ accordingly
                isRunning_ = false;
                gameFinished_ = true;
            }

            // Finally, check if the laser left the bounds of the window. If so we can remove it from the active lasers_
            // list
            if (!laser->isInBounds())
            {
                laser = lasers_.erase(laser);
            }
            else
            {
                ++laser;
            }
        }

        // Check the win condition: Are the enemies all gone?
        if (enemies_.empty())
        {
            // The game is over, update isRunning_ and gameFinished_ accordingly
            isRunning_ = false;
            gameFinished_ = true;
        }

        // Redraw the map with new movements and entity updates
        redraw();
    }
}

void GameController::redraw()
{
    // First clear the previous drawing
    window_->clear();

    // Draw, in order, the background, buzzy, the enemies, and the lasers
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

    // Display the drawings
    window_->display();
}

bool GameController::isGameFinished()
{
    return gameFinished_;
}

void GameController::addEnemies()
{
    // Fill the rows with as many enemies as can fit
    int enemiesPerRow = (kRightBound / textures_["bulldog"].getSize().x);

    // A flag to flip enemy types
    bool enemyType = false;

    // A marching type enum
    MarchDirection marchType = MarchDirection::Left;

    // For each row...
    for (int row = 0; row < kEnemyRows; row++)
    {
        // For each enemy in that row...
        for (int enemy = 0; enemy < enemiesPerRow; enemy++)
        {
            // A ternary operator that says: If the last enemy was a bulldog, make the next enemy a tiger. Had
            // to static_cast to a float so the compiler knew the conversion was intentional

            enemyType
                ? enemies_.emplace_back(
                      textures_["bulldog"], static_cast<float>(textures_["bulldog"].getSize().x * enemy),
                      static_cast<float>(kBottomBound - textures_["bulldog"].getSize().y * row), marchType)
                : enemies_.emplace_back(textures_["tiger"], static_cast<float>(textures_["tiger"].getSize().x * enemy),
                                        static_cast<float>(kBottomBound - textures_["tiger"].getSize().y * row),
                                        marchType);

            // Flip the enemy type for the next enemy
            enemyType = !enemyType;
        }

        // Ensures every enemy in a row marches the same direction. Flips march type every row
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
