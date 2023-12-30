#include "pch.h"
#include "Ball.h"

Ball::Ball(sf::Texture &texture)
{
    // Zaladowanie tekstury strzalki do celowania
    if (!(this->aimingArrowTexture.loadFromFile("assets/aiming_arrow.png")))
        std::cout << "ERROR::TEXTURES::Ball.cpp - aiming_arrow.png\n";
    this->aimingArrowTexture.setSmooth(true);

    this->ball.setTexture(texture);
    this->ball.setOrigin(sf::Vector2f(
        this->ball.getGlobalBounds().width / 2,
        this->ball.getGlobalBounds().height / 2));

    this->ball.setPosition(sf::Vector2f(162, 350 + 50));

    this->isMoving = false;
    this->isAiming = false;
    this->stopTreshold = 0.35;
    this->friction = 0.96;
    this->velocity = sf::Vector2f(0, 0);

    // Ustawienie strzalki do celowania
    this->aimingArrow.setTexture(this->aimingArrowTexture);
    this->aimingArrow.setOrigin(0, this->aimingArrow.getGlobalBounds().height / 2);
    this->aimingArrow.setPosition(this->ball.getPosition().x, this->ball.getPosition().y);
    // this->aimingArrow.rotate(45.f);
}
Ball::~Ball()
{
}

float Ball::obliczKat(float xStrzalki, float yStrzalki, float xKursora, float yKursora)
{
    double deltaX = xKursora - xStrzalki;
    double deltaY = yKursora - yStrzalki;

    // Używamy atan2, aby obliczyć kąt w radianach
    double katRadiany = std::atan2(deltaY, deltaX);

    // Zamieniamy kąt na stopnie i dodajemy 180 stopni
    double katStopnie = std::fmod((katRadiany * 180.0 / M_PI) + 360.0, 360.0);

    // Obrót strzałki będzie przeciwny do kąta, a grot strzałki będzie po przeciwną stronie
    double katDoObrotu = std::fmod(katStopnie + 180.0, 360.0);

    return katDoObrotu;
}

sf::FloatRect Ball::getGlobalBounds()
{
    return this->ball.getGlobalBounds();
}
sf::Vector2f Ball::getVelocity()
{
    return this->velocity;
}
sf::Vector2f Ball::getPosition()
{
    return this->ball.getPosition();
}
float Ball::getStopTreshold()
{
    return this->stopTreshold;
}
float Ball::getFriction()
{
    return this->friction;
}
void Ball::setFriction(float k)
{
    this->friction = k;
}
void Ball::setStopTreshold(float newTreshold)
{
    this->stopTreshold = newTreshold;
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

void Ball::update(sf::WindowBase &window, int &leftStrokes, int &gameState, bool &isMouseBtnPressedRef)
{
    // Pozycja myszy
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    // Pozycja pilki
    sf::Vector2f ballPos = this->ball.getPosition();

    if (!this->isMoving && gameState == -1 && !this->isAiming && !isMouseBtnPressedRef)
    {
        this->isAiming = true;
    }
    else if ((this->isMoving || gameState != -1) && this->isAiming)
    {
        this->isAiming = false;
    }

    if (isAiming)
    {
        // Ustawienie pozycji strzalki
        this->aimingArrow.setPosition(ballPos.x, ballPos.y);
        float distance = sqrt(pow(mousePos.x - ballPos.x, 2) + pow(mousePos.y - ballPos.y, 2));
        float scaleX = distance / 100.f;
        this->aimingArrow.setScale(sf::Vector2f(scaleX, this->aimingArrow.getScale().y));

        // Obracanie sie strzalki
        float kat = this->obliczKat(this->aimingArrow.getPosition().x, this->aimingArrow.getPosition().y,
                                    mousePos.x, mousePos.y);
        this->aimingArrow.setRotation(kat);
    }

    // Strzelaj tylko, jezeli gra sie nie skonczyla => liczba strokeow > 0
    // i jeżeli przycisk nie jest aktualnie klikniety
    // + obsluga logiki strzalki do celowania
    if (gameState == -1 && !isMouseBtnPressedRef)
    {
        // Strzelanie
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->isMoving)
        {
            // Mysz w stosunku do pilki - z lewej strony lub z prawej strony
            this->velocity.x = (ballPos.x - mousePos.x) / 5.f;
            // Mysz w stosunku do pilki - nad lub pod pilka
            this->velocity.y = (ballPos.y - mousePos.y) / 5.f;

            leftStrokes--;
        }
    }

    // Move
    this->ball.move(this->velocity);

    // Zachamowanie pilki przy zbyt malym velocity
    if (fabs(this->velocity.x) >= fabs(this->velocity.y) && fabs(this->velocity.x) < this->stopTreshold)
        this->velocity = sf::Vector2f(0, 0);
    else if (fabs(this->velocity.x) < fabs(this->velocity.y) && fabs(this->velocity.y) < this->stopTreshold)
        this->velocity = sf::Vector2f(0, 0);

    this->velocity *= this->friction;

    // Sprawdzanie czy pilka sie porusza i aktualizowanie zmiennej
    if (this->velocity.x == 0 && this->velocity.y == 0)
        this->isMoving = false;
    else
        this->isMoving = true;
}
void Ball::render(sf::RenderTarget &target, int &gameState)
{
    if (this->isAiming && gameState == -1)
        target.draw(this->aimingArrow);

    target.draw(this->ball);
}