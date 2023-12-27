#include "pch.h"
#include "Ball.h"

Ball::Ball(sf::Texture &texture)
{
    this->ball.setTexture(texture);
    this->ball.setOrigin(sf::Vector2f(
        this->ball.getGlobalBounds().width / 2,
        this->ball.getGlobalBounds().height / 2));

    this->ball.setPosition(sf::Vector2f(400, 350));

    this->velocity = sf::Vector2f(0, 0);
}
Ball::~Ball()
{
}

sf::FloatRect Ball::getGlobalBounds()
{
    return this->ball.getGlobalBounds();
}
sf::Vector2f Ball::getVelocity()
{
    return this->velocity;
}
void Ball::setVelocityX(float newVel)
{
    this->velocity.x = newVel;
}
void Ball::setVelocityY(float newVel)
{
    this->velocity.y = newVel;
}
void Ball::setPositionX(float newPos)
{
    this->ball.setPosition(sf::Vector2f(
        newPos,
        this->ball.getPosition().y));
}
void Ball::setPositionY(float newPos)
{
    this->ball.setPosition(sf::Vector2f(
        this->ball.getPosition().x,
        newPos));
}

void Ball::update(sf::WindowBase &window)
{
    // Strzelanie = ustawianie odpowiedniego velocity tylko jezeli aktualnie velocity = 0
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (this->velocity.x == 0.f && this->velocity.y == 0.f))
    {
        // Pozycja myszy
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        sf::Vector2f ballPos = this->ball.getPosition();

        // Mysz w stosunku do pilki - z lewej strony lub z prawej strony
        this->velocity.x = (ballPos.x - mousePos.x) / 10.f;
        // Mysz w stosunku do pilki - nad lub pod pilka
        this->velocity.y = (ballPos.y - mousePos.y) / 10.f;

        // TODO zmniejszenie liczby strokeow
    }

    // Move
    this->ball.move(this->velocity);

    // Zmniejszenie velocity
    if (fabs(this->velocity.x) < 0.1f)
        this->velocity.x = 0.f;
    if (fabs(this->velocity.y) < 0.1f)
        this->velocity.y = 0.f;

    this->velocity *= 0.95f;
}
void Ball::render(sf::RenderTarget &target)
{
    target.draw(this->ball);
}