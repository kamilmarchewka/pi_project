#include <SFML/Graphics.hpp> // Include SFML graphics library

class Ball
{
public:
  Ball()
  {
    ball.setRadius(10);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setPosition(200, 250);
    velocity.x = 4;
    velocity.y = 4;
  }

  void set_position(sf::Vector2f pos)
  {
    ball.setPosition(pos);
  }

  sf::Vector2f get_position()
  {
    return ball.getPosition();
  }
  sf::Vector2f get_velocity()
  {
    return velocity;
  }
  void set_velocity(sf::Vector2f vel)
  {
    velocity = vel;
  }
  float get_radius()
  {
    return ball.getRadius();
  }
  bool is_colliding_with(sf::Sprite &sprite)
  {
    return ball.getGlobalBounds().intersects(sprite.getGlobalBounds());
  }

  void draw_to(sf::RenderWindow &window)
  {
    window.draw(ball);
  }

private:
  sf::CircleShape ball;
  sf::Vector2f velocity;
};