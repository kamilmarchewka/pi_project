#include "pch.h"
#include "Button.h"

Button::Button(sf::Texture &texture, sf::Vector2f pos, int value, sf::IntRect textureRect)
{
    this->value = value;

    this->button.setTexture(texture); // Danie textury na przycisk
    if (textureRect != sf::IntRect(-1, -1, -1, -1))
        this->button.setTextureRect(textureRect);

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

void Button::setTextureRect(sf::IntRect rect)
{
    this->button.setTextureRect(rect);
}
void Button::setPositionY(float newPos)
{
    this->button.setPosition(sf::Vector2f(this->button.getPosition().x, newPos));
}
sf::Vector2f Button::getPosition()
{
    return this->button.getPosition();
}

void Button::updateHover(sf::WindowBase &window)
{
    // Pozycja myszki wewnatrz okna gry
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    sf::FloatRect buttonBounds = this->button.getGlobalBounds();

    if (
        mousePos.x >= buttonBounds.left && mousePos.x <= buttonBounds.left + buttonBounds.width &&
        mousePos.y >= buttonBounds.top && mousePos.y <= buttonBounds.top + buttonBounds.height)
    {
        this->button.setScale(sf::Vector2f(1, 1));
    }
    else
    {
        this->button.setScale(sf::Vector2f(0.95, 0.95));
    }
}
void Button::render(sf::RenderTarget &target)
{
    target.draw(this->button); // Renderowanie przycisku we wskazanym targecie
}