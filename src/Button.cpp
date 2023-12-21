#include <SFML/Graphics.hpp>

#include "Button.h"

extern float W_WIDTH;
extern float W_HEIGHT;

Button::Button(sf::Texture *texture, float posX, float posY, int value)
{
    this->value = value;
    this->posX = posX;
    this->posY = posY;

    this->sprite.setTexture(*texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setPosition(this->posX, this->posY);
}

Button::~Button() {}

void Button::draw(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}