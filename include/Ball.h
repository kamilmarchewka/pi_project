#include <SFML/Graphics.hpp>

class Ball {
private:
  float x; // Position in X axis
  float y; // Position in Y axis
  float size; // Size of ball
  float xVelocity; // Velocity in X axis
  float yVelocity; // Velocity in Y axis

public:
  Ball(float x, float y, float size); // Constructor
  // Getters
  float getX();
  float getY();
  // Setters
};

Ball::Ball(float x, float y, float size){
  this->x = x;
  this->y = y;
  this->size = size;
  this->xVelocity = 0;
  this->yVelocity = 0;
}
float Ball::getX(){ return this->x; }
float Ball::getY(){ return this->y; }