#include "ECE_Buzzy.hpp"
#include "utils.hpp"
#include <iostream>

ECE_Buzzy::ECE_Buzzy()
{
    if (textureLoaded == false)
    {
        if (!texture.loadFromFile("graphics/Buzzy_blue.png"))
        {
            std::cout << "Failed to load texture\n";
        }
        textureLoaded = true;
    }
    setTexture(texture);
    setPosition(xLen / 2, 100);
    setScale(0.25, 0.25);
}

void ECE_Buzzy::move(float offsetX)
{
    auto spriteBounds = getGlobalBounds();
    auto spriteLeftBorder = spriteBounds.left + offsetX;
    auto spriteRightBorder = spriteBounds.left + spriteBounds.width + offsetX;
    // Implement the base Transformable::move, with some bounds checking

    if (spriteLeftBorder >= leftBound && spriteRightBorder <= rightBound)
    {
        Transformable::move(offsetX, 0);
    }
}
