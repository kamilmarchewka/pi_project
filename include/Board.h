#include <SFML/Graphics.hpp>

class Board
{
public:
  Board(sf::Vector2f pos, sf::Texture &grass_t);
  void draw_to(sf::RenderWindow &window);

  sf::Vector2f get_size()
  {
    return sf::Vector2f(
        grass_s.getTexture()->getSize().x,
        grass_s.getTexture()->getSize().y);
  }

private:
  sf::Sprite grass_s;
};