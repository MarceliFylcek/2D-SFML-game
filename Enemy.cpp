#include "Enemy.h"
#include <iostream>



Enemy::Enemy(std::string filepath, int health, float x, float y) //Set Texture, set texture position, set texturerectangle, scale, set position
{
    this->health = health;
    skin.loadFromFile(filepath);
    character.setTexture(skin);
    character.setTextureRect(sf::IntRect(0 * 64, 2 * 64, 64, 64));
    character.setScale(1.5, 1.5);
    setPosition(x, y);
    spear = 0;
}
Enemy::Enemy()
{

}



void Enemy::attack(Player* player, Map* map)
{
    sf::Vector2f vector;
    vector.x = 0;
    vector.y = 0;
    if (randomy == 0)
    {
        srand(time(NULL));
        int i = rand();
        int randomy = (i % 10) + 1;
    }
    //Run towards player
    if (position.x - (player->position.x) <= 0 && abs(position.x - player->position.x) < 700 && abs(position.x - player->position.x) > 47) //enemy to the left && distance less than 700 && distance more than 30
    {
        vector.x += defenemyspeed;
    }
    if (position.x - (player->position.x) > 0 && abs(position.x - player->position.x) < 700 && abs(position.x - player->position.x) > 47)  //enemy to right && distance less than 700 && more than 50
    {
        vector.x += -defenemyspeed;
    }
    if (position.y - player->position.y > 0 && abs(position.x - player->position.x) < 500 && abs(position.y - player->position.y) > 10)
    {
        vector.y += -defenemyspeed;
    }
    if (position.y - player->position.y < 0 && abs(position.x - player->position.x) < 500 && abs(position.y - player->position.y) > 10)
    {
        vector.y += defenemyspeed;
    }

    if(!(vector.x == 0 && vector.y == 0))
        map->moveEntity(vector.x, vector.y, this);

    //Animate
    if (abs(position.y - player->position.y) <= 10 && abs(position.x - player->position.x) <= 47)
    {
            if (player->position.x < position.x)
            {
                animate(5);
            }

            if (player->position.x > position.x)
            {
                animate(4);
            }  

        if (delay > 20)
        {
            player->defend(damage);
            delay = 0;
        }
        delay++;

    }
    else
    {
        //Reset animation sequence, move the sprite
        delay = 0;
       
    }
   
       

}

void Enemy::move(float x, float y) //Update position, move sprite, animate sprite, always the last function
{
    position.x += x;
    position.y += y;
  
    if (x > 0)
    {
        animate(0);
    }
    if (x < 0)
    {
        animate(1);
    }
    if (x == 0 && y==0)
    {
        setstate(3);
    }
    if (y < 0 && (x == 0.0f))
    {
        animate(2);
    }
    if (y > 0 && (x == 0.0f))
    {
        animate(3);
    }
     
}
