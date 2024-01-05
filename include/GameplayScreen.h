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
    sf::Texture obstaclesTexture, grassLightTexture, grassDarkTexture, rockTexture, sandTexture, iceTexture, gulfTexture, whiteBallTexture, holeTexture, winBgTexture, loseBgTexture, gameFinishedBgTexture, replayBtnTexture, nextLvlBtnTexture, water_upTexture, water_downTexture;

    // Zmienne
    int lvl;          // Aktualnie wyswietlany lvl
    int strokesLimit; // Limit uderzen dla danego poziomu
    int strokesLeft;
    int logicalMap[8][16]; // Logiczna mapa przedstawiajaca gdzie znajduja sie jakie przeskzody

    // Pole / plansza
    float borderThickness;
    sf::RectangleShape course; // Pole golfowe
    sf::Text titleText;        // Naglowek z nr lvlu
    sf::Text leftStrokesText;  // Naglowek z liczba pozostalych uderzen
    int gridRows;              // Liczba rzedow na planszy
    int gridCols;              // Liczba kolumn na planszy

    std::vector<sf::Sprite> grassVector;      // Wektor przechowujacy trawe jasna i ciemna
    std::vector<sf::Sprite> wallsVector;      // Wektor przechowujacy wszystkie sciany
    std::vector<sf::Sprite> sandVector;       // Wektor przechowujacy wszystkie piaski
    std::vector<sf::Sprite> iceVector;        // Wektor przechowujacy wszystkie lody
    std::vector<sf::Sprite> gulfsVector;      // Wektor przechowujacy wszystkie przepascie
    std::vector<sf::Sprite> water_upVector;   // Wektor przechowujacy wszystkie wody (kierujące w górę ekranu)
    std::vector<sf::Sprite> water_downVector; // Wektor przechowujacy wszystkie wody (kierujące w dół ekranu)

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
    void grassCollision();
    void wallsCollision();
    void sandCollision();
    void iceCollision();
    void gulfCollision();
    void waterupCollision();
    void waterdownCollision();
    void ObstaclesCollisions();
    void holeCollision(int allLvls);

public:
    GameplayScreen(int &currentLvl, sf::Texture &ballsTexture, int ballSkin);
    ~GameplayScreen();

    void setNewString(sf::String newString, sf::Text &text);
    // void setTitleText(sf::String newTitle);
    // void setStrokesLimitText(sf::String newText);
    void readLvlFromFile(int currentLvl);

    void update(sf::WindowBase &window, int &prevLvl, int &currentLvl, int allLvls, int &unlockedLevels, bool &isMouseBtnPressed);
    void render(sf::RenderTarget &target, int allLvls);
};

#endif