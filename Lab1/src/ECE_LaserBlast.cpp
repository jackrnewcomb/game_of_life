#include "ECE_LaserBlast.hpp"
#include "utils.hpp"
#include <iostream>

ECE_LaserBlast::ECE_LaserBlast(sf::Texture &texture, float xPos, float yPos, bool isFriendly)
{
    // Set the texture with the input texture
    setTexture(texture);

    // Set position with input position
    setPosition(xPos, yPos);

    // Set scale based on image size
    setScale(0.1, 0.1);

    // Set alignment based on input alignment
    isFriendly_ = isFriendly;

    // If the blast originated from an enemy...
    if (!isFriendly_)
    {
        // Rotate 180 degrees facing upwards
        setRotation(180);
    }
}

void ECE_LaserBlast::propagate()
{
    // If the blast came from buzzy, it should travel downwards toward the enemies
    if (isFriendly_)
    {
        move(0, buzzySpeed * 2);
    }
    // Otherwise, it should travel upwards toward buzzy
    else
    {
        move(0, -buzzySpeed * 2);
    }

    // Check if the laser exceeded the bounds of the window. If so...
    if (getPosition().y > bottomBound || getPosition().y < topBound)
    {
        // Set the bounds flag to false so it can be destructed by the game controller
        isInBounds_ = false;
    }
}

bool ECE_LaserBlast::isInBounds()
{
    return isInBounds_;
}

bool ECE_LaserBlast::isFriendly()
{
    return isFriendly_;
}
