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

    // Screens
    // 0 - Home
    sf::Sprite *backgroundSprite;
    Button *playBtn, *optionsBtn, *levelsBtn;

    // 1 - Play
    Ball *ball;

    void initVariables();
    void initWindow();
    void initTextures();

public:
    Game();
    ~Game();

    void initScreen(int screen);
    void destroyScreen(int screen);

    const bool isRunning() const;
    void poolEvents();

    void update();
    void render();
};

#endif
