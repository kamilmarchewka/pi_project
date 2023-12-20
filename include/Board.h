#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

class Board
{
private:
    /* data */
    sf::Vector2f size;
    sf::Vector2f position;
    sf::RectangleShape board;

    void initVariables();
    void initShape();

public:
    Board(/* args */);
    ~Board();

    void render(sf::RenderTarget *target);
};
#endif
