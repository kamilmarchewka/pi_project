#include "pch.h"

#include "Game.h"

int main()
{
  // Stworzenie obiektu Game
  Game game;

  // Game loop
  while (game.getWindow().isOpen()) // Sprawdzenie czy okno jest otwarte
  {
    // Aktualizacja
    game.update();
    // Renderowanie
    game.render();
  }

  // Koniec gry
  return 0;
}