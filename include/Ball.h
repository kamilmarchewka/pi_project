#ifndef BALL_H
#define BALL_H

#include "pch.h"

class Ball
{
private:
    sf::Sprite ball;
    sf::Vector2f velocity;
    float friction;     // Okresla o ile zostanie zmniejszona predkosc w nastepnej klatce
    float stopTreshold; // Graniczna predkosc, przy niej nastepuje calkowite zatrzymanie
    float maxVelocity;  // Maksymalna moc z jaka mozna wystrzelic pilke

    sf::Texture aimingArrowTexture, aimingLineTexture;
    sf::Sprite aimingArrow, aimingLine;

    float obliczKat(float xStrzalki, float yStrzalki, float xKursora, float yKursora);

public:
    Ball(sf::Texture &texture, int ballSkin);
    ~Ball();

    bool isMoving;
    bool isAiming;

    sf::FloatRect getGlobalBounds();
    sf::Vector2f getVelocity();
    sf::Vector2f getPosition();
    float getFriction();
    float getStopTreshold();
    void setFriction(float k);
    void setStopTreshold(float newTreshold);
    void setVelocityX(float newVel);
    void setVelocityY(float newVel);
    void setPositionX(float newPos);
    void setPositionY(float newPos);
    void setScale(float scale);

    void update(sf::WindowBase &window, int &leftStrokes, int &gameState, bool &isMouseBtnPressedRef);
    void render(sf::RenderTarget &target, int &gameState);
};

#endif