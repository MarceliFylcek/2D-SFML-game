#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Vector4b.h"
#include <iostream>
#include <time.h>

Player::Player(int selectedcharacter, int health, float x, float y) //Set texture, health, position
    {
        this->health = health;
        if (!skin.loadFromFile("images/maincharacter.png"))
            std::cout << "Couldn't load maincharacter1" << std::endl;
        if (!skin2.loadFromFile("images/maincharacter2.png"))
            std::cout << "Couldn't load maincharacter2" << std::endl;
        if (!skin3.loadFromFile("images/maincharacter3.png"))
            std::cout << "Couldn't load maincharacter3" << std::endl;
 
        switch (selectedcharacter)
        {
        case 0:
            character.setTexture(skin);
            break;
        case 1:
            character.setTexture(skin2);
            break;
        case 2:
            character.setTexture(skin3);
            break;

        }
        
        character.setTextureRect(sf::IntRect(0 * 64, 2 * 64, 64, 64));
        character.setScale(1.5, 1.5);
        setPosition(x,y);
        armor = 20;
        damage = 60;
        spear = 0;
        defspeed = 3.75; //3
        defspeedv = 3.125; //2.5
        received_damage = -1;
    }
Player::Player()
    {
        health = 100;
        std::cout << "Created" << std::endl;
    }
void Player::setHealth(unsigned int health)
    {
        this->health = health;
        if (health > 0)
            this->isdead = 0;
    }
void Player::setPosition(float x, float y)
    {
        position.x = x;
        position.y = y;
        character.setPosition(sf::Vector2f(x-45, y-30));
    }

void Player::move(float x, float y) //Set position, animate, move the sprite, always the last function
    {
        position.x += x;
        position.y += y;
        
        //camera mechanics
        if (position.x < SCREEN_WIDTH / 2)
        {
            character.move(sf::Vector2f(x, y));
        }

        if (position.x > SCREEN_WIDTH / 2 && position.x < 127 * 50 - SCREEN_WIDTH / 2)
        {
            character.move(sf::Vector2f(0, y));
        }
        if (position.x > 127 * 50 - SCREEN_WIDTH / 2)
        {
            character.move(sf::Vector2f(x, y));
        }
        
    }

void Player::addVelocity(float x, float y)
{
    velocity.x += x;
    velocity.y += y;
    
}
void Player::setVelocityX(float x)
{
    velocity.x = x;
}
void Player::setVelocityY(float y)
{
    velocity.y = y;
}
float Player::getVelocityX()
{
    return velocity.x;
}
float Player::getVelocityY()
{
    return velocity.y;
}
unsigned int Player::getHealth()
{
    return health;
}

void Player::defend(int damage)
{
    srand(time(NULL));
    int i = rand() % armor + 1;
    received_damage = damage - i;
    if (received_damage < 0)
    {
        received_damage = 0;
    }
    health -= received_damage;
    if (health < 1)
    {
        health = 0;
        isdead = 1;
    }     
    std::cout << "dm: " << received_damage << std::endl;
    std::cout << "health: " << health << std::endl;
}
void Player::fight()
{
   
}

void Player::animate(int animation)
{
    if (animation != 8)
    {
        texture_state_die = 0;
    }
    if (clock1.getElapsedTime().asMilliseconds()>150 && animation < 4) //200
    {
        switch (animation)
        {
        case 0: //walk right
            if (currentanimation != 0)
            {
                texture_state_r = 0;
            }
            texture_state_r++;
            if (texture_state_r == 9)
                texture_state_r = 1;
            character.setTextureRect(sf::IntRect((texture_state_r) * 64, 11 * 64, 64, 64));
            currentanimation = 0;
            break;
        case 1: //walk left
            if (currentanimation != 1)
            {
                texture_state_l = 0;
            }
            texture_state_l++;
            if (texture_state_l == 9)
                texture_state_l = 1;
            character.setTextureRect(sf::IntRect((texture_state_l) * 64, 9 * 64, 64, 64));
            currentanimation = 1;
            break;
        case 2: //walk up
            if (currentanimation != 2)
            {
                texture_state_f = 0;
            }
            texture_state_f++;
            if (texture_state_f == 9)
                texture_state_f = 1;
            character.setTextureRect(sf::IntRect((texture_state_f) * 64, 8 * 64, 64, 64));
            currentanimation = 2;
            break;
        case 3: //walk down
            if (currentanimation != 3)
            {
                texture_state_b = 0;
            }
            texture_state_b++;
            if (texture_state_b == 9)
                texture_state_b = 1;
            character.setTextureRect(sf::IntRect((texture_state_b) * 64, 10 * 64, 64, 64));
            currentanimation = 3;
            break;
        }

        clock1.restart();   
    }

    if (clock1.getElapsedTime().asMilliseconds() > 75 && animation > 3) //fighting animations, every 100ms
    {
        switch (animation)
        {
        case 4: //fight right
            if (currentanimation != 4)
            {
                texture_state_fight_r = 0;
            }
            if (texture_state_fight_r == 6)
                texture_state_fight_r = 0;
            if(spear == 0)
                character.setTextureRect(sf::IntRect((texture_state_fight_r) * 64, 15 * 64, 64, 64));
            else
                character.setTextureRect(sf::IntRect((texture_state_fight_r) * 64, 7 * 64, 64, 64));
            texture_state_fight_r++;
            currentanimation = 4;
            break;
        case 5: //fight left
            if (currentanimation != 5)
            {
                texture_state_fight_l = 0;
            }
            if (texture_state_fight_l == 6)
                texture_state_fight_l = 0;
            if(spear == 0)
                character.setTextureRect(sf::IntRect((texture_state_fight_l) * 64, 13 * 64, 64, 64));
            else
                character.setTextureRect(sf::IntRect((texture_state_fight_l) * 64, 5 * 64, 64, 64));
            texture_state_fight_l++;
            currentanimation = 5;
            break;
        case 6: //fight up
            if (currentanimation != 6)
            {
                texture_state_fight_f = 0;
            }
            if (texture_state_fight_f == 6)
                texture_state_fight_f = 0;
            if (spear == 0)
                character.setTextureRect(sf::IntRect((texture_state_fight_f) * 64, 12 * 64, 64, 64));
            else
                character.setTextureRect(sf::IntRect((texture_state_fight_f) * 64, 4 * 64, 64, 64));
            texture_state_fight_f++;
            currentanimation = 6;
            break;
        case 7: //fight down
            if (currentanimation != 7)
            {
                texture_state_fight_b = 0;
            }
            if (texture_state_fight_b == 6)
                texture_state_fight_b = 0;
            if (spear == 0)
                character.setTextureRect(sf::IntRect((texture_state_fight_b) * 64, 14 * 64, 64, 64));
            else
                character.setTextureRect(sf::IntRect((texture_state_fight_b) * 64, 6 * 64, 64, 64));
            texture_state_fight_b++;
            currentanimation = 7;
            break;
        case 8: //die
            character.setTextureRect(sf::IntRect((texture_state_die) * 64, 20 * 64, 64, 64));
            if (texture_state_die != 5)
            {
                texture_state_die++;
            }
            
            currentanimation = 7;
            break;

        }
        clock1.restart();
    }
}

void Player::setstate(int texture)
{
    switch (texture)
    {
    case 0:
        character.setTextureRect(sf::IntRect(0 * 64, 11 * 64, 64, 64)); //look right
        break;
    case 1:
        character.setTextureRect(sf::IntRect(0 * 64, 9 * 64, 64, 64)); //look left
        break;
    case 2:
        character.setTextureRect(sf::IntRect(0 * 64, 8 * 64, 64, 64)); //look up
        break;
    case 3:
        character.setTextureRect(sf::IntRect(0 * 64, 10 * 64, 64, 64)); //look down
        break;
    case 4:
        character.setTextureRect(sf::IntRect(0 * 64, 10 * 64, 64, 64)); //shield up (not available)
        break;
    case 5: //bow right
        character.setTextureRect(sf::IntRect(6 * 64, 19 * 64, 64, 64));
        break;
    case 6: //bow left
        character.setTextureRect(sf::IntRect(6 * 64, 17 * 64, 64, 64));
        break;
    case 7: //bow up
        character.setTextureRect(sf::IntRect(6 * 64, 16 * 64, 64, 64));
        break;
    case 8: //bow down
        character.setTextureRect(sf::IntRect(6 * 64, 18 * 64, 64, 64));
        break;
    }
}

void Player::setTexture(int selectedcharacter)
{
    switch (selectedcharacter)
    {
    case 0:
        break;
    case 1:
        skin = skin2;
        break;
    case 2:
        skin = skin3;
        break;
    default:
        std::cout << "error" << std::endl;
    }
}

int Player::getfightstate(fightstate j)
{
    switch(j)
    {
    case right:
        return texture_state_fight_r;
        break;
    case left:
        return texture_state_fight_l;
        break;
    case up:
        return texture_state_fight_f;
        break;
    case down:
        return texture_state_fight_b;
        break;
    }
}
