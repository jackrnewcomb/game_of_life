#include "ECE_LaserBlast.hpp"
#include "utils.hpp"
#include <iostream>

ECE_LaserBlast::ECE_LaserBlast(sf::Texture &texture, float xPos, float yPos, bool isFriendly)
{
    setTexture(texture);
    setPosition(xPos, yPos);
    setScale(0.1, 0.1);
    isTraveling = true;
    isFriendly_ = isFriendly;

    if (!isFriendly_)
    {
        setRotation(180);
    }
}

void ECE_LaserBlast::propagate()
{
    if (isTraveling)
    {
        if (isFriendly_)
        {
            move(0, 0.2);
        }
        else
        {
            move(0, -0.2);
        }

        if (getPosition().y > bottomBound || getPosition().y < topBound)
        {
            isTraveling = false; // mark as finished
        }
    }
}

bool ECE_LaserBlast::getTravelStatus()
{
    return isTraveling;
}

bool ECE_LaserBlast::isFriendly()
{
    return isFriendly_;
}
