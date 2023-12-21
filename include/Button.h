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

    sf::Sprite btnSprite;
    sf::Texture t;

    void initVariables()
    {
        this->t.loadFromFile("assets/v2/play_btn.png");
        this->posX = W_WIDTH / 2.f;
        this->posY = W_HEIGHT / 2.f;
    };
    void initShape()
    {
        this->btnSprite.setTexture(this->t);
        this->btnSprite.setOrigin(this->btnSprite.getGlobalBounds().width / 2, this->btnSprite.getGlobalBounds().height / 2);
        this->btnSprite.setPosition(sf::Vector2f(posX, posY));
    }

public:
    Button()
    {
        initVariables();
        initShape();
    }
    ~Button(){};

    void draw(sf::RenderTarget *t)
    {
        t->draw(this->btnSprite);
    }
};
#endif