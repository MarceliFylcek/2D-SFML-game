#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <time.h>
#include <stdlib.h> 


class Enemy : public Player
{
public:
	Enemy(std::string filepath, int health, float x, float y);
	Enemy();
	void attack(Player* player, Map* map);
	void move(float x, float y) override;
private:
	int delay = 0;
	float defenemyspeed = 2.5; //2
	int randomy = 0;
};

