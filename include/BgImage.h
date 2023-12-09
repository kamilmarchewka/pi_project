#include <SFML/Graphics.hpp>

class BgImage
{
public:
  BgImage(sf::Texture &texture, sf::Vector2f pos)
  {
    sprite.setTexture(texture);
    sprite.setPosition(pos);
  }

  sf::Vector2f get_size()
  {
    return sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
  }

  void draw_to(sf::RenderWindow &window)
  {
    window.draw(sprite);
  }

private:
  sf::Sprite sprite;
};