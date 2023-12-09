#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp> // Include SFML graphics library

#include "BgImage.h"
#include "Button.h"
#include "Board.h"
#include "Ball.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

enum GameState
{
  HOME,
  PLAYING,
};

// Game settings
bool SOUND_ON;
int GAME_STATE;

// Fonts
sf::Font font, font_bold;

// Textures
sf::Texture
    main_bg_t,
    play_btn_t,
    sound_on_icon_t,
    sound_off_icon_t,
    settings_icon_t,
    exit_icon_t,
    grass_t,
    wall_t;

// Functions
void game_init()
{
  // Load fonts
  font.loadFromFile("assets/Comic_Sans_MS.ttf");
  font_bold.loadFromFile("assets/Comic_Sans_MS_Bold.ttf");

  // Load Textures
  // Main background
  main_bg_t.loadFromFile("assets/main_bg.png");
  main_bg_t.setSmooth(true);
  // Play btn
  play_btn_t.loadFromFile("assets/play_btn.png");
  play_btn_t.setSmooth(true);
  // Music and sound icon
  sound_on_icon_t.loadFromFile("assets/sound_on_icon.png");
  sound_off_icon_t.loadFromFile("assets/sound_off_icon.png");
  sound_on_icon_t.setSmooth(true);
  sound_off_icon_t.setSmooth(true);
  // Settings icon
  settings_icon_t.loadFromFile("assets/settings_icon.png");
  settings_icon_t.setSmooth(true);
  // Exit icon
  exit_icon_t.loadFromFile("assets/exit_icon.png");
  exit_icon_t.setSmooth(true);
  // Grass texture
  grass_t.loadFromFile("assets/grass.png");
  grass_t.setSmooth(true);
  // Wall
  wall_t.loadFromFile("assets/wall.png");
  wall_t.setSmooth(true);

  // Other settings
  SOUND_ON = true;
  GAME_STATE = PLAYING;
}

int main()
{
  // Game init
  // Loading fonts, textures, and default game settings
  game_init();

  // Define window
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MiniGolf");
  window.setFramerateLimit(60); // Set limit to 60 FPS

  // Main background
  BgImage home_bg(
      main_bg_t,
      sf::Vector2f(0, WINDOW_HEIGHT - main_bg_t.getSize().y));

  // Play btn
  Button play_btn(
      sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
      play_btn_t);

  // Settings icon
  Button settings_btn(
      sf::Vector2f(WINDOW_WIDTH - 30, 30),
      settings_icon_t);

  // Music and sound icon
  Button sound_btn(
      sf::Vector2f(WINDOW_WIDTH - 80, 30),
      SOUND_ON ? sound_on_icon_t : sound_off_icon_t);

  // Exit icon
  Button exit_btn(
      sf::Vector2f(WINDOW_WIDTH - 30, WINDOW_HEIGHT - 30),
      exit_icon_t);

  // Game board
  Board board(
      sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
      grass_t);

  // Wall
  sf::Sprite wall_s;
  wall_s.setTexture(wall_t);
  wall_s.setOrigin(wall_t.getSize().x / 2, wall_t.getSize().y / 2);
  wall_s.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

  // Ball
  Ball ball;

  while (window.isOpen()) // Game loop
  {
    sf::Event event;                // Define variable which holds events data
    while (window.pollEvent(event)) // Check if there is any event
    {
      switch (event.type)
      {
      case sf::Event::Closed: // If event is window closed
        window.close();       // Close window
        break;
      case sf::Event::MouseMoved:

        play_btn.is_mouse_over(window) ? play_btn.set_scale(1.05f) : play_btn.set_scale(1.f);
        if (GAME_STATE == HOME)
        {
          sound_btn.is_mouse_over(window) ? sound_btn.set_rotation(10.f) : sound_btn.set_rotation(0.f);
          settings_btn.is_mouse_over(window) ? settings_btn.set_rotation(10.f) : settings_btn.set_rotation(0.f);
        }

        break;
      case sf::Event::MouseButtonPressed:
        if (sound_btn.is_mouse_over(window))
        {
          SOUND_ON = !SOUND_ON;
          sound_btn.set_texture(SOUND_ON ? sound_on_icon_t : sound_off_icon_t);
        }
        if (play_btn.is_mouse_over(window))
        {
          std::cout << "Play button pressed" << std::endl;
          GAME_STATE = PLAYING;
        }

        if (exit_btn.is_mouse_over(window))
        {
          std::cout << "Exit button pressed" << std::endl;
          GAME_STATE = HOME;
        }

        break;
      default:
        break;
      }
    }

    // Render
    window.clear(sf::Color(168, 202, 89, 100)); // Clear window with green
    if (GAME_STATE == HOME)
    {
      home_bg.draw_to(window);
      play_btn.draw_to(window);
      sound_btn.draw_to(window);
      settings_btn.draw_to(window);
    }

    if (GAME_STATE == PLAYING)
    {
      //--------------------------------------------------
      // For testing
      ball.set_position(
          sf::Vector2f(
              ball.get_position().x + ball.get_velocity().x,
              // ball.get_position().y + ball.get_velocity().y),
              ball.get_position().y));

      // Check collision with board
      if (ball.get_position().x + ball.get_radius() > WINDOW_WIDTH / 2 + board.get_size().x / 2 || ball.get_position().x - ball.get_radius() < WINDOW_WIDTH / 2 - board.get_size().x / 2)
      {
        ball.set_velocity(sf::Vector2f(-ball.get_velocity().x, ball.get_velocity().y));
      }
      // check y collision
      if (ball.get_position().y + ball.get_radius() > WINDOW_HEIGHT / 2 + board.get_size().y / 2 || ball.get_position().y - ball.get_radius() < WINDOW_HEIGHT / 2 - board.get_size().y / 2)
      {
        ball.set_velocity(sf::Vector2f(ball.get_velocity().x, -ball.get_velocity().y));
      }

      if (ball.is_colliding_with(wall_s))
      {
        ball.set_velocity(sf::Vector2f(-ball.get_velocity().x, ball.get_velocity().y));
      }
      //--------------------------------------------------

      board.draw_to(window);
      window.draw(wall_s);
      ball.draw_to(window);

      exit_btn.draw_to(window);
    }

    window.display(); // Display window
  }
  return 0;
}