// Standard library includes
#include <iostream>

// SFML includes
#include <SFML/Graphics.hpp>

/**
 * Main entry point of the application
 * Function that runs the entire game loop
 */
int main()
{
  // Create an instance of the SFML RenderWindow type which represents the display
  // and initialise its size and title text
  sf::RenderWindow window(sf::VideoMode(800, 600), "MiniGolf", sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60); // Set limit of 60fps

  // Game loop, runs until the game is over
  // updates the game 60 times per second
  while (window.isOpen())
  {
    // Input
    // Handle player input
    sf::Event event;
    while (window.pollEvent(event))
    {
      // Handle events here
      if (event.type == sf::Event::Closed)
        window.close(); // Close window
    }

    // Update
    // Update the game

    // Draw
    // Draw the scene
    window.clear(sf::Color::Black);

    // Display everything that has been drawn
    window.display();
  }

  // Game has ended
  return 0;
}