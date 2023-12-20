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

    sf::Vector2f ballPos;

    this->ball.setSize(sf::Vector2f(50, 50));
    this->ball.setFillColor(sf::Color::Green);
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
}

void Game::render()
{
    std::cout << "Window size:" << this->window->getSize().x << " " << this->window->getSize().y << "\n";
    // Clear the window with black color
    this->window->clear();

    // Render stuff
    this->board.draw(this->window);
    this->window->draw(this->ball);

    // Display everything that has been drawn
    this->window->display();
}