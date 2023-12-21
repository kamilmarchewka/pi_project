// Standard includes
#include "Game.h"

// SFML includes
#include <SFML/Graphics.hpp>

#include "Board.h"

extern float W_WIDTH;
extern float W_HEIGHT;
extern int GAME_STATE;

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initTextures();

    this->backgroundSprite.setTexture(*this->bgImageTexture);
    this->backgroundSprite.setPosition(sf::Vector2f(0, W_HEIGHT - this->backgroundSprite.getGlobalBounds().height));
}

Game::~Game()
{
    // Delete textures
    delete this->bgImageTexture;
    delete this->playBtnTexture;
    delete this->optionsBtnTexture;
    delete this->levelsBtnTexture;

    // Delete window
    delete this->window;
}

const bool Game::isRunning() const
{
    return this->window->isOpen();
}

void Game::initVariables()
{
    this->window = nullptr;
    this->videoMode.width = W_WIDTH;
    this->videoMode.height = W_HEIGHT;
    this->title = "MiniGolf";

    // Textures
    this->bgImageTexture = NULL;
    this->playBtnTexture = NULL;
    this->optionsBtnTexture = NULL;
    this->levelsBtnTexture = NULL;
}

void Game::initWindow()
{
    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text
    this->window = new sf::RenderWindow(this->videoMode, this->title, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60); // Set limit of 60fps
}

void Game::initTextures()
{
    this->bgImageTexture = new sf::Texture();
    this->bgImageTexture->loadFromFile("assets/v2/background.png");

    this->playBtnTexture = new sf::Texture();
    this->playBtnTexture->loadFromFile("assets/v2/play_btn.png");

    this->optionsBtnTexture = new sf::Texture();
    this->optionsBtnTexture->loadFromFile("assets/v2/ustawienia_btn.png");

    this->levelsBtnTexture = new sf::Texture();
    this->levelsBtnTexture->loadFromFile("assets/v2/poziomy_btn.png");
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
    // Clear the window with green color
    this->window->clear(sf::Color(168, 202, 89, 255));

    switch (GAME_STATE)
    {
    case 0: // Show home screen
        this->window->draw(this->backgroundSprite);
        break;

    case 1: // Show game screen with obard
        // Render stuff
        // this->board.draw(this->window);
        // this->ball.draw(this->window);
        break;
    }

    // Display everything that has been drawn
    this->window->display();
}