#include <SFML/Graphics.hpp>

#include "Board.h"

class Ball
{
private:
    float size;
    float posX;
    float posY;
    float velocityX;
    float velocityY;

    sf::RectangleShape ball;

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