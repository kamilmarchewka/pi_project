#include <iostream>
#include <math.h>
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
    this->size = 20;
    this->posX = W_WIDTH / 2;
    this->posY = W_HEIGHT / 2;
    this->velocityX = 0;
    this->velocityY = 0;
}
void Ball::initShape()
{
    this->ball.setSize(sf::Vector2f(this->size, this->size));
    this->ball.setOrigin(sf::Vector2f(this->size / 2.f, this->size / 2.f));
    this->ball.setPosition(sf::Vector2f(this->posX, this->posY));
    this->ball.setFillColor(sf::Color::Yellow);
}

void Ball::setVelocity(sf::WindowBase *window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->velocityX == 0 && this->velocityY == 0)
    {
        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
        // std::cout << "Mouse pos: " << mousePosition.x << " " << mousePosition.y << "\n";

        if (mousePosition.x < this->posX)
            this->velocityX = (this->posX - mousePosition.x) / 100.f;
        else if (mousePosition.x > this->posX)
            this->velocityX = (mousePosition.x - this->posX) / 100.f;

        if (mousePosition.y < this->posY)
            this->velocityY = (this->posY - mousePosition.y) / 100.f;
        else if (mousePosition.y > this->posY)
            this->velocityY = (mousePosition.y - this->posY) / 100.f;

        std::cout << "Ball position: " << this->posX << " " << this->posY << "\n";
        std::cout << "Mouse position: " << mousePosition.x << " " << mousePosition.y << "\n";
        std::cout << "Velocity: " << velocityX << " " << velocityY << "\n";
    }
}
void Ball::changePosition(float velX, float velY)
{
    // this->posX += velX;
    // this->posY += velY;

    // this->ball.setPosition(sf::Vector2f(this->posX, this->posY));

    // if (!(fabs(this->velocityX) < 0.1f))
    // {
    //     this->velocityX -= this->velocityX * velocityProportion * 0.01;
    // }
    // else
    // {
    //     this->velocityX = 0;
    // }

    // if (!(fabs(this->velocityY) < 0.1f))
    // {
    //     this->velocityY -= this->velocityY * velocityProportion * 0.01;
    // }
    // else
    // {
    //     this->velocityY = 0;
    // }

    // float velocityValue = sqrt(this->velocityX * this->velocityX + this->velocityY * this->velocityY);
    // std::cout << "Velocity value: " << velocityValue << "\n";

    // // if (!(fabs(this->velocityX) < 0.01f))
    // if (!(fabs(this->velocityX) < 0.1f))
    // {
    //     // Calculate proportion
    //     this->velocityX -= (this->velocityX * velocityValue) / 10;
    //     // this->velocityX *= 0.991; // szybkosc zmienia sie o 0.09% ale i tak jest problem "Normalizacji" czyli w jednym kierunku szybciej dobija do 0.1 i się zeruje
    // } // przez co lekko zakręca, lecz i tak jest to dużo mniejsze niż w przypadku gdy zmieniamy o 0.1
    // else
    // {
    //     this->velocityX = 0;
    // }
    // // if (!(fabs(this->velocityY) < 0.01f))
    // if (!(fabs(this->velocityY) < 0.1f))
    // {
    //     // Calculate proportion
    //     float velocityValue = sqrt(this->velocityX * this->velocityX + this->velocityY * this->velocityY);
    //     // this->velocityY *= 0.991;
    //     this->velocityY -= (this->velocityY * velocityValue) / 10;
    // }
    // else
    // {
    //     this->velocityY = 0;
    // }
}

void Ball::update(sf::WindowBase *window)
{
    this->setVelocity(window);
    this->changePosition(this->velocityX, this->velocityY);
}
void Ball::draw(sf::RenderTarget *target)
{
    target->draw(this->ball);
}
