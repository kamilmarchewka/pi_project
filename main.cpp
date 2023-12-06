#include <iostream>

#include <SFML/Graphics.hpp>

#include "Ball.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

using namespace sf;

int main(){
  // Ball pilka_golfowa(10, 10, 20); // Create ball object
  // std::cout << "Polozenie pilki: " << pilka_golfowa.getX() << ", " << pilka_golfowa.getY() << std::endl; // Print ball position
  
  RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MiniGolf"); // Define window
  window.setFramerateLimit(60); // Set limit to 60 FPS

  RectangleShape rect; // Define rectangle
  Vector2f position(10,10);
  Vector2f size(100, 100);
  rect.setSize(size); // Set size of rectangle
  rect.setPosition(position); // Set position of rectangle

  int xVelocity = 5;
  int yVelocity = 15;

  Texture texture;
  texture.loadFromFile("assets/main_bg.png");
  Sprite sprite;
  sprite.setTexture(texture);

  while(window.isOpen()) // Game loop
  {
    Event event; // Define variable which holds events data
    while(window.pollEvent(event)) // Check if there is any event
    { // Check if event is window closed
      if(event.type == Event::Closed) window.close(); // Close window
    }

    position.x += xVelocity;
    position.y += yVelocity;
    rect.setPosition(position);

    // Detect collision in X axis with window borders
    if(
      position.x <=0 || // Left border
      position.x + size.x >= WINDOW_WIDTH // Right border
    ){
      xVelocity *= -1;
    }
    // Detect collision in Y axis with window borders
    if(
      position.y <= 0 || // Top border
      position.y + size.y >= WINDOW_HEIGHT // Bottom border
    ){
      yVelocity *= -1;
    }

    window.clear(Color::Black); // Clear window with black color
    window.draw(sprite);
    window.draw(rect); // Draw rectangle
    window.display(); // Display window
  }
  
  return 0;
}