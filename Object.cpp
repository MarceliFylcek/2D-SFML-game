#include "Object.h"
#include <iostream>

Object::Object(std::string filepath, int width, int height, float x, float y) //file path, width of a texture, height of a texture, x coordinate on a map, y coorinate
{
	this->filepath = filepath;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	if (!texture.loadFromFile(filepath))
	{
		std::cout << "Couldn't load up a texture for "<< filepath << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	numx = 0; //position of a texture in a texture sheet/ this can be set by changeSheet()
	numy = 0;
}
void Object::display(sf::RenderWindow& window, sf::Vector2f cameraoffset) //draw
{
	sprite.setPosition(x - cameraoffset.x, y);
	window.draw(sprite);
}
void Object::displayAt(sf::RenderWindow& window, sf::Vector2f cameraoffset, float x, float y) //draw at different position
{
	sprite.setPosition(x - cameraoffset.x, y);
	window.draw(sprite);
}
void Object::displayAtSheet(sf::RenderWindow& window, sf::Vector2f cameraoffset, float x, float y, int numx, int numy) //draw at different position, with different texture in the sheet
{
	sprite.setTextureRect(sf::IntRect(numx * width, numy * height, width, height));
	sprite.setPosition(x - cameraoffset.x, y);
	window.draw(sprite);
	sprite.setTextureRect(sf::IntRect(this->numx, this->numy, width, height));
}
void Object::changeSheet(int numx, int numy) //change default texture in the sheet
{
	sprite.setTextureRect(sf::IntRect(numx * width, numy * height, width, height));
	this->numx = numx;
	this->numy = numy;
}
void Object::scale(float x)
{
	sprite.setScale(x, x);
}
Object::Object()
{

}

void Object::displayAtSpecific(sf::RenderWindow& window, sf::Vector2f cameroffset, float x, float y, int sheetx, int sheety, int twidth, int theight) //draw at different position, with different texture and different size
{
	sprite.setTextureRect(sf::IntRect(sheetx, sheety, twidth, theight));
	sprite.setPosition(x - cameroffset.x, y);
	window.draw(sprite);
	sprite.setTextureRect(sf::IntRect(this->numx, this->numy, width, height));
}
