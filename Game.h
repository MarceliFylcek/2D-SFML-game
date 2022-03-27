#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "Arrow.h"
#include "Vector4b.h"
#include "Enemy.h"
#include "AnimatedObject.h"
#include "Map.h"
#include "MainWorld.h"

//Contains all the code connected to the game enginne
class Game
{
    public:
        Game(int SCREEN_WIDTH, int SCREEN_HEIGHT, int* selectedcharacter, int*difficulty);
        sf::Text text;
        Player* player = (Player*)malloc(sizeof(Player));
        Map* map1 = (Map*)malloc(sizeof(Map));
        sf::Vector2f cameraoffset;
        Arrow arrow[10];
        void run(sf::RenderWindow& window, int *phase);
        void cameraupdate(sf::Vector2f playerposition);
        sf::Clock clock;
        Enemy enemy[30];
        Object* playermap = (Object*)malloc(sizeof(Object));
        Object* blood = (Object*)malloc(sizeof(Object));
        void playerinput();
        void save();
        void load();
    private:
        struct DamageStats
        {
            sf::Text dm_display;
            int received_damage;
            sf::Clock dmclock;
        };
        DamageStats damagestats[31];
        int numofenemies;
        sf::Font font;
        sf::Font font2;
        sf::Clock attackdelay;
        sf::Text endtext;
        sf::Text endscore[2];
        sf::Text scoretxt[2];
        sf::Text missiongoal;
        int score;
        sf::Texture enemy1txt;
        sf::Texture enemy2txt;
        sf::Texture enemy3txt;
        sf::Texture enemy4txt;
        sf::Texture bloodtext;
        sf::Music music;
        sf::Music bandittheme;
        sf::Music malescream;
        sf::Music map2;
        sf::Music ending;
        int SCREEN_HEIGHT;
        int SCREEN_WIDTH;
        MainWorld mainworld;
        void runmain(sf::RenderWindow& window);
        void runloc(sf::RenderWindow& window);
        void setmap(int num);
        bool slowed_down;
        void gameover(sf::RenderWindow& window);
        void display_damage(sf::RenderWindow& window);
        int currentmap;
        void setup();
        int *tselectedcharacter;
        int* tdifficulty;
        void help(sf::RenderWindow& window);
        bool helpon = 0;
        sf::Clock helpdelay;
        bool gamefinished;
        bool gamerestart;
        void script();
        void arrows_logic();
        int numfarrows;
        Player temp;
        int arrowsused;
        bool shiftpressed;
};