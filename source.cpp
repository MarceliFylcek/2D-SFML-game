#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <iostream>
#include "Vector4b.h"
#include "Player.h"
#include "Menu.h"
#include "Game.h"

int main()
{
    //Set the parameters of the window and the framerate
    unsigned int SCREEN_WIDTH = 1600;
    unsigned int SCREEN_HEIGHT = 900;
    char WINDOW_TITLE[] = "The Game";

    //Create the clock used for input
    sf::Clock clock;

    //Create a window and set a framerate
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE);
    window.setFramerateLimit(60);
    /*window.setVerticalSyncEnabled(1);*/

    //Create menu object
    Menu menu(SCREEN_WIDTH, SCREEN_HEIGHT);

    //Phase of the program (menu, start of the game, pause, creating a character)
    int phase = 0; 

    //Index of a character selected in the menu
    int selectedcharacter = 0;

    //Difficulty level set in the menu
    int difficulty = 0;

    //phase
    //0 - starting menu
    //1 - start the game
    //2 - pause
    //3 - countinue the game
    //4 - quit the program
    //5 - character creation menu
    //6 - save to a file
    //7 - load from a file
    //8 - game has been finished

    //Create game object
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT, &selectedcharacter, &difficulty);

    while (phase != 4)
    {
        //Runs the main loop in game class 
        if (phase == 0 || phase == 2) //starting menu || paused game
            menu.run(&phase, &selectedcharacter, &difficulty, window, &clock);


        //Runs the main loop in menu class 
        if (phase == 1 || phase == 3) //new game || unpaused game
            game.run(window, &phase);

        if (phase == 6) //saving
        {
            std::cout << "saving" << std::endl;
            game.save();
            //draw something to the screen
            phase = 2;
        }

        if (phase == 7) //loading
        {
            game.load();
            phase = 3; //countinue game
        }

        if (phase == 8)
        {
            phase = 0;
        }


    }
       
        
     


    return 0;

}