#pragma once
#include<SFML/Graphics.hpp>

class MainWorld
{
public:
	MainWorld();
	void set();
	void display(sf::RenderWindow& window);
	void zoom();
	void unzoom();
	void setCamPos(float x, float y);
private:

	sf::Sprite map;
	sf::Sprite background;
	sf::Texture maptxt;
	sf::Texture backgroundtxt;
	sf::View view;
};

