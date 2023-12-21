// Standard includes
#include "Game.h"

// SFML includes
#include <SFML/Graphics.hpp>

#include "Board.h"
extern float W_WIDTH;
extern float W_HEIGHT;

// Constructor and destructor
Game::Game()
{
    initVariables();
    initWindow();
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
    // Clear the window with black color
    this->window->clear();

    // Render stuff
    this->board.draw(this->window);
    this->ball.draw(this->window);

    // Display everything that has been drawn
    this->window->display();
}