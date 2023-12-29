#include "pch.h"
#include "GameplayScreen.h"
#include "Button.h"

void GameplayScreen::initAssets()
{
    // Ladowanie fontow
    if (!(this->font.loadFromFile("../assets/fonts/Inter-SemiBold.ttf")))
        std::cout << "ERROR::GameplayScreen::FONTS - Inter-SemiBold.ttf";

    // Ladowanie tekstur blokow
    if (!(this->grassDarkTexture.loadFromFile("../assets/grass_dark.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - grass_dark.png\n";
    this->grassDarkTexture.setSmooth(true);
    if (!(this->grassLightTexture.loadFromFile("../assets/grass_light.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - grass_light.png\n";
    this->grassLightTexture.setSmooth(true);
    if (!(this->rockTexture.loadFromFile("../assets/rock.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - rock.png\n";
    this->rockTexture.setSmooth(true);
    if (!(this->sandTexture.loadFromFile("../assets/sand.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - sand.png\n";
    this->sandTexture.setSmooth(true);
    if (!(this->waterTexture.loadFromFile("../assets/water.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - water.png\n";
    this->waterTexture.setSmooth(true);
    if (!(this->iceTexture.loadFromFile("../assets/ice.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - ice.png\n";
    this->iceTexture.setSmooth(true);

    // Ladowanie tekstur pilek
    if (!(this->whiteBallTexture.loadFromFile("../assets/ball_white.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - ball_white.png\n";
    this->whiteBallTexture.setSmooth(true);

    // Tekstura dolka
    if (!(this->holeTexture.loadFromFile("../assets/hole.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - hole.png\n";
    this->holeTexture.setSmooth(true);

    // Tekstury ekranu wygranej / przegranej
    if (!(this->winBgTexture.loadFromFile("../assets/win_screen_bg.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - win_screen_bg.png\n";
    this->winBgTexture.setSmooth(true);
    if (!(this->loseBgTexture.loadFromFile("../assets/lose_screen_bg.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - lose_screen_bg.png\n";
    this->loseBgTexture.setSmooth(true);
    if (!(this->replayBtnTexture.loadFromFile("../assets/repeat_btn.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - repeat_btn.png\n";
    this->replayBtnTexture.setSmooth(true);
    if (!(this->nextLvlBtnTexture.loadFromFile("../assets/next_lvl_btn.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - next_lvl_btn.png\n";
    this->nextLvlBtnTexture.setSmooth(true);
}
void GameplayScreen::initCourse()
{
    // Inicjalizaja pola
    this->course.setFillColor(sf::Color(146, 186, 59, 255)); // Kolor
    this->course.setSize(sf::Vector2f(1000, 500));           // Rozmiar
    this->course.setOrigin(sf::Vector2f(1000 / 2, 500 / 2)); // Origin - srodek pola
    this->course.setPosition(sf::Vector2f(600, 350 + 50));   // Pozycja - srodek ekranu (lekko przesuniete w dol)

    this->course.setOutlineColor(sf::Color(108, 88, 76, 255));
    this->course.setOutlineThickness(this->borderThickness);
}
void GameplayScreen::initLvlTitle()
{
    // Inicjalizacja tytulu
    this->setTitleText(sf::String("Lvl: " + std::to_string(this->currentLvl))); // Ustawienie napisu

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
    this->setStrokesLimitText(sf::String("Strzaly: " + std::to_string(this->leftStrokes))); // Napis
    this->leftStrokesText.setFont(this->font);                                              // Czcionka
    this->leftStrokesText.setCharacterSize(20);                                             // Rozmiar
    this->leftStrokesText.setFillColor(sf::Color(30, 48, 80, 255));                         // Kolor
    this->leftStrokesText.setOrigin(sf::Vector2f(                                           // Origin - lewy dol
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
    // 4 - water
    // 5 - ice
    // Czyszczenie vektorow, na wypadek gdyby byly zajete
    this->grassVector.clear();
    this->wallsVector.clear();
    this->sandVector.clear();

    // Dodawania spriteow do odpowiednich vektorow
    for (int i = 0; i < this->gridRows; i++)
    {
        for (int j = 0; j < this->gridCols; j++)
        {
            sf::Sprite s;

            // Ustawienie pozycji
            s.setPosition(sf::Vector2f(
                this->course.getGlobalBounds().left + this->borderThickness + (j * 62.5),
                this->course.getGlobalBounds().top + this->borderThickness + (i * 62.5)));

            // Ustawienie tekstury
            switch (this->logicalMap[i][j])
            {
            case 0:
                s.setTexture(this->grassLightTexture);
                this->grassVector.push_back(s);
                break;

            case 1:
                s.setTexture(this->grassDarkTexture);
                this->grassVector.push_back(s);
                break;

            case 2:
                s.setTexture(this->rockTexture);
                this->wallsVector.push_back(s);
                break;

            case 3:
                s.setTexture(this->sandTexture);
                this->sandVector.push_back(s);
                break;
            case 4:
                s.setTexture(this->waterTexture);
                this->waterVector.push_back(s);
                break;
            case 5:
                s.setTexture(this->iceTexture);
                this->iceVector.push_back(s);
                break;
            default:
                break;
            }
        }
    }
}

GameplayScreen::GameplayScreen(std::string pathToLvl)
{
    // Ladowanie fontow i tekstur
    this->initAssets();

    // Inicjalizacja zmiennych
    this->gameState = -1;
    this->gridRows = 8;         // Ilosc rzedow
    this->gridCols = 16;        // Ilosc kolumn
    this->borderThickness = 15; // Grubosc drewnianego ogrodzenia

    // Odczyt poziomu z pliku i zapisanie go do zmiennych
    this->readLvlFromFile(pathToLvl);

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
    this->ball = new Ball(this->whiteBallTexture);

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
    std::cout << "GameplayScreen has been destroyed\n";
}

void GameplayScreen::setTitleText(sf::String newTitle)
{
    this->titleText.setString(newTitle);
}
void GameplayScreen::setStrokesLimitText(sf::String newText)
{
    this->leftStrokesText.setString(newText);
}
void GameplayScreen::readLvlFromFile(std::string pathToFile)
{

    std::fstream odczyt;
    int logicalValue;

    odczyt.open(pathToFile, std::ios::in);
    if (!odczyt.good())
    {
        std::cout << "ERROR::GameplayScreen.cpp: Nie udalo sie odczytac poziomu z pliku" << std::endl;
        exit(0);
    }

    odczyt >> this->currentLvl;
    odczyt >> this->strokesLimit;
    this->leftStrokes = this->strokesLimit;

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
void GameplayScreen::wallsCollision()
{
    sf::FloatRect ballBounds = this->ball->getGlobalBounds(); // Pozycja pilki w AKTUALNIEJ klatce
    sf::FloatRect nextPosBounds = ballBounds;                 // Pozycja pilki w NASTEPNEJ klatce
    nextPosBounds.left += this->ball->getVelocity().x;
    nextPosBounds.top += this->ball->getVelocity().y;

    for (int i = 0; i < this->wallsVector.size(); i++)
    {
        sf::FloatRect wallBounds = wallsVector[i].getGlobalBounds();

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

    for (int i = 0; i < this->sandVector.size(); i++)
    {
        sf::FloatRect sandBounds = sandVector[i].getGlobalBounds();

        // Sprawdzenie czy w nastepnej klatce nastapi kolizja
        if (ballBounds.intersects(sandBounds))
        {
            // Zmniejszenie predkosci pilki
            float k = 0.8;
            this->ball->setVelocityX(this->ball->getVelocity().x * k);
            this->ball->setVelocityY(this->ball->getVelocity().y * k);
        }
    }
}
void GameplayScreen::waterCollision(){
    sf::FloatRect ballBounds = this->ball->getGlobalBounds(); // Pozycja pilki w AKTUALNIEJ klatce

    for (int i = 0; i < this->waterVector.size(); i++)
    {
        sf::FloatRect waterBounds = waterVector[i].getGlobalBounds();
        float k = 0.8;
        float l = 1.15;
        // Sprawdzenie czy w nastepnej klatce nastapi kolizja
        if (ballBounds.intersects(waterBounds))
        {
            // Zmniana predkosci pilki
            float l = 1.0002;
            this->ball->setVelocityY(this->ball->getVelocity().y * (l+0.1));
            //std::cout<<this->ball->getVelocity().y<<"\n";
            if(fabs(this->ball->getVelocity().y)>6){
                this->ball->setVelocityY(this->ball->getVelocity().y /2);
            }
            else if(fabs(this->ball->getVelocity().y)>=4){
                this->ball->setVelocityX(this->ball->getVelocity().x * pow(1.2,2));
            }
            else{
            this->ball->setVelocityX(this->ball->getVelocity().x / l);
            }
            if(fabs(this->ball->getVelocity().x)>=2){
                this->ball->setVelocityX(this->ball->getVelocity().x / 10);
            }
        }
    }
}
void GameplayScreen::iceCollision()
{
    sf::FloatRect ballBounds = this->ball->getGlobalBounds(); // Pozycja pilki w AKTUALNIEJ klatce

    for (int i = 0; i < this->iceVector.size(); i++)
    {
        sf::FloatRect iceBounds = iceVector[i].getGlobalBounds();

        // Sprawdzenie czy w nastepnej klatce nastapi kolizja
        if (ballBounds.intersects(iceBounds))
        {
            // Zmniejszenie predkosci pilki
            float k = 1.125;
            if(sqrt(pow(this->ball->getVelocity().x,2)+pow(this->ball->getVelocity().x,2))<7.5){
            this->ball->setVelocityX(this->ball->getVelocity().x * k);
            this->ball->setVelocityY(this->ball->getVelocity().y * k);
            }
            else{
                this->ball->setVelocityX(this->ball->getVelocity().x /3);
            this->ball->setVelocityY(this->ball->getVelocity().y /3);
            }
        }
    }
}
void GameplayScreen::holeCollision()
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
        }
    }
}

void GameplayScreen::update(sf::WindowBase &window, std::string *lvlsPathArray, int lvlsPathArrayLength, int &currentLvlRef, bool &isMouseBtnPressedRef)
{
    // Kolizja ze scianami
    this->wallsCollision();

    this->ball->update(window, this->leftStrokes, this->gameState, isMouseBtnPressedRef);

    // Zmniejszenie liczby uderzen
    this->setStrokesLimitText(sf::String("Strzaly: " + std::to_string(this->leftStrokes)));

    // Kolizja z piaskiem
    this->sandCollision();

    // Kolizja z wodą
    this->waterCollision();

    // Kolizja z lodem
    this->iceCollision();

    // Kolizja z polem
    this->courseBordersCollision();

    // Kolizja z dolkiem
    this->holeCollision();

    // Poczekanie az pilka sie zatrzyma i sprawdzenie czy przypadkiem juz nie przegralismy
    if (!this->ball->isMoving && this->gameState == -1)
    {
        if (this->leftStrokes <= 0)
        {
            this->gameState = 0;
            this->endGameScreen.setTexture(this->loseBgTexture);
        }
    }

    // Obsluga przyciskow na ekranie konca gry
    if (this->gameState != -1)
    {
        if (this->replayBtn->isClicked(window) && !isMouseBtnPressedRef)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            isMouseBtnPressedRef = true;
            this->gameState = -1;
            this->leftStrokes = this->strokesLimit;
            this->ball->setPositionX(162);
            this->ball->setPositionY(350 + 50);
        }
        else if (this->nextLvlBtn->isClicked(window) && !isMouseBtnPressedRef)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            isMouseBtnPressedRef = true;
            // Sprawdzenie, czy istnieje kolejny lvl
            if ((currentLvlRef < lvlsPathArrayLength))
            {

                currentLvlRef++;
                currentLvl = currentLvlRef;
                this->gameState = -1;

                // Ladowanie od nowa kolejnego poziomu
                // Wczytanie danych z pliku
                this->readLvlFromFile(lvlsPathArray[this->currentLvl - 1]);

                // Aktualizacja tytulu
                this->setTitleText(sf::String("Lvl: " + std::to_string(this->currentLvl)));

                // Liczba uderzen sama sie aktualizuje, wiec nie trzeba tego robic tutaj

                // Zaaktualizowanie wektorow ze spriteami
                this->setUpObstacles();

                // Ustawienie pilki na pozycje startowa
                this->ball->setPositionX(162);
                this->ball->setPositionY(350 + 50);
            }
        }
    }
}

void GameplayScreen::render(sf::RenderTarget &target)
{
    target.draw(this->course);
    target.draw(this->titleText);
    target.draw(this->leftStrokesText);

    // Rysowanie wszystkich spriteow
    for (int i = 0; i < this->grassVector.size(); i++) // Trawa
        target.draw(grassVector[i]);
    for (int i = 0; i < this->wallsVector.size(); i++) // Sciany
        target.draw(wallsVector[i]);
    for (int i = 0; i < this->sandVector.size(); i++) // Piasek
        target.draw(sandVector[i]);
    for (int i = 0; i < this->waterVector.size(); i++) // Woda
        target.draw(waterVector[i]);
    for (int i = 0; i < this->iceVector.size(); i++) // Woda
        target.draw(iceVector[i]);

    target.draw(this->hole); // Dolek

    this->ball->render(target);

    // Ewentualny ekran wygranej / przegranej
    if (gameState != -1)
    {
        target.draw(this->endGameScreen);
        this->replayBtn->render(target);
        this->nextLvlBtn->render(target);
    }
}