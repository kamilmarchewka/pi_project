#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

class Board
{
private:
    float outlineThickness;
    float width;
    float height;
    float posX;
    float posY;

    sf::RectangleShape board;

    void initVariables();
    void initShape();

public:
    Board();
    ~Board();

    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    float getBorderThickness();

    void draw(sf::RenderTarget *target);
};
#endif