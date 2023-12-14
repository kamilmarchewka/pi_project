#include <iostream>
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
}
/**
 * Function that calculates the velocity of the ball
 * and its direction
 */
void Ball::shoot(sf::RenderWindow *window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
    }
}

// Functions
void Ball::initVariables()
{
    this->position = sf::Vector2f(100.f, 100.f);
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
    // this->move(this->velocity.x, this->velocity.y);
    // Set the position of the circle to the position vector
    this->circle.setPosition(this->position);
}

void Ball::render(sf::RenderTarget *target)
{
    target->draw(this->circle);
}
