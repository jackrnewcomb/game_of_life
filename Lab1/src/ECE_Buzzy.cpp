#include "ECE_Buzzy.hpp"
#include "utils.hpp"
#include <iostream>

ECE_Buzzy::ECE_Buzzy(sf::Texture &texture)
{
    // Set the texture with the input texture
    setTexture(texture);

    // Set the starting position to be in the upper middle
    setPosition(rightBound / 2, 100);

    // Set scale based on the image size
    setScale(0.25, 0.25);
}

void ECE_Buzzy::move(float offsetX)
{
    // Get current buzzy position information
    auto spriteBounds = getGlobalBounds();
    auto spriteLeftBorder = spriteBounds.left + offsetX;
    auto spriteRightBorder = spriteBounds.left + spriteBounds.width + offsetX;

    // Implement the base Transformable::move, with some bounds checking to ensure buzzy remains in the window
    if (spriteLeftBorder >= leftBound && spriteRightBorder <= rightBound)
    {
        Transformable::move(offsetX, 0);
    }
}
