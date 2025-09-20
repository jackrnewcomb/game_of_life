#include "ECE_LaserBlast.hpp"
#include "utils.hpp"
#include <iostream>

ECE_LaserBlast::ECE_LaserBlast()
{
    if (textureLoaded == false)
    {
        if (!texture.loadFromFile("graphics/Laser_blast.png"))
        {
            std::cout << "Failed to load texture\n";
        }
        textureLoaded = true;
    }
    setTexture(texture);
    // setPosition(xLen / 2, 100);
    setScale(0.25, 0.25);
}

void ECE_LaserBlast::fire(float xPos, float yPos)
{
    setPosition(xPos, yPos);
    isTraveling = true;
}

void ECE_LaserBlast::propagate()
{
    if (isTraveling)
    {
        move(0, -0.2);
    }
}

bool ECE_LaserBlast::getTravelStatus()
{
    return isTraveling;
}
