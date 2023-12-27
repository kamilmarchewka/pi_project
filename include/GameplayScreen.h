#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H

#include "pch.h"

#include "Ball.h"

// Taka nakladka, ktora zostanie nalozona na ten 'normalny' ekran;
class GameplayScreen
{
private:
    sf::Font font;
    sf::Texture grassLightTexture, grassDarkTexture, rockTexture, whiteBallTexture;

    int currentLvl;        // Aktualnie wyswietlany lvl
    int strokesLimit;      // Limit uderzen dla danego poziomu
    int logicalMap[8][16]; // Logiczna mapa przedstawiajaca gdzie znajduja sie jakie przeskzody

    float borderThickness;
    sf::RectangleShape course; // Pole golfowe
    sf::Text titleText;        // Naglowek z nr lvlu
    sf::Text strokesLimitText; // Naglowek z liczba pozostalych uderzen

    int gridRows;                 // Liczba rzedow na planszy
    int gridCols;                 // Liczba kolumn na planszy
    sf::Sprite spritesMap[8][16]; // Tablica ze spriteami

    Ball *ball; // Pointer do pilki

    void initAssets();

public:
    GameplayScreen(int lvl, int strokesLimit, int logicalMap[8][16]);
    ~GameplayScreen();

    void initCourseObstackles();

    void update(sf::WindowBase &window);
    void render(sf::RenderTarget &target);
};

#endif