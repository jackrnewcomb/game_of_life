#include "ECE_Buzzy.hpp"
#include "GameController.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <memory>

int main()
{
    // Need to seed the random generator once at the beginning
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate the window. Make it a shared_ptr so the game controller can share ownership

    sf::VideoMode vm(kRightBound, kBottomBound); // Dimensions of the Start_Screen.png

    std::shared_ptr<sf::RenderWindow> window =
        std::make_shared<sf::RenderWindow>(vm, "Buzzy Defender", sf::Style::Default);

    // General execution loop. Each iteration represents a playthrough of the game
    while (window->isOpen())
    {
        // Create the starting screen
        sf::Texture textureStart;
        textureStart.loadFromFile("graphics/Start_Screen.png");
        sf::Sprite startScreen = sf::Sprite(textureStart);

        // Draw and display starting screen
        window->draw(startScreen);
        window->display();

        // Generate a GameController. This will go out of scope after this play-through is over
        GameController controller(window);

        // Begins the game loop
        bool playing = true;
        while (playing)
        {
            // Update the GameController, which controls all gameplay logic
            controller.update();

            // Check if the game finished, or the window was closed manually. If so, reset to the starting screen
            if (controller.isGameFinished() || !window->isOpen())
            {
                playing = false;
            }
        }
    }

    return 0;
}
