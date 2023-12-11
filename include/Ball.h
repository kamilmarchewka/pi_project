#ifndef BALL_H
#define BALL_H
// Standard includes

// SFML includes
#include <SFML/Graphics.hpp>

class Ball
{
private:
    // Variables
    sf::CircleShape circle;
    sf::Vector2f position;
    sf::Vector2f velocity;

    // Functions
    void initVariables();
    void initShape();

public:
    // Constructor and destructor
    Ball();
    ~Ball();

    // Accessors

    // Modifiers

    // Functions
    void update();
    void render(sf::RenderTarget *target);
};

#endif