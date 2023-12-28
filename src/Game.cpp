#include "pch.h"
#include "Game.h"
#include "GameplayScreen.h"

void Game::initAssets()
{
    // Font
    if (!this->InterBlack.loadFromFile("assets/fonts/Inter-Black.ttf"))
    {
        std::cout << "ERROR::FONTS - Inter-Black.ttf\n";
    }

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

    // Music btn
    if (!(this->musicBtnTexture.loadFromFile("assets/music.png")))
        std::cout << "ERROR::TEXTURES - music.png\n";
    this->musicBtnTexture.setSmooth(true); // Wyrownanie krawedzi

    // Level 1 - przycisk
    if (!(this->Level1BtnTexture.loadFromFile("assets/l1_btn.png")))
        std::cout << "ERROR::TEXTURES - l1_btn.png\n";
    this->Level1BtnTexture.setSmooth(true);

    // Level 2 - przycisk
    if (!(this->Level2BtnTexture.loadFromFile("assets/l2_btn.png")))
        std::cout << "ERROR::TEXTURES - l2_btn.png\n";
    this->Level2BtnTexture.setSmooth(true);

    // Level 3 - przycisk
    if (!(this->Level3BtnTexture.loadFromFile("assets/l3_btn.png")))
        std::cout << "ERROR::TEXTURES - l3_btn.png\n";
    this->Level3BtnTexture.setSmooth(true);

    // Ladowanie muzyki
    this->backgroundMusic.openFromFile("assets/background_music.ogg");
    this->backgroundMusic.setVolume(30.f);
    // this->backgroundMusic.play();
    this->backgroundMusic.setLoop(true);
}

Game::Game()
{
    this->currentLvl = 1;

    // Przypisanie sciezek do plikow z poziomami do tablicy
    this->lvlsPathArrayLength = sizeof(this->lvlsPathArray) / sizeof(std::string);
    for (int i = 0; i < lvlsPathArrayLength; i++)
    {
        std::string lvlNum = std::to_string(i + 1);
        std::string path = "data/lvl_" + lvlNum + ".txt";
        std::cout << path << std::endl;
        this->lvlsPathArray[i] = path;
    }

    this->gameScreen = 0;    // Zaczecie gry na ekranie z menu glownym
    this->musicIsOn = false; // Domyslnie muzyka jest wylaczona
    this->isMouseBtnPressed = false;

    this->window.create(sf::VideoMode(1200, 700), "MiniGolf", sf::Style::Default); // Inicjalizacja okna
    this->window.setFramerateLimit(30);                                            // Ustawienie limitu klatek do 30 fps

    // Zaladowanie tekstur
    this->initAssets();

    // Screen 0 ----------------
    this->mainBg.setTexture(this->mainBgTexture);                                           // Ustawienie tekstury
    this->mainBg.setPosition(sf::Vector2f(0, 700 - this->mainBg.getGlobalBounds().height)); // Ustawienie pozycji tla
                                                                                            // na lewy dolny rog

    float menuTopOffset = 50.f; // Przy 0 - playBtn jest na srodku ekranu
    this->playBtn = new Button(this->playBtnTexture, sf::Vector2f(600, 350 + menuTopOffset), 1);
    this->lvlsBtn = new Button(this->lvlsBtnTexture, sf::Vector2f(600, 450 + menuTopOffset), 2);
    this->optionsBtn = new Button(this->optionsBtnTexture, sf::Vector2f(600, 530 + menuTopOffset), 3);

    this->musicBtn = new Button(this->musicBtnTexture, sf::Vector2f(1180, 30), -1);
    this->musicBtn->setTextureRect(sf::IntRect(34, 0, 34, 34));

    // Screen 1 ----------------

    // Screen 2 ----------------
    // Inicjalizacja tytulu

    this->LevelsTitle.setString("Poziomy");                     // Napis
    this->LevelsTitle.setFont(this->InterBlack);                // Czcionka
    this->LevelsTitle.setFillColor(sf::Color(30, 48, 80, 255)); // Kolor
    this->LevelsTitle.setCharacterSize(70);
    this->LevelsTitle.setOrigin(sf::Vector2f( // Origin - srodek dolnej krawedzi
        this->LevelsTitle.getGlobalBounds().width / 2,
        this->LevelsTitle.getGlobalBounds().height + 9));
    this->LevelsTitle.setPosition(sf::Vector2f(1200 / 2, 170));

    float lvlsTopOffset = 300;
    float lvlsLineHeight = 200;
    this->Level1Btn = new Button(this->Level1BtnTexture, sf::Vector2f(600 - 200, lvlsTopOffset), 1);
    this->Level2Btn = new Button(this->Level2BtnTexture, sf::Vector2f(600, lvlsTopOffset), 2);
    this->Level3Btn = new Button(this->Level3BtnTexture, sf::Vector2f(600 + 200, lvlsTopOffset), 3);
    this->Level4Btn = new Button(this->Level1BtnTexture, sf::Vector2f(600 - 200, lvlsTopOffset + lvlsLineHeight), 4);
    this->Level5Btn = new Button(this->Level2BtnTexture, sf::Vector2f(600, lvlsTopOffset + lvlsLineHeight), 5);
    this->Level6Btn = new Button(this->Level3BtnTexture, sf::Vector2f(600 + 200, lvlsTopOffset + lvlsLineHeight), 5);

    // All screens -------------
    this->exitBtn = new Button(this->exitBtnTexture, sf::Vector2f(1200 - 35, 30), 0);
}
Game::~Game()
{
    // Screen 0 ----------------
    delete this->playBtn;
    delete this->lvlsBtn;
    delete this->optionsBtn;

    delete this->musicBtn;

    // Screen 1 ----------------
    delete this->GameplayScreenLvl1;

    // Screen 2 ----------------
    delete this->Level1Btn;
    delete this->Level2Btn;
    delete this->Level3Btn;
    delete this->Level4Btn;
    delete this->Level5Btn;
    delete this->Level6Btn;

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
        if (this->event.type == sf::Event::MouseButtonReleased)
        {
            this->isMouseBtnPressed = false;
        }
    }

    // Animacja przyciskow gdy najedzie sie myszka
    this->playBtn->updateHover(this->window);
    this->lvlsBtn->updateHover(this->window);
    this->optionsBtn->updateHover(this->window);
    this->musicBtn->updateHover(this->window);

    // Dzialanie przycisku exit
    if (this->gameScreen == 1 || this->gameScreen == 2 || this->gameScreen == 3)
    {
        // Spraawdzenie czy przycisk jest klikniety
        if (this->exitBtn->isClicked(this->window) && !this->isMouseBtnPressed)
        {
            this->isMouseBtnPressed = true;

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
        if (this->playBtn->isClicked(this->window) && !this->isMouseBtnPressed)
        {
            this->isMouseBtnPressed = true;

            this->gameScreen = this->playBtn->getValue();
            this->GameplayScreenLvl1 = new GameplayScreen(this->lvlsPathArray[this->currentLvl - 1]);
        }
        else if (this->lvlsBtn->isClicked(this->window) && !this->isMouseBtnPressed)
        {
            this->isMouseBtnPressed = true;

            this->gameScreen = this->lvlsBtn->getValue();
            std::cout << "POZIOMY zostal wcisniety\n";
        }
        else if (this->optionsBtn->isClicked(this->window) && !this->isMouseBtnPressed)
        {
            this->isMouseBtnPressed = true;

            this->gameScreen = this->optionsBtn->getValue();
            std::cout << "USTAWIENIA zostal wcisniety\n";
        }

        // Wlaczanie / wylaczanie musycki
        if (this->musicBtn->isClicked(this->window) && !this->isMouseBtnPressed)
        {
            this->isMouseBtnPressed = true;

            if (musicIsOn)
            {
                this->musicIsOn = false;
                this->musicBtn->setTextureRect(sf::IntRect(34, 0, 34, 34));
                this->backgroundMusic.pause(); // Zatrzymanie muzyki
            }
            else
            {
                this->musicIsOn = true;
                this->musicBtn->setTextureRect(sf::IntRect(0, 0, 34, 34));
                this->backgroundMusic.play(); // Wznowienie muzyki
            }
        }
    }
    else if (this->gameScreen == 1)
    {
        this->GameplayScreenLvl1->update(this->window, this->lvlsPathArray, this->lvlsPathArrayLength, this->currentLvl, this->isMouseBtnPressed);
        std::cout << "game.cpp " << this->currentLvl << std::endl;
    }
    else if (this->gameScreen == 2)
    {
        // Wybor poziomu
        // Poziom 1
        if (this->Level1Btn->isClicked(this->window))
        {
            this->isMouseBtnPressed = true;
            this->currentLvl = this->Level1Btn->getValue();
        }
        // Poziom 2
        if (this->Level2Btn->isClicked(this->window))
        {
            this->isMouseBtnPressed = true;
            this->currentLvl = this->Level2Btn->getValue();
        }
        // Poziom 3
        if (this->Level3Btn->isClicked(this->window))
        {
            this->isMouseBtnPressed = true;
            this->currentLvl = this->Level3Btn->getValue();
        }
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
        this->musicBtn->render(this->window);
        break;

    case 1:
        this->GameplayScreenLvl1->render(this->window);
        break;

    case 2:
        this->window.draw(this->LevelsTitle);
        this->Level1Btn->render(this->window);
        this->Level2Btn->render(this->window);
        this->Level3Btn->render(this->window);
        this->Level4Btn->render(this->window);
        this->Level5Btn->render(this->window);
        this->Level6Btn->render(this->window);
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
