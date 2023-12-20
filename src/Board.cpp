#include <SFML/Graphics.hpp>

#include "Board.h"

extern float W_WIDTH;
extern float W_HEIGHT;

Board::Board()
{
    this->initVariables();
    this->initShape();
}
Board::~Board(){};

void Board::initVariables()
{
    this->outlineThickness = 15;
    this->width = 900 + outlineThickness;
    this->height = 500 + outlineThickness;
    this->posX = (W_WIDTH - this->width - this->outlineThickness * 2) / 2;
    this->posY = (W_HEIGHT - this->height - this->outlineThickness * 2) / 2 + 50;
}
void Board::initShape()
{
    // Setting size
    this->board.setSize(sf::Vector2f(this->width, this->height));
    this->board.setOutlineThickness(this->outlineThickness);

    // Setting colors
    this->board.setFillColor(sf::Color::Green);
    this->board.setOutlineColor(sf::Color::Blue);

    // Setting position
    this->board.setPosition(sf::Vector2f(this->posX, this->posY));
}

sf::Vector2f Board::getPosition()
{
    return this->board.getGlobalBounds().getPosition();
}
sf::Vector2f Board::getSize()
{
    return this->board.getGlobalBounds().getSize();
}

void Board::draw(sf::RenderTarget *target)
{
    target->draw(this->board);
}
