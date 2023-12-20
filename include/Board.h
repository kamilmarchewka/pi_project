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

    sf::Vector2f getPosition()
    {
        return this->position;
    };
    sf::Vector2f getSize()
    {
        return this->size;
    }

    void render(sf::RenderTarget *target);
};
#endif
