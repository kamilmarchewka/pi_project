#include <SFML/Graphics.hpp>

class Ball
{
private:
    float radius;
    float posX;
    float posY;
    sf::CircleShape ball;

    void initVariables();
    void initShape();

public:
    Ball();
    ~Ball();

    sf::Vector2f getPosition();
    sf::Vector2f getSize();

    void setVelocity(float newVelocityX, float newVelocityY);
    void changePosition(float newX, float newY);

    void update();

    void draw(sf::RenderTarget *target);
};