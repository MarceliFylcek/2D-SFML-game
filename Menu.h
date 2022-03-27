#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedObject.h"
class Menu {
private:
    sf::Font font;
    sf::Text menu[3];
    sf::Text pause[3];
    sf::Text ins[3];
    sf::Text setuptext[3];
    sf::Text difficultytext[4];
    sf::Text stats[4];
    int selectedItem = 0;
    sf::Sprite background;
    sf::Sprite setupbackground;
    sf::Texture background_menu_txt;
    sf::Texture setupbackgroundtxt;
    int selected;
    int options = 3;
    void drawsetup(sf::RenderWindow& window);
    AnimatedObject* character;
    int diff;
public:
    Menu(float SCREEN_WIDTH, float SCREEN_HEIGHT);
    void draw(sf::RenderWindow& window);
    void drawpause(sf::RenderWindow& window);
    void input(int* phase, sf::RenderWindow& window, sf::Clock* clock);
    void run(int* phase, int* selectedcharacter, int* difficulty, sf::RenderWindow& window, sf::Clock* clock);
};
