// Standard library includes
#include <iostream>

// SFML includes
#include <SFML/Graphics.hpp>

// Game includes
#include "Game.h"

// Consts
float W_WIDTH = 1200;
float W_HEIGHT = 700;

/**
 * Main entry point of the application
 * Function that runs the entire game loop
 */
int main()
{
  // Create an instance of the Game class
  Game game;
  // Game loop, runs until the game is over
  // updates the game 60 times per second
  while (game.isRunning())
  {
    // Update
    // All the logic of the game is updated here
    game.update();

    // Draw and display the game
    game.render();
  }

  // Game has ended
  return 0;
}