#include <SFML/Graphics.hpp> // Include SFML graphics library

class Button
{
public:
  // Constructor
  Button(
      sf::Vector2f pos,       // Button position
      sf::Texture &play_btn_t // Texture for btn
  );

  void set_position(sf::Vector2f pos);

  bool is_mouse_over(sf::RenderWindow &window);
  void set_scale(float s);
  void set_rotation(float d);
  void set_texture(sf::Texture &t);

  // Render
  void draw_to(sf::RenderWindow &window);

private:
  sf::Sprite btn_s;
};