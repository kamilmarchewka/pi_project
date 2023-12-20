#include <SFML/Graphics.hpp>
#include "Ball.h"

extern float W_WIDTH;
extern float W_HEIGHT;

Ball::Ball()
{
    this->initVariables();
    this->initShape();
}
Ball::~Ball() {}

void Ball::initVariables()
{
    this->radius = 15;
    this->posX = W_WIDTH / 2;
    this->posY = W_HEIGHT / 2;
}
void Ball::initShape()
{
    this->ball.setRadius(this->radius);
    this->ball.setPosition(sf::Vector2f(this->posX, this->posY));
    this->ball.setFillColor(sf::Color::Yellow);
}

void Ball::draw(sf::RenderTarget *target)
{
    target->draw(this->ball);
}
