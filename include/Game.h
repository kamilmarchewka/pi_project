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

    int currentLvl;               // Okresla to, jaki jest wybrany lvl w danym momencie
    std::string lvlsPathArray[3]; // Przechowuje sciezki do plikow z lvlami
    int lvlsPathArrayLength;      // Dlugosc, jest liczona automatycznie

    /**
     * Aktualnie wywietlany ekran gry
     * 0 - menu glowne
     * 1 - ekran gry
     * 2 - poziomy
     * 3 - ustawienia gry
     */
    int gameScreen;

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
        Level1BtnTexture,
        Level2BtnTexture,
        Level3BtnTexture,
        LevelsTexture;

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
    Button *lvlsButtonArr[6];
    int allLevels;
    int unlockedLevels;
    Button *lvlButton;
    std::vector<Button *> LevelsBtnVector;

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