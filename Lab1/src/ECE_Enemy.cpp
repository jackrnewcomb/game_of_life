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

void ECE_Enemy::march(float &deltaSeconds)
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
        move(-kBuzzySpeed * deltaSeconds / 2.0f, 0);

        // If we hit the wall, set movement direction to Up
        if (pos.x <= 0)
        {
            marchDirection_ = MarchDirection::Up;
        }
        break;

    // If we are marching right...
    case MarchDirection::Right:
        // Move right, at half buzzy's speed
        move(kBuzzySpeed * deltaSeconds / 2.0f, 0);

        // If we hit the wall, set movement direction to Up
        if (pos.x + bounds.width >= kRightBound)
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

bool ECE_Enemy::randomBlast(float &deltaSeconds)
{
    // Randomization logic for enemy firing. Basically, pick a random float between 0 and 1 (std::rand() generates, then
    // divide by the max possible randomly generated value). Then check if thats less than our firing probability. The
    // deltaSeconds factor is also included to ensure framerate agnosticism
    if (static_cast<float>(std::rand()) / RAND_MAX < kFireChancePerSecond * deltaSeconds)
    {
        return true;
    }

    return false;
}
