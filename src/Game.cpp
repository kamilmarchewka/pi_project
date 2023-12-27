#include "pch.h"
#include "Game.h"
#include "GameplayScreen.h"

Game::Game()
{
    this->gameScreen = 0; // Zaczecie gry na ekranie z menu glownym

    this->window.create(sf::VideoMode(1200, 700), "MiniGolf", sf::Style::Default); // Inicjalizacja okna
    this->window.setFramerateLimit(30);                                            // Ustawienie limitu klatek do 30 fps

    // Ladowanie textur
    // Tlo
    if (!(this->mainBgTexture.loadFromFile("assets/background.png")))
        std::cout
            << "ERROR::TEXTURES - background.png\n";
    this->mainBgTexture.setSmooth(true); // Wyrownanie krawedzi

    // Play btn
    if (!(this->playBtnTexture.loadFromFile("assets/play_btn.png")))
        std::cout << "ERROR::TEXTURES - play_btn.png\n";
    this->playBtnTexture.setSmooth(true); // Wyrownanie krawedzi

    // Lvls btn
    if (!(this->lvlsBtnTexture.loadFromFile("assets/poziomy_btn.png")))
        std::cout << "ERROR::TEXTURES - poziomy_btn.png\n";
    this->lvlsBtnTexture.setSmooth(true); // Wyrownanie krawedzi

    // Options btn
    if (!(this->optionsBtnTexture.loadFromFile("assets/ustawienia_btn.png")))
        std::cout << "ERROR::TEXTURES - ustawienia_btn.png\n";
    this->optionsBtnTexture.setSmooth(true); // Wyrownanie krawedzi

    // Exit btn
    if (!(this->exitBtnTexture.loadFromFile("assets/exit_icon.png")))
        std::cout << "ERROR::TEXTURES - exit_icon.png\n";
    this->exitBtnTexture.setSmooth(true); // Wyrownanie krawedzi

    // Screen 0 ----------------
    this->mainBg.setTexture(this->mainBgTexture);                                           // Ustawienie tekstury
    this->mainBg.setPosition(sf::Vector2f(0, 700 - this->mainBg.getGlobalBounds().height)); // Ustawienie pozycji tla
                                                                                            // na lewy dolny rog

    float menuTopOffset = 50.f; // Przy 0 - playBtn jest na srodku ekranu
    this->playBtn = new Button(this->playBtnTexture, sf::Vector2f(600, 350 + menuTopOffset), 1);
    this->lvlsBtn = new Button(this->lvlsBtnTexture, sf::Vector2f(600, 450 + menuTopOffset), 2);
    this->optionsBtn = new Button(this->optionsBtnTexture, sf::Vector2f(600, 530 + menuTopOffset), 3);

    // Screen 1 ----------------
    // this->GameplayScreenLvl1 = new GameplayScreen(1); // Inicjujemy gdy klikniemy przycisk play

    // All screens -------------
    this->exitBtn = new Button(this->exitBtnTexture, sf::Vector2f(1200 - 35, 30), 0);
}
Game::~Game()
{
    // Screen 0 ----------------
    delete this->playBtn;
    delete this->lvlsBtn;
    delete this->optionsBtn;

    // Screen 1 ----------------
    delete this->GameplayScreenLvl1;

    // All screens -------------
    delete this->exitBtn;
}

sf::RenderWindow &Game::getWindow() // Zwraca referencje do okna gry
{
    return this->window;
}

void Game::update()
{
    // Sprawdzanie wszystkich eventow, ktore zostaly dodane
    while (this->window.pollEvent(this->event)) // Poolowanie eventow z okna do zmiennej event
    {
        // Zamkniecie X
        if (this->event.type == sf::Event::Closed)
            this->window.close(); // Zamkniecie okna
        // Nacisniecie klawisza ESC
        if (
            this->event.type == sf::Event::KeyPressed && // Jezeli jest wcisniety klawisz
            this->event.key.code == sf::Keyboard::Escape)
        {                         // Sprawdzenie czy tym klawiszem jest ESC
            this->window.close(); // Zamkniecie okna
        }
    }

    // Dzialanie przycisku exit
    if (this->gameScreen == 1 || this->gameScreen == 2 || this->gameScreen == 3)
    {
        // Spraawdzenie czy przycisk jest klikniety
        if (this->exitBtn->isClicked(this->window))
        {
            // Powrot do ekranu z menu
            this->gameScreen = this->exitBtn->getValue();

            if (this->gameScreen == 1)
            {
                delete this->GameplayScreenLvl1;
            }
        }
    }

    // Aktualizacja w zaleznosci od okna, na ktorym sie znajdujemy
    if (this->gameScreen == 0)
    {
        // Logika menu
        if (this->playBtn->isClicked(this->window))
        {
            this->gameScreen = this->playBtn->getValue();
            this->GameplayScreenLvl1 = new GameplayScreen(1);
        }
        else if (this->lvlsBtn->isClicked(this->window))
        {
            this->gameScreen = this->lvlsBtn->getValue();
            std::cout << "POZIOMY zostal wcisniety\n";
        }
        else if (this->optionsBtn->isClicked(this->window))
        {
            this->gameScreen = this->optionsBtn->getValue();
            std::cout << "USTAWIENIA zostal wcisniety\n";
        }
    }
    else if (this->gameScreen == 1)
    {
        this->GameplayScreenLvl1->update(this->window);
    }
    else if (this->gameScreen == 2)
    {
        std::cout << "Ekran POZIOMY ejej\n";
    }
    else if (this->gameScreen == 3)
    {
        std::cout << "Ekran USTAWIENIA ejej\n";
    }
    else
        std::cout << "ERROR: Nie ma takiego okna\n";
}

void Game::render()
{
    this->window.clear(sf::Color(168, 202, 89, 255));

    // Renderowanie exitBtn
    if (gameScreen == 1 || gameScreen == 2 || gameScreen == 3)
        this->exitBtn->render(this->window);

    // Renderowanie w zaleznosci od okna, na ktorym sie znajdujemy
    switch (this->gameScreen)
    {
    case 0:
        this->window.draw(this->mainBg);
        this->playBtn->render(this->window);
        this->lvlsBtn->render(this->window);
        this->optionsBtn->render(this->window);
        break;

    case 1:
        this->GameplayScreenLvl1->render(this->window);
        break;

    case 2:
        std::cout << "POZIOMY\n";
        break;

    case 3:
        std::cout << "USTAWIENIA\n";
        break;

    default:
        std::cout << "ERROR: Nie ma takiego okna\n";
        break;
    }

    this->window.display();
}
