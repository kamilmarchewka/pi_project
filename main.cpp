#include <iostream>

#include <SFML/Graphics.hpp>

#include "Ball.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

int main(){

  // Define window
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MiniGolf");
  window.setFramerateLimit(60); // Set limit to 60 FPS

  sf::Texture main_bg_t; // Texture for main bg
  main_bg_t.loadFromFile("assets/main_bg.png");
  main_bg_t.setSmooth(true); // Smothen edges
  sf::Sprite main_bg_s; // Sprite for main bg
  main_bg_s.setTexture(main_bg_t); // Set spirte texture
  // align to bottom left
  main_bg_s.setPosition(0, WINDOW_HEIGHT - main_bg_t.getSize().y);

  while(window.isOpen()) // Game loop
  {
    sf::Event event; // Define variable which holds events data
    while(window.pollEvent(event)) // Check if there is any event
    { // Check if event is window closed
      if(event.type == sf::Event::Closed) window.close(); // Close window
    }

    window.clear(sf::Color(168,202,89,100)); // Clear window with green
    window.draw(main_bg_s);
    window.display(); // Display window
  }
  
  return 0;
}