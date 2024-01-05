#include "pch.h"
#include "Ball.h"

Ball::Ball(sf::Texture &texture, int ballSkin)
{
    // Zaladowanie tekstury strzalki do celowania
    if (!(this->aimingArrowTexture.loadFromFile("assets/aiming_arrow.png")))
        std::cout << "ERROR::TEXTURES::Ball.cpp - aiming_arrow.png\n";
    this->aimingArrowTexture.setSmooth(true);
    if (!(this->aimingLineTexture.loadFromFile("assets/aiming_line.png")))
        std::cout << "ERROR::TEXTURES::Ball.cpp - aiming_line.png\n";
    this->aimingLineTexture.setSmooth(true);

    this->ball.setTexture(texture);
    this->ball.setTextureRect(sf::IntRect(ballSkin * 35, 0, 35, 35));
    this->ball.setOrigin(sf::Vector2f(
        this->ball.getGlobalBounds().width / 2,
        this->ball.getGlobalBounds().height / 2));

    this->ball.setPosition(sf::Vector2f(162, 350 + 50));

    // Inicjalizacja zmiennych
    this->isMoving = false;
    this->isAiming = false;
    this->stopTreshold = 0.35;
    this->friction = 0.96;
    this->velocity = sf::Vector2f(0, 0);
    this->maxVelocity = 35.f; // Dla takiej wartosci nie przelatuje przez sciany

    // Ustawienie strzalki do celowania
    // Linia
    this->aimingLine.setTexture(this->aimingLineTexture);
    this->aimingLine.setOrigin(0, this->aimingLine.getGlobalBounds().height / 2);
    this->aimingLine.setPosition(this->ball.getPosition().x, this->ball.getPosition().y);
    // Grot
    this->aimingArrow.setTexture(this->aimingArrowTexture);
    this->aimingArrow.setOrigin(this->aimingArrow.getGlobalBounds().width / 2, this->aimingArrow.getGlobalBounds().height / 2);
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
void Ball::setScale(float scale)
{
    this->ball.setScale(sf::Vector2f(scale, scale));
}

void Ball::update(sf::WindowBase &window, int &leftStrokes, int &gameState, bool &isMouseBtnPressedRef)
{
    // Pozycja myszy
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    // Pozycja pilki
    sf::Vector2f ballPos = this->ball.getPosition();

    // Aktualizacja isAiming
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
        // Ustawienie pozycji linii
        this->aimingLine.setPosition(ballPos.x, ballPos.y);

        float distanceX = (mousePos.x - ballPos.x) / 6.f;
        float distanceY = (mousePos.y - ballPos.y) / 6.f;

        // Obliczenie odleglosci myszki od pilki
        float distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

        if (distance > this->maxVelocity)
            distance = this->maxVelocity;

        // Ustawienie dlugosci strzalki
        float scaleX = distance / this->maxVelocity + 0.2f;
        this->aimingLine.setScale(sf::Vector2f(scaleX, 1));

        // Obracanie sie linii
        float kat = this->obliczKat(this->aimingLine.getPosition().x, this->aimingLine.getPosition().y,
                                    mousePos.x, mousePos.y);

        // Obrocenie linii i grotu o ten sam kat
        this->aimingLine.setRotation(kat);
        this->aimingArrow.setRotation(kat);

        // Ustawienie grotu na koncu linii
        sf::Transform transform = this->aimingLine.getTransform();
        sf::Vector2f endPosition = transform.transformPoint(sf::Vector2f(this->aimingLine.getLocalBounds().width, this->aimingLine.getLocalBounds().height / 2));
        this->aimingArrow.setPosition(endPosition);
    }

    // Strzelaj tylko, jezeli gra sie nie skonczyla => liczba strokeow > 0
    // i jeżeli przycisk nie jest aktualnie klikniety
    if (
        gameState == -1 &&                             // Musimy grac
        !isMouseBtnPressedRef &&                       // Nie moze byc kliknieta mysz
        sf::Mouse::isButtonPressed(sf::Mouse::Left) && // Kliknieto LPP
        mousePos.x >= 0 && mousePos.x <= 1200 &&       // Kliknieto gdzies w oknie gry
        mousePos.y >= 0 && mousePos.y <= 700 &&
        !this->isMoving) // Pilka sie nie porusza
    {
        // Mysz w stosunku do pilki - z lewej strony lub z prawej strony
        this->velocity.x = (ballPos.x - mousePos.x) / 6.f;
        // Mysz w stosunku do pilki - nad lub pod pilka
        this->velocity.y = (ballPos.y - mousePos.y) / 6.f;
        // Dlugosc wektora predkosci
        float veloctiyLength = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));

        float sin = this->velocity.y / veloctiyLength;
        float cos = this->velocity.x / veloctiyLength;

        // Sprawdzenie czy wektor predkosci jest wiekszy niz max predkosc
        // jezeli tak - normalizacja wektora predkosci i jego skladowych x, i y
        if (veloctiyLength > this->maxVelocity)
        {
            veloctiyLength = this->maxVelocity;
            this->velocity.x = veloctiyLength * cos;
            this->velocity.y = veloctiyLength * sin;
        }

        // Zmniejszenie liczby pozostalych strzalow
        leftStrokes--;
    }

    // Poruszanie sie pilki, do momentu gdy jest jakas predkosc
    this->ball.move(this->velocity);

    // Zachamowanie pilki przy zbyt malym velocity
    if (fabs(this->velocity.x) >= fabs(this->velocity.y) && fabs(this->velocity.x) < this->stopTreshold)
        this->velocity = sf::Vector2f(0, 0);
    else if (fabs(this->velocity.x) < fabs(this->velocity.y) && fabs(this->velocity.y) < this->stopTreshold)
        this->velocity = sf::Vector2f(0, 0);

    // Zmniejszenie wektora predkosci o tarcie
    this->velocity *= this->friction;

    // Sprawdzanie czy pilka sie porusza i aktualizowanie zmiennej
    this->isMoving = (this->velocity.x == 0 && this->velocity.y == 0) ? false : true;
}
void Ball::render(sf::RenderTarget &target, int &gameState)
{
    if (this->isAiming && gameState == -1)
    {
        target.draw(this->aimingLine);
        target.draw(this->aimingArrow);
    }

    target.draw(this->ball);
}