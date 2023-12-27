#ifndef BALL_H
#define BALL_H

#include "pch.h"

class Ball
{
private:
    sf::Sprite ball;
    sf::Vector2f velocity;

public:
    Ball(sf::Texture &texture);
    ~Ball();

    sf::FloatRect getGlobalBounds();
    sf::Vector2f getVelocity();
    void setVelocityX(float newVel);
    void setVelocityY(float newVel);
    void setPositionX(float newPos);
    void setPositionY(float newPos);

    void update(sf::WindowBase &window);
    void render(sf::RenderTarget &target);
};

#endif