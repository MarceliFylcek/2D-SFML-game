#pragma once
#include <SFML/Graphics.hpp>

class Object
{
public:
	Object(std::string filepath, int width, int height, float x, float y);
	Object();
	void display(sf::RenderWindow& window, sf::Vector2f cameraoffset);
	void displayAt(sf::RenderWindow& window, sf::Vector2f cameraoffset, float x, float y);
	void displayAtSheet(sf::RenderWindow& window, sf::Vector2f cameraoffset, float x, float y, int numx, int numy);
	void displayAtSpecific(sf::RenderWindow& window, sf::Vector2f cameroffset, float x, float y, int sheetx, int sheety, int width, int height); //specific size of a texture
	virtual void changeSheet(int numx, int numy);
	void scale(float x);
	sf::Sprite sprite;
protected:
	std::string filepath;
	int width;
	int height;
	float x;
	float y;
	int numx;
	int numy;
	sf::Texture texture;
};

