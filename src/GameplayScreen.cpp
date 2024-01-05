#include "pch.h"
#include "GameplayScreen.h"
#include "Button.h"

void GameplayScreen::initAssets()
{
    // Ladowanie fontow
    if (!(this->font.loadFromFile("assets/fonts/Inter-SemiBold.ttf")))
        std::cout << "ERROR::GameplayScreen::FONTS - Inter-SemiBold.ttf";

    // Ladowanie tekstur blokow
    if (!(this->obstaclesTexture.loadFromFile("assets/obstacles.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - obstacles.png\n";
    this->obstaclesTexture.setSmooth(true);

    // Tekstura dolka
    if (!(this->holeTexture.loadFromFile("assets/hole.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - hole.png\n";
    this->holeTexture.setSmooth(true);

    // Tekstury ekranu wygranej / przegranej
    if (!(this->winBgTexture.loadFromFile("assets/win_screen_bg.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - win_screen_bg.png\n";
    this->winBgTexture.setSmooth(true);
    if (!(this->loseBgTexture.loadFromFile("assets/lose_screen_bg.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - lose_screen_bg.png\n";
    this->loseBgTexture.setSmooth(true);
    if (!(this->gameFinishedBgTexture.loadFromFile("assets/game_finished_texture.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - game_finished_texture.png\n";
    this->gameFinishedBgTexture.setSmooth(true);
    if (!(this->replayBtnTexture.loadFromFile("assets/repeat_btn.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - repeat_btn.png\n";
    this->replayBtnTexture.setSmooth(true);
    if (!(this->nextLvlBtnTexture.loadFromFile("assets/next_lvl_btn.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - next_lvl_btn.png\n";
    this->nextLvlBtnTexture.setSmooth(true);
}
void GameplayScreen::initCourse()
{
    // Inicjalizaja pola
    this->course.setFillColor(sf::Color(146, 186, 59, 255)); // Kolor
    this->course.setSize(sf::Vector2f(1024, 512));           // Rozmiar
    this->course.setOrigin(sf::Vector2f(1024 / 2, 512 / 2)); // Origin - srodek pola
    this->course.setPosition(sf::Vector2f(600, 350 + 50));   // Pozycja - srodek ekranu (lekko przesuniete w dol)

    this->course.setOutlineColor(sf::Color(108, 88, 76, 255));
    this->course.setOutlineThickness(this->borderThickness);
}
void GameplayScreen::initLvlTitle()
{
    // Inicjalizacja tytulu
    // Ustawienie napisu
    this->setNewString(sf::String("Lvl: " + std::to_string(this->lvl)), this->titleText);

    this->titleText.setFont(this->font);                      // Czcionka
    this->titleText.setFillColor(sf::Color(30, 48, 80, 255)); // Kolor
    this->titleText.setOrigin(sf::Vector2f(                   // Origin - srodek dolnej krawedzi
        this->titleText.getGlobalBounds().width / 2,
        this->titleText.getGlobalBounds().height + 9));
    this->titleText.setPosition(sf::Vector2f( // Pozycja - nad polem
        1200 / 2,
        this->course.getGlobalBounds().top - 20));
}
void GameplayScreen::initMaxStrokesTitle()
{
    // Inicjalizacja maks. liczby uderzen
    this->setNewString(sf::String("Strzaly: " + std::to_string(this->strokesLeft)), this->leftStrokesText); // Napis
    this->leftStrokesText.setFont(this->font);                                                              // Czcionka
    this->leftStrokesText.setCharacterSize(20);                                                             // Rozmiar
    this->leftStrokesText.setFillColor(sf::Color(30, 48, 80, 255));                                         // Kolor
    this->leftStrokesText.setOrigin(sf::Vector2f(                                                           // Origin - lewy dol
        this->leftStrokesText.getGlobalBounds().left,
        this->leftStrokesText.getGlobalBounds().height));
    this->leftStrokesText.setPosition(sf::Vector2f( // Pozycja - nad polem z lewej strony
        this->course.getGlobalBounds().left,
        this->course.getGlobalBounds().top - 20));
}
void GameplayScreen::setUpObstacles()
{
    // 0 - light grass
    // 1 - dark grass
    // 2 - rock
    // 3 - sand
    // 4 - ice
    // 5 - gulf
    // 6 - water up
    // 7 - water down

    // Czyszczenie vektorow, na wypadek gdyby byly zajete
    for (int i = 0; i < 7; i++)
    {
        this->obstaclesVectorsArr[i].clear();
    }
    // this->grassVector.clear();
    // this->wallsVector.clear();
    // this->sandVector.clear();
    // this->iceVector.clear();
    // this->gulfsVector.clear();
    // this->water_upVector.clear();
    // this->water_downVector.clear();

    // Dodawania spriteow do odpowiednich vektorow
    // Iteracja przez wiersze tabeli
    for (int i = 0; i < this->gridRows; i++)
    {
        // Iteracja przez kolumny w kazdym wierszu
        for (int j = 0; j < this->gridCols; j++)
        {
            // Sprite reprezentujacy przeszkode
            sf::Sprite s;
            // Ustawienie tekstury
            s.setTexture(this->obstaclesTexture);
            s.setTextureRect(sf::IntRect(64 * this->logicalMap[i][j], 0, 64, 64));
            // Ustawienie pozycji przeszkodu
            s.setPosition(sf::Vector2f(
                this->course.getGlobalBounds().left + this->borderThickness + (j * 64),
                this->course.getGlobalBounds().top + this->borderThickness + (i * 64)));

            int logicValue = this->logicalMap[i][j];
            // Dodanie tekstury do odpowiedniego vektora
            if (logicValue == 0 || logicValue == 1)
            {
                this->obstaclesVectorsArr[0].push_back(s);
            }
            else
            {
                this->obstaclesVectorsArr[logicValue - 1].push_back(s);
            }
            // switch (this->logicalMap[i][j])
            // {
            // case 0:
            //     this->grassVector.push_back(s);
            //     break;

            // case 1:
            //     this->grassVector.push_back(s);
            //     break;

            // case 2:
            //     this->wallsVector.push_back(s);
            //     break;

            // case 3:
            //     this->sandVector.push_back(s);
            //     break;
            // case 4:
            //     this->iceVector.push_back(s);
            //     break;
            // case 5:
            //     this->gulfsVector.push_back(s);
            //     break;

            // case 6:
            //     this->water_upVector.push_back(s);
            //     break;
            // case 7:
            //     this->water_downVector.push_back(s);
            //     break;

            // default:
            //     break;
            // }
        }
    }
}

GameplayScreen::GameplayScreen(int &currentLvl, sf::Texture &ballsTexture, int ballSkin)
{
    // Ladowanie fontow i tekstur
    this->initAssets();

    // Inicjalizacja zmiennych
    this->gameState = -1;
    this->gridRows = 8;         // Ilosc rzedow
    this->gridCols = 16;        // Ilosc kolumn
    this->borderThickness = 15; // Grubosc drewnianego ogrodzenia

    // Odczyt poziomu z pliku i zapisanie go do zmiennych
    this->readLvlFromFile(currentLvl);

    // Inicjalizacja pola
    this->initCourse();

    // Inicjalizacja tytulu z lvlem
    this->initLvlTitle();

    // Inicjalizacja maks. liczby uderzen
    this->initMaxStrokesTitle();

    // Inicjalizacja planszy (przeszkod)
    this->setUpObstacles();

    // Inicjalizacja dolka
    this->hole.setTexture(this->holeTexture);
    this->hole.setOrigin(sf::Vector2f(
        this->hole.getGlobalBounds().width / 2,
        this->hole.getGlobalBounds().height / 2));
    this->hole.setPosition(sf::Vector2f(1000 + 40, 350 + 50));

    // Inicjalizacja pilki
    this->ball = new Ball(ballsTexture, ballSkin);

    // Inicjalizacja ekranu wygranej / przegranej
    this->endGameScreen.setTexture(this->winBgTexture); // Musimy ustawic, zeby mial jakies wymiary
    this->endGameScreen.setOrigin(sf::Vector2f(this->endGameScreen.getGlobalBounds().width / 2, this->endGameScreen.getGlobalBounds().height / 2));
    this->endGameScreen.setPosition(sf::Vector2f(600, 350));
    this->replayBtn = new Button(this->replayBtnTexture, sf::Vector2f(600 - 80, 375), -1);
    this->nextLvlBtn = new Button(this->nextLvlBtnTexture, sf::Vector2f(600 + 80, 375), -1);
}
GameplayScreen::~GameplayScreen()
{
    delete this->ball;
    delete this->replayBtn;
    delete this->nextLvlBtn;
}

void GameplayScreen::setNewString(sf::String newString, sf::Text &text)
{
    text.setString(newString);
}

void GameplayScreen::readLvlFromFile(int currentLvl)
{
    std::string pathToFile = "data/lvl_" + std::to_string(currentLvl) + ".txt";

    std::fstream odczyt;
    int logicalValue; // Logiczna wartosc pola

    odczyt.open(pathToFile, std::ios::in);
    if (!odczyt.good())
    {
        std::cout << "ERROR::GameplayScreen.cpp: Nie udalo sie odczytac poziomu z pliku" << std::endl;
        exit(0);
    }

    odczyt >> this->lvl;
    odczyt >> this->strokesLimit;
    this->strokesLeft = this->strokesLimit;

    for (int i = 0; i < gridRows; ++i)
    {
        for (int j = 0; j < gridCols; ++j)
        {
            odczyt >> logicalValue;
            logicalMap[i][j] = logicalValue; // Wypelnienie tablicy z logiczna reprezentacja pol
        }
    }

    odczyt.close();
}

void GameplayScreen::courseBordersCollision()
{
    sf::FloatRect courseBounds = this->course.getGlobalBounds();
    float courseT = courseBounds.top + this->borderThickness;
    float courseB = courseBounds.top + courseBounds.height - this->borderThickness;
    float courseL = courseBounds.left + this->borderThickness;
    float courseR = courseBounds.left + courseBounds.width - this->borderThickness;

    sf::FloatRect ballBounds = this->ball->getGlobalBounds();

    // Gora
    if (ballBounds.top <= courseT)
    {
        this->ball->setPositionY(courseT + ballBounds.height / 2);
        this->ball->setVelocityY(this->ball->getVelocity().y * -1);
    }
    // Dol
    else if (ballBounds.top + ballBounds.height >= courseB)
    {
        this->ball->setPositionY(courseB - ballBounds.height / 2);
        this->ball->setVelocityY(this->ball->getVelocity().y * -1);
    }
    // Lewo
    if (ballBounds.left <= courseL)
    {
        this->ball->setPositionX(courseL + ballBounds.width / 2);
        this->ball->setVelocityX(this->ball->getVelocity().x * -1);
    }
    // Prawo
    else if (ballBounds.left + ballBounds.width >= courseR)
    {
        this->ball->setPositionX(courseR - ballBounds.width / 2);
        this->ball->setVelocityX(this->ball->getVelocity().x * -1);
    }
}
void GameplayScreen::grassCollision()
{
    sf::FloatRect ballBounds = this->ball->getGlobalBounds(); // Pozycja pilki w AKTUALNIEJ klatce
    std::vector<sf::Sprite> vector = this->obstaclesVectorsArr[0];

    float friction = 0.96f;
    float stopTreshold = 0.35;

    for (int i = 0; i < vector.size(); i++)
    {
        sf::FloatRect grassBounds = vector[i].getGlobalBounds();

        // Sprawdzenie czy w nastepnej klatce nastapi kolizja
        if (ballBounds.intersects(grassBounds))
        {
            if (this->ball->getFriction() != friction)
                this->ball->setFriction(friction);
            if (this->ball->getStopTreshold() != stopTreshold)
                this->ball->setStopTreshold(stopTreshold);
        }
    }
}
void GameplayScreen::wallsCollision()
{
    sf::FloatRect ballBounds = this->ball->getGlobalBounds(); // Pozycja pilki w AKTUALNIEJ klatce
    sf::FloatRect nextPosBounds = ballBounds;                 // Pozycja pilki w NASTEPNEJ klatce
    nextPosBounds.left += this->ball->getVelocity().x;
    nextPosBounds.top += this->ball->getVelocity().y;

    std::vector<sf::Sprite> vector = this->obstaclesVectorsArr[1];

    for (int i = 0; i < vector.size(); i++)
    {
        sf::FloatRect wallBounds = vector[i].getGlobalBounds();

        // Sprawdzenie czy w nastepnej klatce nastapi kolizja
        if (nextPosBounds.intersects(wallBounds))
        {
            // Lewa
            if (
                ballBounds.left < wallBounds.left &&
                ballBounds.left + ballBounds.width < wallBounds.left + wallBounds.width &&
                ballBounds.top < wallBounds.top + wallBounds.height &&
                ballBounds.top + ballBounds.height > wallBounds.top)
            {
                nextPosBounds = ballBounds;
                this->ball->setVelocityX(this->ball->getVelocity().x * -1);
            }
            // Prawa
            else if (
                ballBounds.left > wallBounds.left &&
                ballBounds.left + ballBounds.width > wallBounds.left + wallBounds.width &&
                ballBounds.top < wallBounds.top + wallBounds.height &&
                ballBounds.top + ballBounds.height > wallBounds.top)
            {
                nextPosBounds = ballBounds;
                this->ball->setVelocityX(this->ball->getVelocity().x * -1);
            }

            // Gora
            if (
                ballBounds.top < wallBounds.top &&
                ballBounds.top + ballBounds.height < wallBounds.top + wallBounds.height &&
                ballBounds.left < wallBounds.left + wallBounds.width &&
                ballBounds.left + ballBounds.width > wallBounds.left)
            {
                nextPosBounds = ballBounds;
                this->ball->setVelocityY(this->ball->getVelocity().y * -1);
            }
            // Dol
            else if (
                ballBounds.top > wallBounds.top &&
                ballBounds.top + ballBounds.height > wallBounds.top + wallBounds.height &&
                ballBounds.left < wallBounds.left + wallBounds.width &&
                ballBounds.left + ballBounds.width > wallBounds.left)
            {
                nextPosBounds = ballBounds;
                this->ball->setVelocityY(this->ball->getVelocity().y * -1);
            }
        }
    }
}
void GameplayScreen::sandCollision()
{
    sf::FloatRect ballBounds = this->ball->getGlobalBounds(); // Pozycja pilki w AKTUALNIEJ klatce
    float friction = 0.5f;

    std::vector<sf::Sprite> vector = this->obstaclesVectorsArr[2];

    for (int i = 0; i < vector.size(); i++)
    {
        sf::FloatRect sandBounds = vector[i].getGlobalBounds();

        // Sprawdzenie czy w nastepnej klatce nastapi kolizja
        if (ballBounds.intersects(sandBounds) && this->ball->getFriction() != friction)
        {
            this->ball->setFriction(friction);
        }
    }
}
void GameplayScreen::iceCollision()
{
    sf::FloatRect ballBounds = this->ball->getGlobalBounds(); // Pozycja pilki w AKTUALNIEJ klatce
    float friction = 0.97f;
    float stopTreshold = 0.1f;

    std::vector<sf::Sprite> vector = this->obstaclesVectorsArr[3];

    for (int i = 0; i < vector.size(); i++)
    {
        sf::FloatRect iceBounds = vector[i].getGlobalBounds();

        // Sprawdzenie czy pilka styka sie z lodem
        if (ballBounds.intersects(iceBounds))
        {
            if (this->ball->getFriction() != friction)
                // Zmniejszenie predkosci pilki
                this->ball->setFriction(0.99);

            if (this->ball->getStopTreshold() != stopTreshold)
                this->ball->setStopTreshold(stopTreshold);
        }
    }
}
void GameplayScreen::gulfCollision()
{
    sf::FloatRect ballBounds = this->ball->getGlobalBounds(); // Pozycja pilki w AKTUALNIEJ klatce

    std::vector<sf::Sprite> vector = this->obstaclesVectorsArr[4];
    for (int i = 0; i < vector.size(); i++)
    {
        sf::FloatRect gulfBounds = vector[i].getGlobalBounds();

        // Sprawdzenie czy pilka styka sie z przepascia
        if (ballBounds.intersects(gulfBounds))
        {
            // Sprawdzenie czy srodek pilki 'wpadl' do srodka
            if (
                this->ball->getPosition().x >= gulfBounds.left &&
                this->ball->getPosition().x <= gulfBounds.left + gulfBounds.width &&
                this->ball->getPosition().y >= gulfBounds.top &&
                this->ball->getPosition().y <= gulfBounds.top + gulfBounds.height)
            {

                std::cout << "Przpeascccccc\n";
                this->ball->setVelocityX(0);
                this->ball->setVelocityY(0);
                this->ball->setScale(0.1);

                this->gameState = 0; // Przegralismy
                this->endGameScreen.setTexture(this->loseBgTexture);
            }
        }
    }
}
void GameplayScreen::waterupCollision()
{
    sf::FloatRect ballBounds = this->ball->getGlobalBounds(); // Pozycja pilki w AKTUALNIEJ klatce

    std::vector<sf::Sprite> vector = this->obstaclesVectorsArr[5];

    for (int i = 0; i < vector.size(); i++)
    {
        sf::FloatRect waterBounds = vector[i].getGlobalBounds();
        float k = 0.8;
        float l = 1.1;
        // Sprawdzenie czy w nastepnej klatce nastapi kolizja
        if (ballBounds.intersects(waterBounds))
        {
            // Zmniana predkosci pilki
            this->ball->setVelocityY((-fabs(this->ball->getVelocity().y)) * l);
            // if (this->ball->getVelocity().y != 0)
            // {
            //     this->tikker++;
            // }
            // std::cout<<tikker<<"\n";
            // if (tikker >= 250)
            // {
            //     this->ball->setVelocityY(0);
            //     this->tikker = 0;
            // }
            if (fabs(this->ball->getVelocity().y) > 7)
            {
                this->ball->setVelocityY(this->ball->getVelocity().y / 2);
            }
            else if (fabs(this->ball->getVelocity().y) >= 4)
            {
                this->ball->setVelocityX(this->ball->getVelocity().x * 5);
            }
            else
            {
                this->ball->setVelocityX(this->ball->getVelocity().x / l);
            }
            if (fabs(this->ball->getVelocity().x) >= 2)
            {
                this->ball->setVelocityX(this->ball->getVelocity().x / 10);
            }
        }
    }
}
void GameplayScreen::waterdownCollision()
{
    sf::FloatRect ballBounds = this->ball->getGlobalBounds(); // Pozycja pilki w AKTUALNIEJ klatce

    std::vector<sf::Sprite> vector = this->obstaclesVectorsArr[6];

    for (int i = 0; i < vector.size(); i++)
    {
        sf::FloatRect waterBounds = vector[i].getGlobalBounds();
        float k = 0.8;
        float l = 1.1;
        // Sprawdzenie czy w nastepnej klatce nastapi kolizja
        if (ballBounds.intersects(waterBounds))
        {
            // Zmniana predkosci pilki
            this->ball->setVelocityY((fabs(this->ball->getVelocity().y)) * l);
            // if (this->ball->getVelocity().y != 0)
            // {
            //     this->tikker++;
            // }
            // // std::cout<<tikker<<"\n";
            // if (tikker >= 250)
            // {
            //     this->ball->setVelocityY(0);
            //     this->tikker = 0;
            // }
            // std::cout<<this->ball->getVelocity().y<<"\n";
            if (fabs(this->ball->getVelocity().y) > 7)
            {
                this->ball->setVelocityY(this->ball->getVelocity().y / 2);
            }
            else if (fabs(this->ball->getVelocity().y) >= 4)
            {
                this->ball->setVelocityX(this->ball->getVelocity().x * 5);
            }
            else
            {
                this->ball->setVelocityX(this->ball->getVelocity().x / l);
            }
            if (fabs(this->ball->getVelocity().x) >= 2)
            {
                this->ball->setVelocityX(this->ball->getVelocity().x / 10);
            }
        }
    }
}
void GameplayScreen::holeCollision(int allLvls)
{
    sf::FloatRect ballBounds = this->ball->getGlobalBounds();
    sf::FloatRect holeBounds = this->hole.getGlobalBounds();
    // Sprawdzenie, czy pilka przelatuje przez dolek
    if (ballBounds.intersects(holeBounds))
    {
        // Sprawdzenie czy srodek pilki jest odpowiednio blisko srodka dolka
        sf::Vector2f ballPos = this->ball->getPosition();
        sf::Vector2f ballVel = this->ball->getVelocity();
        sf::Vector2f holePos = this->hole.getPosition();

        float distance = sqrt(pow(ballPos.x - holePos.x, 2) + pow(ballPos.y - holePos.y, 2) * 1.f);
        float ballSpeed = sqrt(pow(ballVel.x, 2) + pow(ballVel.y, 2) * 1.f);

        if (distance < 10.f && ballSpeed < 5.f)
        {
            this->ball->setVelocityX(0);
            this->ball->setVelocityY(0);
            this->ball->setPositionX(holePos.x);
            this->ball->setPositionY(holePos.y);

            this->gameState = 1; // Wygralismy
            this->endGameScreen.setTexture(this->winBgTexture);

            if (this->lvl >= allLvls)
                this->endGameScreen.setTexture(this->gameFinishedBgTexture);
        }
    }
}
void GameplayScreen::ObstaclesCollisions()
{
    // Kolizja z trawa
    this->grassCollision();
    // Kolizja z piaskiem
    this->sandCollision();
    // Kolizja z lodem
    this->iceCollision();
    // Kolizja z polem
    this->courseBordersCollision();
    // Kolizja z przepascia
    this->gulfCollision();
    // Kolizja z woda
    this->waterupCollision();
    this->waterdownCollision();
}
void GameplayScreen::update(sf::WindowBase &window, int &prevLvl, int &currentLvl, int allLvls, int &unlockedLvls, bool &isMouseBtnPressed)
{
    // Gramy
    if (this->gameState == -1)
    {
        // Kolizja ze scianami
        this->wallsCollision();

        this->ball->update(window, this->strokesLeft, this->gameState, isMouseBtnPressed);

        // Zmniejszenie liczby uderzen
        this->setNewString(sf::String("Strzaly: " + std::to_string(this->strokesLeft)), this->leftStrokesText);

        this->ObstaclesCollisions();

        this->holeCollision(allLvls);

        // Poczekanie az pilka sie zatrzyma i sprawdzenie czy przypadkiem juz nie przegralismy
        if (!this->ball->isMoving && this->strokesLeft <= 0)
        {
            this->gameState = 0; // Zmienienie stanu gry na ekran z przegrana
            this->endGameScreen.setTexture(this->loseBgTexture);
        }
    }
    // Przegralismy
    else if (this->gameState == 0)
    {
        // Obsluga przycisku replay
        if (
            this->replayBtn->isClicked(window) && // Kliknelismy przycisk replay
            !isMouseBtnPressed                    // Nie jest klikniety jakis inny przycisk
        )
        {
            isMouseBtnPressed = true;
            this->gameState = -1; // Zmiana stanu gry na granie
            // Zresetowanie ustawien
            this->strokesLeft = this->strokesLimit;
            this->ball->setPositionX(162);
            this->ball->setPositionY(350 + 50);
            this->ball->setScale(1);
        }
    }
    // Wygralismy
    else if (this->gameState == 1)
    {
        // Obsluga przycisku replay
        if (
            currentLvl != allLvls &&              // Nie wygralismy ostatniego poziomu
            this->replayBtn->isClicked(window) && // Kliknelismy przycisk replay
            !isMouseBtnPressed                    // Nie jest klikniety jakis inny przycisk
        )
        {
            isMouseBtnPressed = true;
            this->gameState = -1; // Zmiana stanu gry na granie
            // Zresetowanie ustawien
            this->strokesLeft = this->strokesLimit;
            this->ball->setPositionX(162);
            this->ball->setPositionY(350 + 50);
            this->ball->setScale(1);
        }

        // Obsluga przycisku next lvl
        if (
            currentLvl < allLvls &&                // Nie przeszlismy ostatniego poziomu
            this->nextLvlBtn->isClicked(window) && // Kliknelismy przycisk next lvl
            !isMouseBtnPressed                     // Nie jest klikniety jakis inny przycisk
        )
        {
            isMouseBtnPressed = true;

            // Kolejny lvl jest odblokowany
            if (currentLvl < unlockedLvls)
            {
                prevLvl = currentLvl;
                currentLvl++;
                this->lvl = currentLvl;
                this->gameState = -1;
            }
            else if (currentLvl == unlockedLvls && // Przeszlismy ostatni lvl, ktory mamy odblokowany
                     currentLvl < allLvls          // Jest jeszcze nastepny lvl
            )
            {
                unlockedLvls++;
                prevLvl = currentLvl;
                currentLvl++;
                this->lvl = currentLvl;
                this->gameState = -1;
            }

            // Ladowanie od nowa kolejnego poziomu
            // Wczytanie danych z pliku
            this->readLvlFromFile(this->lvl);

            // Aktualizacja tytulu
            this->setNewString(sf::String("Lvl: " + std::to_string(this->lvl)), this->titleText);

            // Liczba uderzen sama sie aktualizuje, wiec nie trzeba tego robic tutaj

            // Zaaktualizowanie wektorow ze spriteami
            this->setUpObstacles();

            // Ustawienie pilki na pozycje startowa

            this->ball->setPositionX(162);
            this->ball->setPositionY(350 + 50);
        }
    }
}

void GameplayScreen::render(sf::RenderTarget &target, int allLvls)
{
    target.draw(this->course);
    target.draw(this->titleText);
    target.draw(this->leftStrokesText);

    // Rysowanie wszystkich spriteow
    for (int i = 0; i < 7; i++)
    {
        std::vector<sf::Sprite> currentVector = this->obstaclesVectorsArr[i];
        for (int j = 0; j < currentVector.size(); j++)
        {
            target.draw(currentVector[j]);
        }
    }
    // for (int i = 0; i < this->grassVector.size(); i++) // Trawa
    //     target.draw(grassVector[i]);
    // for (int i = 0; i < this->wallsVector.size(); i++) // Sciany
    //     target.draw(wallsVector[i]);
    // for (int i = 0; i < this->sandVector.size(); i++) // Piasek
    //     target.draw(sandVector[i]);
    // for (int i = 0; i < this->iceVector.size(); i++) // Lod
    //     target.draw(iceVector[i]);
    // for (int i = 0; i < this->gulfsVector.size(); i++) // Przepasc
    //     target.draw(gulfsVector[i]);
    // for (int i = 0; i < this->water_upVector.size(); i++) // Woda gora
    //     target.draw(water_upVector[i]);
    // for (int i = 0; i < this->water_downVector.size(); i++) // Woda dol
    //     target.draw(water_downVector[i]);

    target.draw(this->hole); // Dolek

    this->ball->render(target, this->gameState);

    // Ewentualny ekran wygranej / przegranej / konca gry
    if (this->gameState != -1)
    {
        // ekran wygranej / przegranej /konca gry
        target.draw(this->endGameScreen);

        // replayBtn
        // Jezeli wygralismy ostatni poziom to nie pokazuj
        if (!(this->lvl == allLvls && this->gameState == 1))
            this->replayBtn->render(target);

        // next lvl btn
        // Jezeli nie jestesmy na ostatnim poziomie i wygralismy
        if (this->lvl < allLvls && this->gameState == 1)
            this->nextLvlBtn->render(target);
    }
}