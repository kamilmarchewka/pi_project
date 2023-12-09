#include "Button.h"

Button::Button(
    sf::Vector2f pos,       // Button position
    sf::Texture &play_btn_t // Texture for btn
)
{
  btn_s.setTexture(play_btn_t);
  btn_s.setOrigin(
      btn_s.getGlobalBounds().width / 2.f,
      btn_s.getGlobalBounds().height / 2.f);
  set_position(pos);
}

void Button::set_position(sf::Vector2f pos)
{
  btn_s.setPosition(pos);
}

bool Button::is_mouse_over(sf::RenderWindow &window)
{
  sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
  sf::FloatRect buttonBounds = btn_s.getGlobalBounds();

  if (buttonBounds.contains((float)(mousePosition.x), (float)(mousePosition.y)))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Button::set_scale(float s)
{
  btn_s.setScale(s, s);
}
void Button::set_rotation(float d)
{
  btn_s.setRotation(d);
}

void Button::set_texture(sf::Texture &t)
{
  btn_s.setTexture(t);
}

void Button::draw_to(sf::RenderWindow &window)
{
  window.draw(btn_s);
}