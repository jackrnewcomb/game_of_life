#include "GameController.hpp"

GameController::GameController(std::shared_ptr<sf::RenderWindow> window)
{
    window_ = window;
}
bool GameController::Update()
{

    return true;
}
void GameController::setIsRunning(const bool &update)
{
    isRunning_ = update;
}
