#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp> // Include SFML graphics library

#include "Button.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

enum GameState
{
  HOME,
  PLAYING,
};

int main()
{
  int GAME_STATE = HOME;
  int SOUND_ON = 1;

  // Load Fonts
  sf::Font font, font_bold;
  font.loadFromFile("assets/Comic_Sans_MS.ttf");
  font_bold.loadFromFile("assets/Comic_Sans_MS_Bold.ttf");

  // Load Textures
  // Main background
  sf::Texture main_bg_t;
  main_bg_t.loadFromFile("assets/main_bg.png");
  main_bg_t.setSmooth(true);
  // Play btn
  sf::Texture play_btn_t;
  play_btn_t.loadFromFile("assets/play_btn.png");
  play_btn_t.setSmooth(true);
  // Music and sound icon
  sf::Texture sound_on_icon_t, sound_off_icon_t;
  sound_on_icon_t.loadFromFile("assets/sound_on_icon.png");
  sound_off_icon_t.loadFromFile("assets/sound_off_icon.png");
  sound_on_icon_t.setSmooth(true);
  sound_off_icon_t.setSmooth(true);
  // Settings icon
  sf::Texture settings_icon_t;
  settings_icon_t.loadFromFile("assets/settings_icon.png");
  settings_icon_t.setSmooth(true);
  // Exit icon
  sf::Texture exit_icon_t;
  exit_icon_t.loadFromFile("assets/exit_icon.png");
  exit_icon_t.setSmooth(true);

  // Define window
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MiniGolf");
  window.setFramerateLimit(60); // Set limit to 60 FPS

  // Main background
  sf::Sprite main_bg_s;            // Sprite for main bg
  main_bg_s.setTexture(main_bg_t); // Set spirte texture
  main_bg_s.setPosition(0, WINDOW_HEIGHT - main_bg_t.getSize().y);

  // Play btn
  Button play_btn(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), play_btn_t);

  // Settings icon
  Button settings_btn(sf::Vector2f(WINDOW_WIDTH - 30, 30), settings_icon_t);
  // Music and sound icon
  Button sound_btn(
      sf::Vector2f(WINDOW_WIDTH - 80, 30),
      SOUND_ON ? sound_on_icon_t : sound_off_icon_t);
  // Exit icon
  Button exit_btn(sf::Vector2f(WINDOW_WIDTH - 30, WINDOW_HEIGHT - 30), exit_icon_t);

  while (window.isOpen()) // Game loop
  {
    sf::Event event; // Define variable which holds events data

    // Event loop
    while (window.pollEvent(event)) // Check if there is any event
    {
      switch (event.type)
      {
      case sf::Event::Closed: // If event is window closed
        window.close();       // Close window
        break;
      case sf::Event::MouseMoved:

        play_btn.is_mouse_over(window) ? play_btn.set_scale(1.05f) : play_btn.set_scale(1.f);

        sound_btn.is_mouse_over(window) ? sound_btn.set_rotation(10.f) : sound_btn.set_rotation(0.f);
        settings_btn.is_mouse_over(window) ? settings_btn.set_rotation(10.f) : settings_btn.set_rotation(0.f);

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
    switch (GAME_STATE)
    {
    case HOME:
      window.clear(sf::Color(168, 202, 89, 100)); // Clear window with green
      window.draw(main_bg_s);
      play_btn.draw_to(window);
      sound_btn.draw_to(window);
      settings_btn.draw_to(window);

      window.display(); // Display window
      break;
    case PLAYING:
      window.clear(sf::Color(168, 202, 89, 100)); // Clear window with green

      exit_btn.draw_to(window);
      window.display(); // Display window
      break;
    default:
      break;
    }
  }

  return 0;
}