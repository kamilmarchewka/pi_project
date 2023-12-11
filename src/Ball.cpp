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

// Functions
void Ball::initVariables()
{
    this->position = sf::Vector2f(10.f, 10.f);
    this->velocity = sf::Vector2f(5.f, 5.f);
}

void Ball::initShape()
{
    this->circle.setRadius(10.f);
    this->circle.setPosition(this->position);
    this->circle.setFillColor(sf::Color::Red);
}

void Ball::update()
{
}

void Ball::render(sf::RenderTarget *target)
{
    target->draw(this->circle);
}
