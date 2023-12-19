#include <iostream>
#include <cmath>
#include "Ball.h"

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

    if (!(fabs(this->velocity.x) < 0.1f))
    {
        if (this->velocity.x > 0)
            this->velocity.x -= 0.1;
        else if (this->velocity.x < 0)
            this->velocity.x += 0.1;
    }
    else
    {
        this->velocity.x = 0;
    }
    if (!(fabs(this->velocity.y) < 0.1f))
    {

        if (this->velocity.y > 0)
            this->velocity.y -= 0.1;
        else if (this->velocity.y < 0)
            this->velocity.y += 0.1;
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Get the mouse position inside the game window
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePositionFloat = static_cast<sf::Vector2f>(mousePosition);
        // Calculate the velocity of the ball
        if (mousePositionFloat.x > this->position.x)
            this->velocity.x = -5.f;
        else if (mousePositionFloat.x < this->position.x)
            this->velocity.x = 5.f;

        if (mousePositionFloat.y > this->position.y)
            this->velocity.y = -5.f;
        else if (mousePositionFloat.y < this->position.y)
            this->velocity.y = 5.f;
    }
}

// Functions
void Ball::initVariables()
{
    this->position = sf::Vector2f(200.f, 200.f);
    this->velocity = sf::Vector2f(0.f, 0.f);
}

void Ball::initShape()
{
    this->circle.setRadius(10.f);
    this->circle.setPosition(this->position);
    this->circle.setFillColor(sf::Color::Red);
}

void Ball::update(sf::RenderWindow *window)
{
    // Check if the left mouse button is pressed
    // If it is, call the shoot function
    this->shoot(window);
    // Update the position vector
    this->move(this->velocity.x, this->velocity.y);
}

void Ball::render(sf::RenderTarget *target)
{
    target->draw(this->circle);
}
