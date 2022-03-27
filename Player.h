#pragma once
#include <SFML/Graphics.hpp>
#include "Vector4b.h"
class Player
{
public:
    Player(int selectedcharcter, int health, float x, float y);
    Player();
    void setHealth(unsigned int health);
    unsigned int getHealth();
    void setPosition(float x, float y);
    virtual void move(float x, float y);
    void addVelocity(float x, float y);
    void setVelocityX(float x);
    void setVelocityY(float y);
    void setTexture(int selectedcharacter);
    float getVelocityX();
    float getVelocityY();
    void defend(int damage);
    void fight();
    sf::Texture skin;
    sf::Texture skin2;
    sf::Texture skin3;
    sf::Sprite character;
    sf::Vector2f position;
    int armor;
    int damage;
    int received_damage;
    void animate(int animation); //walk right(0), walk left(1), walk up(2), walk down(3), fight right(4), fight left(5), fight up (6), fight down(7) ,die(8)
    int currentanimation;
    void setstate(int texture); //look right(0), left(1), up(2), down(3), shield right(4), left(5), up(6), down(7), dead(8);
    bool isdead = 0;
    bool spear;
    float defspeed;
    float defspeedv; //vertical
    enum fightstate
    {
        right, left, up, down
    };
    int getfightstate(fightstate j);
    
protected:
    int cycles = 10;
    int currentcycle = 0;
    int fight_cycles = 6;
    int fight_currentcycle = 0;
    int texture_state_l = 0;
    int texture_state_r = 0;
    int texture_state_f = 0;
    int texture_state_b = 0;
    int texture_state_fight_l = 0;
    int texture_state_fight_r = 0;
    int texture_state_fight_f = 0;
    int texture_state_fight_b = 0;
    int texture_state_die = 0;
    int health = 100;
private:
    sf::Vector2f velocity;
    int SCREEN_HEIGHT = 900;
    int SCREEN_WIDTH = 1600;
    sf::Clock clock1;
};
