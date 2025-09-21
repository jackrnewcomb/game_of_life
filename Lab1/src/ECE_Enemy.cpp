#include "ECE_Enemy.hpp"
#include "utils.hpp"
#include <iostream>

ECE_Enemy::ECE_Enemy(sf::Texture &texture, float xPos, float yPos, MarchDirection marchDirection)
{
    // Set the texture with the input texture
    setTexture(texture);

    // Set position with input position
    setPosition(xPos, yPos);

    // Set marching direction with input marching direction
    marchDirection_ = marchDirection;
}

void ECE_Enemy::march()
{
    // Get the current position and global rectangle bounds of the enemy
    auto pos = getPosition();
    auto bounds = getGlobalBounds();

    // Depending on which way its marching...
    switch (marchDirection_)
    {
    // If we are marching left...
    case MarchDirection::Left:
        // Move left, at half buzzy's speed
        move(-buzzySpeed / 2, 0);

        // If we hit the wall, set movement direction to Up
        if (pos.x <= 0)
        {
            marchDirection_ = MarchDirection::Up;
        }
        break;

    // If we are marching right...
    case MarchDirection::Right:
        // Move right, at half buzzy's speed
        move(buzzySpeed / 2, 0);

        // If we hit the wall, set movement direction to Up
        if (pos.x + bounds.width >= rightBound)
        {
            marchDirection_ = MarchDirection::Up;
        }
        break;

    // If we are moving up
    case MarchDirection::Up:
        // Just "snap" up by one row: Slow movement up negatively affects the marching formation
        move(0, -bounds.height);

        // A ternary operator that says: If we just hit the left wall, move right. Otherwise, move left.
        marchDirection_ = (pos.x <= 0) ? MarchDirection::Right : MarchDirection::Left;
        break;
    }
}

bool ECE_Enemy::randomBlast()
{
    // Generate a random number between 0 and the blast probability int
    int randomNum = rand() % randomBlastProbability;

    // Blast if the randomly generated number is 0
    if (randomNum == 0)
    {
        return true;
    }
    // Otherwise, don't blast
    else
    {
        return false;
    }
}
