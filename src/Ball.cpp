#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Board.h"

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
    this->posX = W_WIDTH / 2;
    this->posY = W_HEIGHT / 2;
    this->velocityX = 0;
    this->velocityY = 0;
}
void Ball::initShape()
{
    this->texture.loadFromFile("assets/v2/ball_white.png");
    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture);

    this->sprite.setOrigin(sf::Vector2f(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f));
    this->sprite.setPosition(sf::Vector2f(this->posX, this->posY));
    // this->sprite.setScale(sf::Vector2f(.95f, .95f));
}

sf::Vector2f Ball::getPosition()
{
    return this->sprite.getGlobalBounds().getPosition();
};
sf::Vector2f Ball::getSize()
{
    return this->sprite.getGlobalBounds().getSize();
}

void Ball::setVelocity(sf::WindowBase *window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->velocityX == 0 && this->velocityY == 0)
    { // Kiedy piłka się porusza nie można zmienić ruchu
        // Get the mouse position inside the game window
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePositionFloat = static_cast<sf::Vector2f>(mousePosition);
        // Calculate the velocity of the ball
        if (mousePositionFloat.x > this->posX)
            this->velocityX = -(mousePositionFloat.x - this->posX) / 50.f;
        else if (mousePositionFloat.x < this->posX)
            this->velocityX = (this->posX - mousePositionFloat.x) / 50.f;

        if (mousePositionFloat.y > this->posY)
            this->velocityY = -(mousePositionFloat.y - this->posY) / 50.f;
        else if (mousePositionFloat.y < this->posY)
            this->velocityY = (this->posY - mousePositionFloat.y) / 50.f;
    }
}
void Ball::changePosition(float velX, float velY)
{
    // Change the value of the position vector
    this->posX += velX;
    this->posY += velY;

    // Set the position of the circle to the position vector
    this->sprite.setPosition(sf::Vector2f(this->posX, this->posY));

    if (!(fabs(this->velocityX) < 0.05f))
    {
        this->velocityX *= 0.991; // szybkosc zmienia sie o 0.09% ale i tak jest problem "Normalizacji" czyli w jednym kierunku szybciej dobija do 0.1 i się zeruje
    }                             // przez co lekko zakręca, lecz i tak jest to dużo mniejsze niż w przypadku gdy zmieniamy o 0.1
    else
    {
        this->velocityX = 0;
    }
    if (!(fabs(this->velocityY) < 0.05f))
    {
        this->velocityY *= 0.991;
    }
    else
    {
        this->velocityY = 0;
    }
}
void Ball::checkBoardCollision(Board *board)
{
    float boardLeft = board->getPosition().x + board->getBorderThickness();
    float boardRight = board->getPosition().x + board->getSize().x - board->getBorderThickness();
    float boardTop = board->getPosition().y + board->getBorderThickness();
    float boardBottom = board->getPosition().y + board->getSize().y - board->getBorderThickness();

    float ballLeft = this->getPosition().x;
    float ballRight = this->getPosition().x + this->getSize().x;
    float ballTop = this->getPosition().y;
    float ballBottom = this->getPosition().y + this->getSize().y;

    if (ballLeft <= boardLeft)
    {
        this->velocityX *= -1;
        this->posX = boardLeft + this->getSize().x / 2.f;
    }
    else if (ballRight >= boardRight)
    {
        this->velocityX *= -1;
        this->posX = boardRight - this->getSize().x / 2.f;
    }

    if (ballTop <= boardTop)
    {
        this->velocityY *= -1;
        this->posY = boardTop + this->getSize().y / 2.f;
    }
    else if (ballBottom >= boardBottom)
    {
        this->velocityY *= -1;
        this->posY = boardBottom - this->getSize().y / 2.f;
    }
}

void Ball::update(sf::WindowBase *window, Board *board)
{
    this->setVelocity(window);
    this->changePosition(this->velocityX, this->velocityY);
    // this->checkBoardCollision(board);
}
void Ball::draw(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}
