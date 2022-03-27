#include "AnimatedObject.h"

void AnimatedObject::animate()
{
	if (clock1.getElapsedTime().asMilliseconds() > 200)
	{

		sprite.setTextureRect(sf::IntRect(width * currenttxt, height * numy, width, height));

		currenttxt++;
		if (currenttxt == numoftxt)
			currenttxt = numx;

		clock1.restart();
	}
}
AnimatedObject::AnimatedObject(std::string texturefilepath, int width, int height, int num, float x, float y)
{
	texture.loadFromFile(texturefilepath);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	this->width = width;
	this->height = height;
	this->numoftxt = num;
	currenttxt = 0;
	sprite.setPosition(x, y);
	this->x = x;
	this->y = y;
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	numx = 0;
	numy = 0;
}
AnimatedObject::AnimatedObject()
{

}
void AnimatedObject::changeSheet(int numx, int numy)
{
	this->numx = numx;
	this->numy = numy;
	sprite.setTextureRect(sf::IntRect(width * currenttxt, height * numy, width, height));

}