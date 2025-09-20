// Include important C++ libraries here
#include "Ece_Buzzy.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
// #include <sstream>
//  #include <SFML/Audio.hpp>

int main()
{
    // Create a video mode object
    sf::VideoMode vm(xLen, yLen); // Dimensions of the Start_Screen.png

    // Create and open a window for the game
    std::shared_ptr<sf::RenderWindow> window =
        std::make_shared<sf::RenderWindow>(vm, "Buzzy Defender", sf::Style::Default);

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

    // render blank screen
    sf::Texture textureBlank;
    textureBlank.loadFromFile("graphics/Blank.png");
    sf::Sprite spriteBlank;
    spriteBlank.setTexture(textureBlank);

    // buzzy
    ECE_Buzzy buzzy = ECE_Buzzy();

    bool gameStarted = false;

    while (window->isOpen())
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            gameStarted = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            buzzy.move(-0.2);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            buzzy.move(0.2);
        }

        if (gameStarted)
        {
            // update window
            window->clear();
            window->draw(spriteBlank);
            window->draw(buzzy);
            window->display();
        }
    }

    return 0;
}
