#include "pch.h"
#include "Game.h"
#include "GameplayScreen.h"

void Game::initAssets()
{
    // Font
    if (!this->InterBlack.loadFromFile("../assets/fonts/Inter-Black.ttf"))
    {
        std::cout << "ERROR::FONTS - Inter-Black.ttf\n";
    }

    // Ladowanie textur
    // Tlo
    if (!(this->mainBgTexture.loadFromFile("../assets/background.png")))
        std::cout
            << "ERROR::TEXTURES - background.png\n";
    this->mainBgTexture.setSmooth(true); // Wyrownanie krawedzi

    // Play btn
    if (!(this->playBtnTexture.loadFromFile("../assets/play_btn.png")))
        std::cout << "ERROR::TEXTURES - play_btn.png\n";
    this->playBtnTexture.setSmooth(true); // Wyrownanie krawedzi

    // Lvls btn
    if (!(this->lvlsBtnTexture.loadFromFile("../assets/poziomy_btn.png")))
        std::cout << "ERROR::TEXTURES - poziomy_btn.png\n";
    this->lvlsBtnTexture.setSmooth(true); // Wyrownanie krawedzi

    // Options btn
    if (!(this->optionsBtnTexture.loadFromFile("../assets/ustawienia_btn.png")))
        std::cout << "ERROR::TEXTURES - ustawienia_btn.png\n";
    this->optionsBtnTexture.setSmooth(true); // Wyrownanie krawedzi

    // Exit btn
    if (!(this->exitBtnTexture.loadFromFile("../assets/exit_icon.png")))
        std::cout << "ERROR::TEXTURES - exit_icon.png\n";
    this->exitBtnTexture.setSmooth(true); // Wyrownanie krawedzi

    // Music btn
    if (!(this->musicBtnTexture.loadFromFile("../assets/music.png")))
        std::cout << "ERROR::TEXTURES - music.png\n";
    this->musicBtnTexture.setSmooth(true); // Wyrownanie krawedzi
    //Plus and Minus (volume) btn
    if (!(this->PlusTexture.loadFromFile("../assets/Plus.png")))
        std::cout << "ERROR::TEXTURES - music.png\n";
    this->PlusTexture.setSmooth(true); // Wyrownanie krawedzi
    if (!(this->MinusTexture.loadFromFile("../assets/Minus.png")))
        std::cout << "ERROR::TEXTURES - music.png\n";
    this->MinusTexture.setSmooth(true); // Wyrownanie krawedzi

    //Piłki w menu
    if (!(this->WhiteBallTexture.loadFromFile("../assets/ball_white.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - ball_white.png\n";
    this->WhiteBallTexture.setSmooth(true);

    if (!(this->RedBallTexture.loadFromFile("../assets/ball_red.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - ball_red.png\n";
    this->RedBallTexture.setSmooth(true);

    if (!(this->BlueBallTexture.loadFromFile("../assets/ball_blue.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - ball_blue.png\n";
    this->BlueBallTexture.setSmooth(true);

    if (!(this->YellowBallTexture.loadFromFile("../assets/ball_yellow.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - ball_yellow.png\n";
    this->YellowBallTexture.setSmooth(true);

    if (!(this->MinusTexture.loadFromFile("../assets/Minus.png")))
        std::cout << "ERROR::TEXTURES - music.png\n";
    this->MinusTexture.setSmooth(true); // Wyrownanie krawedzi
    
    // Level 1 - przycisk
    if (!(this->Level1BtnTexture.loadFromFile("../assets/l1_btn.png")))
        std::cout << "ERROR::TEXTURES - l1_btn.png\n";
    this->Level1BtnTexture.setSmooth(true);

    // Level 2 - przycisk
    if (!(this->Level2BtnTexture.loadFromFile("../assets/l2_btn.png")))
        std::cout << "ERROR::TEXTURES - l2_btn.png\n";
    this->Level2BtnTexture.setSmooth(true);

    // Level 3 - przycisk
    if (!(this->Level3BtnTexture.loadFromFile("../assets/l3_btn.png")))
        std::cout << "ERROR::TEXTURES - l3_btn.png\n";
    this->Level3BtnTexture.setSmooth(true);

    // Level 4 - przycisk
    if (!(this->Level4BtnTexture.loadFromFile("../assets/l4_btn.png")))
        std::cout << "ERROR::TEXTURES - l4_btn.png\n";
    this->Level4BtnTexture.setSmooth(true);

    // Level 5 - przycisk
    if (!(this->Level5BtnTexture.loadFromFile("../assets/l5_btn.png")))
        std::cout << "ERROR::TEXTURES - l5_btn.png\n";
    this->Level5BtnTexture.setSmooth(true);

    // Level 6 - przycisk
    if (!(this->Level6BtnTexture.loadFromFile("../assets/l6_btn.png")))
        std::cout << "ERROR::TEXTURES - l6_btn.png\n";
    this->Level6BtnTexture.setSmooth(true);
    // Ladowanie muzyki
    volume = 1.f;
    this->backgroundMusic.openFromFile("../assets/background_music.ogg");
    this->backgroundMusic.setVolume(volume);
    // this->backgroundMusic.play();
    this->backgroundMusic.setLoop(true);
}

Game::Game()
{
    //this->currentLvl = 1;

    // Przypisanie sciezek do plikow z poziomami do tablicy
    this->lvlsPathArrayLength = sizeof(this->lvlsPathArray) / sizeof(std::string);
    for (int i = 0; i < lvlsPathArrayLength; i++)
    {
        std::string lvlNum = std::to_string(i + 1);
        std::string path = "../data/lvl_" + lvlNum + ".txt";
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

    this->musicBtn = new Button(this->musicBtnTexture, sf::Vector2f(1120, 30), -1);
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
    // Napisy w opcjach
    this->OptionsTitle1.setString("Sound ON\t\t\t\t\tSound OFF");// Napis
    this->OptionsTitle1.setFont(this->InterBlack);                // Czcionka
    this->OptionsTitle1.setFillColor(sf::Color(30, 48, 80, 255)); // Kolor
    this->OptionsTitle1.setCharacterSize(15);
    this->OptionsTitle1.setOrigin(sf::Vector2f( // Origin - srodek dolnej krawedzi
    this->OptionsTitle1.getGlobalBounds().width / 2,
    this->OptionsTitle1.getGlobalBounds().height + 9));
    this->OptionsTitle1.setPosition(sf::Vector2f(600, 75));

    this->OptionsTitle2.setString("Change volume");// Napis
    this->OptionsTitle2.setFont(this->InterBlack);                // Czcionka
    this->OptionsTitle2.setFillColor(sf::Color(30, 48, 80, 255)); // Kolor
    this->OptionsTitle2.setCharacterSize(20);
    this->OptionsTitle2.setOrigin(sf::Vector2f( // Origin - srodek dolnej krawedzi
    this->OptionsTitle2.getGlobalBounds().width / 2,
    this->OptionsTitle2.getGlobalBounds().height + 9));
    this->OptionsTitle2.setPosition(sf::Vector2f(500, 210));

    this->OptionsTitle3.setString("Wybierz kolor pilki");// Napis
    this->OptionsTitle3.setFont(this->InterBlack);                // Czcionka
    this->OptionsTitle3.setFillColor(sf::Color(30, 48, 80, 255)); // Kolor
    this->OptionsTitle3.setCharacterSize(20);
    this->OptionsTitle3.setOrigin(sf::Vector2f( // Origin - srodek dolnej krawedzi
    this->OptionsTitle3.getGlobalBounds().width / 2,
    this->OptionsTitle3.getGlobalBounds().height + 9));
    this->OptionsTitle3.setPosition(sf::Vector2f(600, 350));

    float lvlsTopOffset = 300;
    float lvlsLineHeight = 200;
    this->Level1Btn = new Button(this->Level1BtnTexture, sf::Vector2f(600 - 200, lvlsTopOffset), 1);
    this->Level2Btn = new Button(this->Level2BtnTexture, sf::Vector2f(600, lvlsTopOffset), 2);
    this->Level3Btn = new Button(this->Level3BtnTexture, sf::Vector2f(600 + 200, lvlsTopOffset), 3);
    this->Level4Btn = new Button(this->Level4BtnTexture, sf::Vector2f(600 - 200, lvlsTopOffset + lvlsLineHeight), 4);
    this->Level5Btn = new Button(this->Level5BtnTexture, sf::Vector2f(600, lvlsTopOffset + lvlsLineHeight), 5);
    this->Level6Btn = new Button(this->Level6BtnTexture, sf::Vector2f(600 + 200, lvlsTopOffset + lvlsLineHeight), 5);

    // Screen 3 ----------------
    this->musiconBtn = new Button(this->musicBtnTexture, sf::Vector2f(400, 75), -1);
    this->musicoffBtn = new Button(this->musicBtnTexture, sf::Vector2f(800, 75), -1);
    this->musiconBtn->setTextureRect(sf::IntRect(0, 0, 34, 34));
    this->musicoffBtn->setTextureRect(sf::IntRect(34, 0, 34, 34));
    this->Minus = new Button(this->MinusTexture, sf::Vector2f(650, 200), -1);
    this->Plus = new Button(this->PlusTexture, sf::Vector2f(800, 200), -1);
    this->WhiteBall = new Button(this->WhiteBallTexture, sf::Vector2f(450, 400), -1);
    this->RedBall = new Button(this->RedBallTexture, sf::Vector2f(550, 400), -1);
    this->BlueBall = new Button(this->BlueBallTexture, sf::Vector2f(650, 400), -1);
    this->YellowBall = new Button(this->YellowBallTexture, sf::Vector2f(750, 400), -1);
    // All screens -------------
    this->exitBtn = new Button(this->exitBtnTexture, sf::Vector2f(1200 - 35, 30), 0);
    this->currentBall=2;
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

    //Screen 3 -----------------
    delete this->musiconBtn;
    delete this->musicoffBtn;
    delete this->Plus;
    delete this->Minus;
    delete  this->WhiteBall;
    delete  this->RedBall;
    delete  this->BlueBall;
    delete  this->YellowBall;
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
    this->musiconBtn->updateHover(this->window);
    this->musicoffBtn->updateHover(this->window);
    this->Plus->updateHover(this->window);
    this->Minus->updateHover(this->window);
    this->WhiteBall->updateHover(this->window);
    this->RedBall->updateHover(this->window);
    this->BlueBall->updateHover(this->window);
    this->YellowBall->updateHover(this->window);

    // Dzialanie przycisku exit
    if (this->gameScreen == 1 || this->gameScreen == 2 || this->gameScreen == 3)
    {
        // Spraawdzenie czy przycisk jest klikniety
        if (this->exitBtn->isClicked(this->window) && !this->isMouseBtnPressed)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            this->currentLvl = 1;
            this->isMouseBtnPressed = true;
            this->gameScreen = this->playBtn->getValue();
            this->GameplayScreenLvl1 = new GameplayScreen(this->lvlsPathArray[this->currentLvl - 1]);
        }
        else if (this->lvlsBtn->isClicked(this->window) && !this->isMouseBtnPressed)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            this->isMouseBtnPressed = true;
            this->gameScreen = this->lvlsBtn->getValue();
            std::cout << "POZIOMY zostal wcisniety\n";
        }
        else if (this->optionsBtn->isClicked(this->window) && !this->isMouseBtnPressed)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                this->musicIsOn = false;
                this->musicBtn->setTextureRect(sf::IntRect(34, 0, 34, 34));
                this->backgroundMusic.pause(); // Zatrzymanie muzyki
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                this->musicIsOn = true;
                this->musicBtn->setTextureRect(sf::IntRect(0, 0, 34, 34));
                this->backgroundMusic.play(); // Wznowienie muzyki
            }
        }
    }
    else if (this->gameScreen == 1)
    {
        this->GameplayScreenLvl1->update(this->window, this->lvlsPathArray, this->lvlsPathArrayLength, this->currentLvl, this->isMouseBtnPressed);
        //std::cout << "game.cpp " << this->currentLvl << std::endl;
    }
    else if (this->gameScreen == 2)
    {
        // Wybor poziomu
        // Poziom 1
        if (this->Level1Btn->isClicked(this->window))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            this->currentLvl = 1;
            this->isMouseBtnPressed = true;
            this->gameScreen = this->playBtn->getValue();
            this->GameplayScreenLvl1 = new GameplayScreen(this->lvlsPathArray[this->currentLvl - 1]);
        }
        // Poziom 2
        if (this->Level2Btn->isClicked(this->window))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            this->currentLvl = 2;
            this->isMouseBtnPressed = true;
            this->gameScreen = this->playBtn->getValue();
            this->GameplayScreenLvl1 = new GameplayScreen(this->lvlsPathArray[this->currentLvl - 1]);
        }
        // Poziom 3
        if (this->Level3Btn->isClicked(this->window))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            this->currentLvl = 3;
            this->isMouseBtnPressed = true;
            this->gameScreen = this->playBtn->getValue();
            this->GameplayScreenLvl1 = new GameplayScreen(this->lvlsPathArray[this->currentLvl - 1]);
        }
        // Poziom 4
        if (this->Level4Btn->isClicked(this->window))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));            
            this->currentLvl = 4;
            this->isMouseBtnPressed = true;
            this->gameScreen = this->playBtn->getValue();
            this->GameplayScreenLvl1 = new GameplayScreen(this->lvlsPathArray[this->currentLvl - 1]);
        }
        // Poziom 5
        if (this->Level5Btn->isClicked(this->window))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            this->currentLvl = 5;
            this->isMouseBtnPressed = true;
            this->gameScreen = this->playBtn->getValue();
            this->GameplayScreenLvl1 = new GameplayScreen(this->lvlsPathArray[this->currentLvl - 1]);
        }
        // Poziom 6
        if (this->Level6Btn->isClicked(this->window))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            this->currentLvl = 6;
            this->isMouseBtnPressed = true;
            this->gameScreen = this->playBtn->getValue();
            this->GameplayScreenLvl1 = new GameplayScreen(this->lvlsPathArray[this->currentLvl - 1]);
        }
    }
    else if (this->gameScreen == 3)
    {
        if (this->musiconBtn->isClicked(this->window))
        {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                this->musicIsOn = true;
                this->backgroundMusic.play();
            
        }
        if (this->musicoffBtn->isClicked(this->window))
        {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                this->musicIsOn = false;
                this->backgroundMusic.pause();
        }
        if (this->Plus->isClicked(this->window))
        {       
            if(volume < 500){
                volume+=25.f;
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                this->backgroundMusic.setVolume(volume);
                }
        }
        if (this->Minus->isClicked(this->window))
        {       
            if(volume >1){
                volume-=25.f;
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                this->backgroundMusic.setVolume(volume);
            }
        }
        if (this->Minus->isClicked(this->window))
        {       
            if(volume >1){
                volume-=25.f;
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                this->backgroundMusic.setVolume(volume);
            }
        }
        if (this->WhiteBall->isClicked(this->window))
        {       
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            this->currentBall=1;
            std::cout<<currentBall;
        }
        if (this->BlueBall->isClicked(this->window))
        {       
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            this->currentBall=2;
            std::cout<<currentBall;
        }
        if (this->RedBall->isClicked(this->window))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            this->currentBall=3;   
            std::cout<<currentBall;    
        }
        if (this->YellowBall->isClicked(this->window))
        {       
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            this->currentBall=4;
            std::cout<<currentBall;
        }
        zap.open("../data/Ball.txt", std::ios::out);//zapisanie wybranego wariantu piłki do pliku
        zap<<currentBall<<std::endl;
        zap.close();
        //std::cout << "Ekran USTAWIENIA ejej\n";
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
        this->window.draw(this->OptionsTitle1);
        this->window.draw(this->OptionsTitle2);
        this->window.draw(this->OptionsTitle3);
        this->musiconBtn->render(this->window);
        this->musicoffBtn->render(this->window);
        this->Plus->render(this->window);
        this->Minus->render(this->window);
        this->WhiteBall->render(this->window);
        this->RedBall->render(this->window);
        this->BlueBall->render(this->window);
        this->YellowBall->render(this->window);
        //std::cout << "USTAWIENIA\n";
        break;

    default:
        std::cout << "ERROR: Nie ma takiego okna\n";
        break;
    }

    this->window.display();
}
