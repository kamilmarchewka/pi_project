#include <iostream>
#include <cmath>
#include "Ball.h"
#include "Board.h"

// Constructor and destructor

Ball::Ball()
{
    this->initVariables();
    this->initShape();
}

Ball::~Ball()
{
}

// Modifiers
void Ball::move(float x, float y)
{
    // Change the value of the position vector
    this->position.x += x;
    this->position.y += y;

    // Set the position of the circle to the position vector
    this->circle.setPosition(this->position);

    if (!(fabs(this->velocity.x) < 0.01f))
    {
        /* if (this->velocity.x > 0)
             this->velocity.x -= 0.1;
         else if (this->velocity.x < 0)

             this->velocity.x += 0.1;
         */
        this->velocity.x *= 0.991; // szybkosc zmienia sie o 0.09% ale i tak jest problem "Normalizacji" czyli w jednym kierunku szybciej dobija do 0.1 i się zeruje
    }                              // przez co lekko zakręca, lecz i tak jest to dużo mniejsze niż w przypadku gdy zmieniamy o 0.1
    else
    {
        this->velocity.x = 0;
    }
    if (!(fabs(this->velocity.y) < 0.01f))
    {
        this->velocity.y *= 0.991;
        /*if (this->velocity.y > 0)
            this->velocity.y -= 0.1;
        else if (this->velocity.y < 0)
            this->velocity.y += 0.1;*/
    }
    else
    {
        this->velocity.y = 0;
    }
}
/**
 * Function that calculates the velocity of the ball
 * and its direction
 */
void Ball::shoot(sf::RenderWindow *window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->velocity.x == 0 && this->velocity.y == 0)
    { // Kiedy piłka się porusza nie można zmienić ruchu
        // Get the mouse position inside the game window
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePositionFloat = static_cast<sf::Vector2f>(mousePosition);
        // Calculate the velocity of the ball
        if (mousePositionFloat.x > this->position.x)
            this->velocity.x = -(mousePositionFloat.x - this->position.x) / 50.f;
        else if (mousePositionFloat.x < this->position.x)
            this->velocity.x = (this->position.x - mousePositionFloat.x) / 50.f;

        if (mousePositionFloat.y > this->position.y)
            this->velocity.y = -(mousePositionFloat.y - this->position.y) / 50.f;
        else if (mousePositionFloat.y < this->position.y)
            this->velocity.y = (this->position.y - mousePositionFloat.y) / 50.f;
    }
}
void Ball::boardCollision(Board *board)
{
    float ballLeftBorder = this->position.x;
    float ballRightBorder = this->position.x + this->radius;

    std::cout << "Right border: " << ballRightBorder << "\n";
    std::cout << "radius: " << this->radius << "\n";
    std::cout << "x pos : " << this->position.x << "\n";

    float boardLeftBorder = board->getPosition().x - (board->getSize().x / 2);
    float boardRightBorder = board->getPosition().x + (board->getSize().x / 2);

    std::cout << "borderrightborder: " << boardRightBorder << "\n";
    // Left wall
    if (ballLeftBorder <= boardLeftBorder)
    {
        this->position.x = boardLeftBorder + 0.5f;
        this->velocity.x *= -1;
    }
    else if (ballRightBorder + this->radius >= boardRightBorder)
    {
        this->position.x = boardRightBorder - (this->radius) - this->radius - 0.5f;
        this->velocity.x *= -1;
    }
}

// Functions
void Ball::initVariables()
{
    this->radius = 13;
    this->position = sf::Vector2f(200.f, 200.f);
    this->velocity = sf::Vector2f(0.f, 0.f);
}

void Ball::initShape()
{
    this->circle.setRadius(radius);
    this->circle.setPosition(this->position);
    this->circle.setFillColor(sf::Color(240, 234, 210, 255));
}

void Ball::update(sf::RenderWindow *window, Board *board)
{
    // Check if the left mouse button is pressed
    // If it is, call the shoot function
    this->shoot(window);
    // Update the position vector
    this->move(this->velocity.x, this->velocity.y);

    // Check collisions
    // Collision with board
    this->boardCollision(board);
}

void Ball::render(sf::RenderTarget *target)
{
    target->draw(this->circle);
}