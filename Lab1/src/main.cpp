// Include important C++ libraries here
#include "Ece_Buzzy.hpp"
#include "GameController.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
// #include <sstream>
//  #include <SFML/Audio.hpp>

int main()
{

    // Create a video mode object
    sf::VideoMode vm(rightBound, bottomBound); // Dimensions of the Start_Screen.png

    // Create and open a window for the game
    std::shared_ptr<sf::RenderWindow> window =
        std::make_shared<sf::RenderWindow>(vm, "Buzzy Defender", sf::Style::Default);

    while (window->isOpen())
    {
        // Create a texture to hold a graphic on the GPU
        sf::Texture textureBackground;

        // Load a graphic into the texture
        textureBackground.loadFromFile("graphics/Start_Screen.png");

        // Create a sprite
        sf::Sprite spriteBackground = sf::Sprite(textureBackground);

        // Draw our game scene here
        window->draw(spriteBackground);

        // Show everything we just drew
        window->display();

        GameController controller(window);

        bool playing = true;
        while (playing)
        {
            controller.update();
            if (controller.isGameFinished() || !window->isOpen())
            {
                playing = false;
            }
        }
    }

    return 0;
}
