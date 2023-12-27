#include "pch.h"
#include "GameplayScreen.h"

GameplayScreen::GameplayScreen(int lvl)
{
    // Ladowanie fontow
    if (!(this->font.loadFromFile("assets/fonts/Inter-SemiBold.ttf")))
        std::cout << "ERROR::GameplayScreen::FONTS - Inter-SemiBold.ttf";

    // Ladowanie tekstur blokow
    if (!(this->grassDarkTexture.loadFromFile("assets/grass_dark.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - grass_dark.png\n";
    this->grassDarkTexture.setSmooth(true);
    if (!(this->grassLightTexture.loadFromFile("assets/grass_light.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - grass_light.png\n";
    this->grassLightTexture.setSmooth(true);
    if (!(this->rockTexture.loadFromFile("assets/rock.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - rock.png\n";
    this->rockTexture.setSmooth(true);
    // Ladowanie tekstur pilek
    if (!(this->whiteBallTexture.loadFromFile("assets/ball_white.png")))
        std::cout << "ERROR::GameplayScreen::TEXTURES - ball_white.png\n";
    this->whiteBallTexture.setSmooth(true);

    // Inicjalizacja zmiennych
    this->currentLvl = 1;
    this->strokesLimit = 10;
    this->borderThickness = 15; // Grubosc drewnianego ogrodzenia

    // Inicjalizaja pola
    this->course.setFillColor(sf::Color(146, 186, 59, 255)); // Kolor
    this->course.setSize(sf::Vector2f(1000, 500));           // Rozmiar
    this->course.setOrigin(sf::Vector2f(1000 / 2, 500 / 2)); // Origin - srodek pola
    this->course.setPosition(sf::Vector2f(600, 350 + 50));   // Pozycja - srodek ekranu (lekko przesuniete w dol)

    this->course.setOutlineColor(sf::Color(108, 88, 76, 255));
    this->course.setOutlineThickness(this->borderThickness);

    // Inicjalizacja tytulu
    sf::String titleString = "Lvl: " + std::to_string(this->currentLvl);

    this->titleText.setString(titleString);                   // Napis
    this->titleText.setFont(this->font);                      // Czcionka
    this->titleText.setFillColor(sf::Color(30, 48, 80, 255)); // Kolor
    this->titleText.setOrigin(sf::Vector2f(                   // Origin - srodek dolnej krawedzi
        this->titleText.getGlobalBounds().width / 2,
        this->titleText.getGlobalBounds().height + 9));
    this->titleText.setPosition(sf::Vector2f( // Pozycja - nad polem
        1200 / 2,
        this->course.getGlobalBounds().top - 20));

    // Inicjalizacja maks. liczby uderzen
    sf::String maxStrokesString = "Strzaly: " + std::to_string(this->strokesLimit);

    this->strokesLimitText.setString(maxStrokesString);              // Napis
    this->strokesLimitText.setFont(this->font);                      // Czcionka
    this->strokesLimitText.setCharacterSize(20);                     // Rozmiar
    this->strokesLimitText.setFillColor(sf::Color(30, 48, 80, 255)); // Kolor
    this->strokesLimitText.setOrigin(sf::Vector2f(                   // Origin - lewy dol
        this->strokesLimitText.getGlobalBounds().left,
        this->strokesLimitText.getGlobalBounds().height));
    this->strokesLimitText.setPosition(sf::Vector2f( // Pozycja - nad polem z lewej strony
        this->course.getGlobalBounds().left,
        this->course.getGlobalBounds().top - 20));

    // Rysowanie planszy (przeszkod)
    this->initCourseObstackles();

    // Inicjalizacja pilki
    this->ball = new Ball(this->whiteBallTexture);
}
GameplayScreen::~GameplayScreen()
{
    delete this->ball;
    std::cout << "GameplayScreen has been destroyed\n";
}

void GameplayScreen::initCourseObstackles()
{
    this->gridRows = 8;  // Ilosc rzedow
    this->gridCols = 16; // Ilosc kolumn

    // 0 - light grass
    // 1 - dark grass
    // 2 - rock

    // Logiczna reprezentacja pol
    int courseGridMap[8][16] = {{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                                {1, 0, 1, 2, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                                {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1},
                                {1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 2, 0, 1, 0},
                                {0, 1, 0, 1, 0, 1, 0, 2, 0, 1, 0, 1, 2, 1, 0, 1},
                                {1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0},
                                {0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 0, 1, 2, 1, 0, 1},
                                {1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 2, 0, 1, 0}};

    // Tworzenie dynamicznej tablicy spriteow
    for (int i = 0; i < this->gridRows; i++)
    {
        for (int j = 0; j < this->gridCols; j++)
        {
            sf::Sprite s;

            switch (courseGridMap[i][j])
            {
            case 0:
                s.setTexture(this->grassLightTexture);
                break;

            case 1:
                s.setTexture(this->grassDarkTexture);
                break;

            case 2:
                s.setTexture(this->rockTexture);
                break;

            default:
                break;
            }

            s.setPosition(sf::Vector2f(
                this->course.getGlobalBounds().left + this->borderThickness + (j * 62.5),
                this->course.getGlobalBounds().top + this->borderThickness + (i * 62.5)));

            courseGrid[i][j] = s;
        }
    }
}

void GameplayScreen::update(sf::WindowBase &window)
{
    // TODO: To sie musi brac z jednego miejsca
    int courseGridMap[8][16] = {{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                                {1, 0, 1, 2, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                                {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1},
                                {1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 2, 0, 1, 0},
                                {0, 1, 0, 1, 0, 1, 0, 2, 0, 1, 0, 1, 2, 1, 0, 1},
                                {1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0},
                                {0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 0, 1, 2, 1, 0, 1},
                                {1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 2, 0, 1, 0}};

    this->ball->update(window);

    // Sprawdzenie kolizji
    float courseWidth = this->course.getGlobalBounds().width - this->borderThickness * 2;
    float courseHeight = this->course.getGlobalBounds().height - this->borderThickness * 2;
    float courseL = this->course.getGlobalBounds().left + this->borderThickness;
    float courseR = courseL + courseWidth;
    float courseT = this->course.getGlobalBounds().top + this->borderThickness;
    float courseB = courseT + courseHeight;

    float ballRadius = this->ball->getGlobalBounds().width / 2;
    float ballL = this->ball->getGlobalBounds().left;
    float ballR = ballL + ballRadius * 2;
    float ballT = this->ball->getGlobalBounds().top;
    float ballB = ballT + ballRadius * 2;
    // Z plansza
    if (ballL <= courseL)
    {
        this->ball->setPosition(sf::Vector2f(
            courseL + ballRadius,
            ballT + ballRadius));
        this->ball->setVelocity(sf::Vector2f(
            this->ball->getVelocity().x * -1,
            this->ball->getVelocity().y));
    }
    else if (ballR >= courseR)
    {
        this->ball->setPosition(sf::Vector2f(
            courseR - ballRadius,
            ballT + ballRadius));
        this->ball->setVelocity(sf::Vector2f(
            this->ball->getVelocity().x * -1,
            this->ball->getVelocity().y));
    }

    if (ballT <= courseT)
    {
        this->ball->setPosition(sf::Vector2f(
            ballL + ballRadius,
            courseT + ballRadius));
        this->ball->setVelocity(sf::Vector2f(
            this->ball->getVelocity().x,
            this->ball->getVelocity().y * -1));
    }
    else if (ballB >= courseB)
    {
        this->ball->setPosition(sf::Vector2f(
            ballL + ballRadius,
            courseB - ballRadius));
        this->ball->setVelocity(sf::Vector2f(
            this->ball->getVelocity().x,
            this->ball->getVelocity().y * -1));
    }

    // Ze spriteami
    // TODO odbijanie se od rogow
    for (int i = 0; i < this->gridRows; i++)
    {
        for (int j = 0; j < this->gridCols; j++)
        {
            // Z kamieniami (odbijanie sie)
            if (courseGridMap[i][j] == 2) // Sprawdzenie czy to jest kamien
            {
                sf::FloatRect ballBounds = this->ball->getGlobalBounds();
                sf::FloatRect rockBounds = this->courseGrid[i][j].getGlobalBounds();
            }
        }
    }
}
void GameplayScreen::render(sf::RenderTarget &target)
{
    target.draw(this->course);
    target.draw(this->titleText);
    target.draw(this->strokesLimitText);

    // Draw course with obstacles
    for (int i = 0; i < this->gridRows; i++)
        for (int j = 0; j < this->gridCols; j++)
            target.draw(this->courseGrid[i][j]);

    this->ball->render(target);
}