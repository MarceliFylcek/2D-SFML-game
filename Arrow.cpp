#include "Arrow.h"
#include <SFML/Graphics.hpp>



void Arrow::setVelocity(float x, float y)
{
    sf::Vector2f vel;
    vel.x = x;
    vel.y = y;
    velocity = vel;
    isactive = 0;
}
void Arrow::move()
{
    sprite.move(velocity);
}