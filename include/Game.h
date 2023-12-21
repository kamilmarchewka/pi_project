#ifndef GAME_H
#define GAME_H

// Standard includes
#include <iostream>

// SFML includes
#include <SFML/Graphics.hpp>

// Game includes
#include "Board.h"
#include "Ball.h"
#include "Button.h"

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

    // Textures
    sf::Texture *bgImageTexture, *playBtnTexture, *optionsBtnTexture, *levelsBtnTexture;

    // Sprites
    sf::Sprite backgroundSprite;

    // Other Game objects
    // Board board;
    // Ball ball;

    void initVariables();
    void initWindow();
    void initTextures();

public:
    Game();
    ~Game();

    const bool isRunning() const;
    void poolEvents();

    void update();
    void render();
};

#endif
