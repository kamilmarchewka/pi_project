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
    std::fstream od;
    sf::Font font;
    sf::Texture grassLightTexture, grassDarkTexture, rockTexture, sandTexture, whiteBallTexture, holeTexture, winBgTexture, loseBgTexture, replayBtnTexture, nextLvlBtnTexture;
    sf::Texture iceTexture, water_upTexture, water_downTexture, redBallTexture, blueBallTexture, yellowBallTexture;
    int currentLvl;   // Aktualnie wyswietlany lvl
    int strokesLimit; // Limit uderzen dla danego poziomu
    int currentBall;
    int tikker=0;
    int leftStrokes;
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
    std::vector<sf::Sprite> water_upVector;
    std::vector<sf::Sprite> water_downVector;
    std::vector<sf::Sprite> iceVector;
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
    void waterupCollision();
    void waterdownCollision();
    void iceCollision();
    void wallsCollision();
    void sandCollision();
    void holeCollision();

public:
    GameplayScreen(std::string pathToLvl);
    ~GameplayScreen();

    void setTitleText(sf::String newTitle);
    void setStrokesLimitText(sf::String newText);
    void readLvlFromFile(std::string pathToFile);

    void update(sf::WindowBase &window, std::string *lvlsPathArray, int lvlsPathArrayLength, int &currentLvlRef, bool &isMouseBtnPressedRef);
    void render(sf::RenderTarget &target);
};

#endif