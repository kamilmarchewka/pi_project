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
    std::string lvlsPathArray[3]; // Przechowuje sciezki do plikow z lvlami
    int lvlsPathArrayLength;

    /**
     * Aktualnie wywietlany ekran gry
     * 0 - menu glowne
     * 1 - ekran gry
     * 2 - poziomy
     * 3 - ustawienia gry
     */
    int gameScreen;

    int musicIsOn;
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
        musicBtnTexture;

    // Screen 0 ----------------
    sf::Sprite mainBg;

    Button *playBtn;
    Button *lvlsBtn;
    Button *optionsBtn;

    Button *musicBtn;

    // Screen 1 ----------------
    GameplayScreen *GameplayScreenLvl1; // Ekran z plansza, nr poziomu itd.

    // Screen 2 ----------------
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