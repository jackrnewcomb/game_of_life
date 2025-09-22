/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 9/21/2025

Description:

Provides a "controller" for each game, delegating authority away from main. The GameController is responsible for
updating all entities in the game on a frame-to-frame basis.

*/

#pragma once

#include "ECE_Buzzy.hpp"
#include "ECE_Enemy.hpp"
#include "ECE_LaserBlast.hpp"
#include "SFML/Graphics.hpp"
#include "utils.hpp"
#include <list>
#include <memory>

/**
 * @brief A class for managing game-play flow and interactions between entities
 */
class GameController
{
  public:
    /**
     * @brief Constructor. Initializes members and populates the texture map
     * @param A pointer to a sf::RenderWindow
     */
    GameController(std::shared_ptr<sf::RenderWindow> window);

    /**
     * @brief Generic update loop for gameplay. Handles all entity interactions, and calls relevant movement/laser
     * firing functions on objects
     */
    void update();

    /**
     * @brief Returns a bool that tracks whether the game has ended
     * @return True if the game has ended, false otherwise
     */
    bool isGameFinished();

  private:
    /**
     * @brief Called internally by the constructor to propagate the enemies_ list
     */
    void addEnemies();

    /**
     * @brief Redraws the background, entities, and lasers after the update loop has finished propagating movements and
     * laser firing
     */
    void redraw();

    // Used to ensure users can't spam lasers by holding down the space bar
    bool spacePressedRecently_{false};

    // Tracks whether the game is actively running
    bool isRunning_{false};

    // A shared pointer to the window
    std::shared_ptr<sf::RenderWindow> window_;

    // A map of string descriptors to textures. Ensures we don't waste time reloading textures
    std::map<std::string, sf::Texture> textures_;

    // Making this a std::list for conceptual symmetry with the other entities, but should only have 1 element
    std::list<ECE_Buzzy> buzzies_;

    // A list of all active lasers
    std::list<ECE_LaserBlast> lasers_;

    // The background sprite
    sf::Sprite background_;

    // A list of all active enemies_
    std::list<ECE_Enemy> enemies_;

    // Tracks whether the game has finished
    bool gameFinished_{false};

    // A clock to ensure the game is framerate-independent
    sf::Clock clock_;
};
