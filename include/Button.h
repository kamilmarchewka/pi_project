#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

extern float W_WIDTH;
extern float W_HEIGHT;

class Button
{
private:
    int value;
    float posX;
    float posY;

    sf::Sprite sprite;

public:
    Button(sf::Texture *texture, float posX, float posY, int value);
    virtual ~Button();

    void draw(sf::RenderTarget *target);
};
#endif