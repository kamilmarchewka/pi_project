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

    int ballSkin;
    bool musicIsOn;
    // -----------------

    // Czcionka
    sf::Font InterBlack, InterSemiBold;

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
        Level1BtnTexture,
        Level2BtnTexture,
        Level3BtnTexture,
        LevelsTexture,
        ballsTexture;

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
    std::vector<Button *> lvlsBtnsVector;

    // Screen 3 ----------------
    sf::Text OptionsTitle, SoundTitle, VolumeTitle, BallColorTitle;
    Button *ballSkinsBtnsArr[5];

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