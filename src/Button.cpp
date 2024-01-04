#include "pch.h"
#include "Button.h"

Button::Button(sf::Texture &texture, sf::Vector2f pos, int value)
{
    this->value = value;

    // Danie textury na przycisk
    this->button.setTexture(texture);

    // Ustawienie pozycji przycisku
    this->button.setOrigin(sf::Vector2f(
        this->button.getGlobalBounds().width / 2,
        this->button.getGlobalBounds().height / 2));
    this->button.setPosition(sf::Vector2f(pos));
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

void Button::setTextureRect(sf::IntRect rect)
{
    this->button.setTextureRect(rect);
}
void Button::setPositionY(float newPos)
{
    this->button.setPosition(sf::Vector2f(this->button.getPosition().x, newPos));
}
void Button::setScale(float scale)
{
    this->button.setScale(sf::Vector2f(scale, scale));
}
sf::Vector2f Button::getPosition()
{
    return this->button.getPosition();
}

bool Button::hovering(sf::WindowBase &window)
{
    // Pozycja myszki wewnatrz okna gry
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    sf::FloatRect buttonBounds = this->button.getGlobalBounds();

    // Sprawdzenie czy myszka jest nad przyciskiem
    if (
        mousePos.x >= buttonBounds.left &&
        mousePos.x <= buttonBounds.left + buttonBounds.width &&
        mousePos.y >= buttonBounds.top &&
        mousePos.y <= buttonBounds.top + buttonBounds.height)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Button::render(sf::RenderTarget &target)
{
    target.draw(this->button); // Renderowanie przycisku we wskazanym targecie
}