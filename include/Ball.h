#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>

#include "Board.h"

class Ball
{
private:
    float posX;
    float posY;
    float velocityX;
    float velocityY;

    sf::Texture texture;
    sf::Sprite sprite;

    void initVariables();
    void initShape();

public:
    Ball();
    ~Ball();

    sf::Vector2f getPosition();
    sf::Vector2f getSize();

    void setVelocity(sf::WindowBase *window);
    void changePosition(float velX, float velY);
    void checkBoardCollision(Board *board);

    void update(sf::WindowBase *window, Board *board);

    void draw(sf::RenderTarget *target);
};
#endif