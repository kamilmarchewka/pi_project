#include "pch.h"
#include "Button.h"

Button::Button(sf::Texture &texture, sf::Vector2f pos, int value)
{
    this->value = value;

    this->button.setTexture(texture); // Danie textury na przycisk

    this->button.setOrigin(sf::Vector2f(
        this->button.getGlobalBounds().width / 2,
        this->button.getGlobalBounds().height / 2));
    this->button.setPosition(sf::Vector2f(pos)); // Ustawienie pozycji przycisku
}
Button::~Button() {}

const int Button::getValue() const
{
    return this->value; // Zwraca wartosc przycisku
}

bool Button::isClicked(sf::WindowBase &window)
{
    // Pozycja myszki wewnatrz okna gry
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    return (
               sf::Mouse::isButtonPressed(sf::Mouse::Left) && // Sprawdzenie czy kliknieto LPM
               // Sprawdzenie czy kliknieto wewnatrz przycisku graj
               mousePos.x >= this->button.getGlobalBounds().left &&
               mousePos.x <= this->button.getGlobalBounds().left + this->button.getGlobalBounds().width &&
               mousePos.y >= this->button.getGlobalBounds().top &&
               mousePos.y <= this->button.getGlobalBounds().top + this->button.getGlobalBounds().height)
               ? true
               : false;
}

void Button::render(sf::RenderTarget &target)
{
    target.draw(this->button); // Renderowanie przycisku we wskazanym targecie
}