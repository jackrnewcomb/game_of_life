#include "GameController.hpp"

GameController::GameController(std::shared_ptr<sf::RenderWindow> window)
{
    window_ = window;

    // load and store in the map
    textures_["blank"].loadFromFile("graphics/Blank.png");
    textures_["start"].loadFromFile("graphics/Start_Screen.png");
    textures_["laser"].loadFromFile("graphics/Laser_blast.png");
    textures_["bulldog"].loadFromFile("graphics/bulldog.png");
    textures_["tiger"].loadFromFile("graphics/clemson_tigers.png");

    // set initial background
    background_.setTexture(textures_["blank"]);
}

bool GameController::update()
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
            buzzy_.move(-0.2);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            buzzy_.move(0.2);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            auto xPos = buzzy_.getPosition().x + buzzy_.getGlobalBounds().width / 2.0;
            auto yPos = buzzy_.getGlobalBounds().top + buzzy_.getGlobalBounds().height;
            lasers_.emplace_back(textures_["laser"], xPos, yPos, true);
        }

        // Physics propagation
        for (auto laser = lasers_.begin(); laser != lasers_.end();)
        {
            laser->propagate();

            if (!laser->getTravelStatus())
            {
                laser = lasers_.erase(laser);
            }
            else
            {
                ++laser;
            }
        }
        redraw();
    }
    return true;
}
void GameController::setIsRunning(const bool &isRunning)
{
    isRunning_ = isRunning;
}

void GameController::redraw()
{
    window_->clear();
    window_->draw(background_);
    window_->draw(buzzy_);

    for (auto &laser : lasers_)
    {
        window_->draw(laser);
    }
    window_->display();
}
