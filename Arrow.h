#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
//create arrow class
class Arrow
{
public:
    void setVelocity(float x, float y);
    void move();
    sf::Sprite sprite;
    sf::Texture arrowtxt;
    bool isactive;
    bool isvisible;
    bool direction; //0 - left, //1 - right, //2 - up //3 - down
    void attack(Enemy& enemy);
private:
    sf::Vector2f velocity;

};