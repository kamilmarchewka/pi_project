#include <SFML/Graphics.hpp>

class Board
{
public:
  Board(sf::Vector2f pos, sf::Texture &grass_t);
  void draw_to(sf::RenderWindow &window);

private:
  sf::Sprite grass_s;
};