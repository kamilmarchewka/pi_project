#include <SFML/Graphics.hpp>
#include "Board.h"

Board::Board(/* args */)
{
    this->initVariables();
    this->initShape();
}

Board::~Board()
{
}

void Board::initVariables()
{
    this->size = sf::Vector2f(900.f, 600.f);
    this->position = sf::Vector2f(1200.f / 2.f, 800.f / 2.f);
}
void Board::initShape()
{
    this->board.setSize(this->size);
    this->board.setOrigin(this->size.x / 2.f, this->size.y / 2.f);
    this->board.setPosition(this->position);
    this->board.setFillColor(sf::Color(146, 186, 59, 255));
}

void Board::render(sf::RenderTarget *target)
{
    target->draw(this->board);
}