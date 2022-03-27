#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class AnimatedObject : public Object
{
public:
	AnimatedObject(std::string texturefilepath, int width, int height, int num, float x, float y);
	AnimatedObject();
	void animate();
	void changeSheet(int numx, int numy);
private:
	int currenttxt;
	int numoftxt;
	sf::Clock clock1;
};

