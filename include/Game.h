#ifndef GAME_H
#define GAME_H

// Standard includes
#include <iostream>

// SFML includes
#include <SFML/Graphics.hpp>

// Game includes
#include "Board.h"

/**
 * Game class
 * Renders the game and handles the game loop
 * handles user input, updates the game and renders the game
 */
class Game
{
private:
    // Variables
    sf::RenderWindow *window; // Pointer to a window object
    sf::VideoMode videoMode;  // Video mode object, holds width and height of the window
    std::string title;        // Title of the window
    // Variable for holding sfml events
    sf::Event event;

    // Other objects
    Board board;
    sf::RectangleShape ball;

    // Functions
    void initVariables();
    void initWindow();

public:
    // Constructor and destructor
    Game();
    ~Game();

    // Accessors
    const bool isRunning() const;

    // Modifiers

    // Functions
    void poolEvents();
    void update();
    void render();
};

#endif
