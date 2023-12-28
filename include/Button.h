#ifndef BUTTON_H
#define BUTTON_H

#include "pch.h"

class Button
{
private:
    sf::Sprite button;
    int value;

public:
    Button(
        sf::Texture &texture, // Texture
        sf::Vector2f pos,     // Position
        int value             // Wartosc przycisku
    );
    ~Button();

    const int getValue() const;             // Zwraca value przycisku
    bool isClicked(sf::WindowBase &window); // Zwraca true - jezeli przycisk jest klikniety i false jezeli nie

    void setTextureRect(sf::IntRect rect);

    void updateHover(sf::WindowBase &window);
    void render(sf::RenderTarget &target); // Renderuje przycisk w targecie
};
#endif