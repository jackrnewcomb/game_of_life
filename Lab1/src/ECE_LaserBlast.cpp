#include "ECE_LaserBlast.hpp"
#include "utils.hpp"
#include <iostream>

ECE_LaserBlast::ECE_LaserBlast(sf::Texture &texture, float xPos, float yPos, bool isFriendly)
{
    setTexture(texture);
    setPosition(xPos, yPos);
    setScale(0.1, 0.1);
    isFriendly_ = isFriendly;

    if (!isFriendly_)
    {
        setRotation(180);
    }
}

void ECE_LaserBlast::propagate()
{

    if (isFriendly_)
    {
        move(0, buzzySpeed * 2);
    }
    else
    {
        move(0, -buzzySpeed * 2);
    }

    if (getPosition().y > bottomBound || getPosition().y < topBound)
    {
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
