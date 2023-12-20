#ifndef BALL_H
#define BALL_H
// Standard includes

// SFML includes
#include <SFML/Graphics.hpp>

#include "Board.h"

class Ball
{
private:
    // Variables
    sf::CircleShape circle;
    sf::Vector2f position;
    float radius;
    sf::Vector2f velocity;

    // Functions
    void initVariables();
    void initShape();

public:
    // Constructor and destructor
    Ball();
    ~Ball();

    // Accessors
    float getRadius()
    {
        return this->radius;
    }

    // Modifiers
    void move(float x, float y);

    // Functions
    void shoot(sf::RenderWindow *window);
    void boardCollision(Board *board);
    void update(sf::RenderWindow *window, Board *board);
    void render(sf::RenderTarget *target);
};

#endif