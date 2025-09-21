#include "ECE_Enemy.hpp"
#include "utils.hpp"
#include <iostream>

ECE_Enemy::ECE_Enemy(sf::Texture &texture, float xPos, float yPos, MarchDirection marchDirection)
{
    setTexture(texture);
    setPosition(xPos, yPos);
    marchDirection_ = marchDirection;
}

void ECE_Enemy::march()
{
    if (isAlive)
    {
        auto pos = getPosition();
        auto bounds = getGlobalBounds();

        switch (marchDirection_)
        {
        case MarchDirection::Left:
            move(-buzzySpeed / 2, 0);
            if (pos.x <= 0)
            {
                marchDirection_ = MarchDirection::Up;
            }
            break;

        case MarchDirection::Right:
            move(buzzySpeed / 2, 0);
            if (pos.x + bounds.width >= xLen)
            {
                marchDirection_ = MarchDirection::Up;
            }
            break;

        case MarchDirection::Up:
            move(0, -bounds.height);
            marchDirection_ = (pos.x <= 0) ? MarchDirection::Right : MarchDirection::Left;
            break;

        default:
            break;
        }
    }
}

bool ECE_Enemy::getSurvivalStatus()
{
    return isAlive;
}

bool ECE_Enemy::randomBlast()
{
    // Generate a random number between 0 and 100
    int randomNum = rand() % static_cast<int>(1e6);

    // todo: make this more elegant
    if (randomNum == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
