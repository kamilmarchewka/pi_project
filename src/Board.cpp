#include <SFML/Graphics.hpp> // Include SFML graphics
#include "Board.h"

Board::Board(sf::Vector2f pos, sf::Texture &grass_t)
{
  // Set sprites
  grass_s.setTexture(grass_t);
  grass_s.setOrigin(grass_t.getSize().x / 2, grass_t.getSize().y / 2);
  grass_s.setPosition(pos);
}

void Board::draw_to(sf::RenderWindow &window)
{
  window.draw(grass_s);
}