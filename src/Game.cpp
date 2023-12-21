// Standard includes
#include "Game.h"

// SFML includes
#include <SFML/Graphics.hpp>

#include "Board.h"
extern float W_WIDTH;
extern float W_HEIGHT;
extern int GAME_STATE;

// Constructor and destructor
Game::Game()
{
    initVariables();
    initWindow();

    this->bgImageTexture.loadFromFile("assets/v2/background.png");

    this->backgroundSprite.setTexture(this->bgImageTexture);
    this->backgroundSprite.setPosition(sf::Vector2f(0, W_HEIGHT - this->backgroundSprite.getGlobalBounds().height));
}

Game::~Game()
{
    delete this->window;
}

// Accessors
const bool Game::isRunning() const
{
    return this->window->isOpen();
}

// Modifiers
// Functions

void Game::initVariables()
{
    this->window = nullptr;
    this->videoMode.width = W_WIDTH;
    this->videoMode.height = W_HEIGHT;
    this->title = "MiniGolf";
}

void Game::initWindow()
{
    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text
    this->window = new sf::RenderWindow(this->videoMode, this->title, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60); // Set limit of 60fps
}

void Game::poolEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    this->poolEvents();

    this->ball.update(this->window, &this->board);
}

void Game::render()
{
    // Clear the window with green color
    this->window->clear(sf::Color(168, 202, 89, 255));

    switch (GAME_STATE)
    {
    case 0: // Show home screen
        this->window->draw(this->backgroundSprite);
        break;

    case 1: // Show game screen with obard
        // Render stuff
        this->board.draw(this->window);
        this->ball.draw(this->window);
        break;
    }

    // Display everything that has been drawn
    this->window->display();
}