#ifndef GAME_H
#define GAME_H

#include "pch.h"

// Screen 0 ----------------
#include "Button.h"
// Screen 1 ----------------
#include "GameplayScreen.h"

class Game
{
private:
    sf::Font InterBlack;
    std::fstream zap;
    int currentLvl;               // Okresla to, jaki jest wybrany lvl w danym momencie
    std::string lvlsPathArray[6]; // Przechowuje sciezki do plikow z lvlami
    int lvlsPathArrayLength;      // Dlugosc, jest liczona automatycznie

    /**
     * Aktualnie wywietlany ekran gry
     * 0 - menu glowne
     * 1 - ekran gry
     * 2 - poziomy
     * 3 - ustawienia gry
     */
    int gameScreen;
    long long int volume;
    int currentBall;

    bool musicIsOn;
    bool isMouseBtnPressed;

    sf::RenderWindow window; // Okno gry
    sf::Event event;         // Event

    // Music
    sf::Music backgroundMusic; // Muzyka w tle

    // Textures
    sf::Texture
        mainBgTexture,
        playBtnTexture,
        lvlsBtnTexture,
        optionsBtnTexture,
        exitBtnTexture,
        musicBtnTexture,
        PlusTexture,
        MinusTexture,
        RedBallTexture,
        BlueBallTexture,
        YellowBallTexture,
        WhiteBallTexture,
        Level1BtnTexture,
        Level2BtnTexture,
        Level3BtnTexture,
        Level4BtnTexture,
        Level5BtnTexture,
        Level6BtnTexture;

    // Screen 0 ----------------
    sf::Sprite mainBg;

    Button *playBtn;
    Button *lvlsBtn;
    Button *optionsBtn;
    Button *musicBtn;

    // Screen 1 ----------------
    GameplayScreen *GameplayScreenLvl1; // Ekran z plansza, nr poziomu itd.

    // Screen 2 ----------------
    sf::Text LevelsTitle;
    Button *Level1Btn;
    Button *Level2Btn;
    Button *Level3Btn;
    Button *Level4Btn;
    Button *Level5Btn;
    Button *Level6Btn;
    // Screen 3 ----------------
    sf::Text OptionsTitle1;
    sf::Text OptionsTitle2;
    sf::Text OptionsTitle3;
    Button *musiconBtn;
    Button *musicoffBtn;
    Button *Plus;
    Button *Minus;
    Button *WhiteBall;
    Button *RedBall;
    Button *BlueBall;
    Button *YellowBall;
    // All screens -------------
    Button *exitBtn;

    void initAssets();

public:
    Game();
    ~Game();

    sf::RenderWindow &getWindow(); // Zwraca okno gry

    void update(); // Aktualizuje gre
    void render(); // Renderuje gre
};
#endif