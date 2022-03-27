#include "MainWorld.h"


MainWorld::MainWorld()
{
	maptxt.loadFromFile("images/map.png");
	map.setTexture(maptxt);
	backgroundtxt.loadFromFile("images/backgroundm.jpg");
	background.setTexture(backgroundtxt);
	background.scale(1.5, 1.5);
	view.setSize(1600, 900);
}
void MainWorld::set()
{
	maptxt.loadFromFile("images/map.png");
	map.setTexture(maptxt);
	backgroundtxt.loadFromFile("images/paper.jpg");
	background.setTexture(backgroundtxt);
	background.scale(5, 5);
	background.setPosition(5500, -1000);
	background.rotate(90);
	view.setSize(1600, 900);
}
void MainWorld::display(sf::RenderWindow &window)
{
	window.clear();
	window.setView(view);
	window.draw(background);
	window.draw(map);
}
void MainWorld::zoom()
{
	view.zoom(0.99);
}
void MainWorld::unzoom()
{
	view.zoom(1.01);
}
void MainWorld::setCamPos(float x, float y)
{
	view.setCenter(x, y);
}

