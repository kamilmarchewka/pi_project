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

    sf::Texture aimingArrowTexture;
    sf::Sprite aimingArrow;

    float obliczKat(float xStrzalki, float yStrzalki, float xKursora, float yKursora);

public:
    Ball(sf::Texture &texture);
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

    void update(sf::WindowBase &window, int &leftStrokes, int &gameState, bool &isMouseBtnPressedRef);
    void render(sf::RenderTarget &target, int &gameState);
};

#endif