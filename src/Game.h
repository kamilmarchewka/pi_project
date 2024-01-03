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
    // Controls
    /**
     * Aktualnie wywietlany ekran gry
     * 0 - menu glowne
     * 1 - ekran gry
     * 2 - poziomy
     * 3 - ustawienia gry
     */
    int gameScreen;
    bool isMouseBtnPressed;

    int currentLvl;  // Okresla to, jaki jest wybrany lvl w danym momencie
    int prevLvl;     // Poprzedni lvl
    int selectedLvl; // Zaznaczony lvl w menu z poziomami
    int allLvls;
    int unlockedLvls;
    int volume;
    int currentBall;

    std::fstream zap;

    bool musicIsOn;
    // -----------------

    // Czcionka
    sf::Font InterBlack;

    // Okno
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
        musiconBtnTexture,
        musicoffBtnTexture,
        OptionsTitle1Texture,
        OptionsTitle2Texture,
        OptionsTitle3Texture,
        Level1BtnTexture,
        Level2BtnTexture,
        Level3BtnTexture,
        LevelsTexture,
        MinusTexture,
        PlusTexture,
        WhiteBallTexture,
        PinkBallTexture,
        PurpleBallTexture,
        GreenBallTexture,
        LblueBallTexture,
        volumeTexture;


    // Screen 0 ----------------
    sf::Sprite mainBg;

    Button *playBtn;
    Button *lvlsBtn;
    Button *optionsBtn;
    Button *musiconBtn;
    Button *musicoffBtn;
    Button *Plus;
    Button *Minus;
    Button *WhiteBall;
    Button *PinkBall;
    Button *PurpleBall;
    Button *LblueBall;
    Button *GreenBall;
    Button *OptionsTitle1;
    Button *OptionsTitle2;
    Button *OptionsTitle3;
    Button *Vol;

    Button *musicBtn;

    // Screen 1 ----------------
    GameplayScreen *GameplayScreenLvl1; // Ekran z plansza, nr poziomu itd.

    // Screen 2 ----------------
    sf::Text LevelsTitle,OptionsTitle;
    std::vector<Button *> lvlsBtnsVector;

    // Screen 3 ----------------

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