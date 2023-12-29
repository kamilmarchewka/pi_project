#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H

#include "pch.h"

#include "Ball.h"
#include "Button.h"

// Taka nakladka, ktora zostanie nalozona na ten 'normalny' ekran;
class GameplayScreen
{
private:
    /**
     * -1 - playgin
     * 0 - lose
     * 1 - win
     */
    int gameState;

    sf::Font font;
    sf::Texture grassLightTexture, grassDarkTexture, rockTexture, sandTexture, whiteBallTexture, holeTexture, winBgTexture, loseBgTexture, replayBtnTexture, nextLvlBtnTexture;

    int lvl;          // Aktualnie wyswietlany lvl
    int strokesLimit; // Limit uderzen dla danego poziomu
    int strokesLeft;
    int logicalMap[8][16]; // Logiczna mapa przedstawiajaca gdzie znajduja sie jakie przeskzody

    float borderThickness;
    sf::RectangleShape course; // Pole golfowe
    sf::Text titleText;        // Naglowek z nr lvlu
    sf::Text leftStrokesText;  // Naglowek z liczba pozostalych uderzen
    int gridRows;              // Liczba rzedow na planszy
    int gridCols;              // Liczba kolumn na planszy

    std::vector<sf::Sprite> grassVector; // Wektor przechowujacy trawe jasna i ciemna
    std::vector<sf::Sprite> wallsVector; // Wektor przechowujacy wszystkie sciany
    std::vector<sf::Sprite> sandVector;  // Wektor przechowujacy wszystkie sciany

    Ball *ball; // Pointer do pilki

    sf::Sprite hole; // Dolek

    // Ekran wygranej / przegranej
    sf::Sprite endGameScreen;
    Button *replayBtn;
    Button *nextLvlBtn;

    // Init
    void initAssets();
    void initCourse();
    void initLvlTitle();
    void initMaxStrokesTitle();
    void setUpObstacles();

    // Kolizje
    void courseBordersCollision();
    void wallsCollision();
    void sandCollision();
    void holeCollision();

public:
    GameplayScreen(int &currentLvl);
    ~GameplayScreen();

    void setTitleText(sf::String newTitle);
    void setStrokesLimitText(sf::String newText);
    void readLvlFromFile(int currentLvl);

    void update(sf::WindowBase &window, int &prevLvl, int &currentLvl, int allLvls, int &unlockedLevels, bool &isMouseBtnPressed);
    void render(sf::RenderTarget &target, int allLvls);
};

#endif