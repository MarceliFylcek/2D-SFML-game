#include "Menu.h"
#include <iostream>

Menu::Menu(float SCREEN_WIDTH, float SCREEN_HEIGHT)
{
        selected = 0;
        if (!font.loadFromFile("fonts/Piazzolla-VariableFont_opsz,wght.ttf"))
        {
            return;
        }

        background_menu_txt.loadFromFile("images/backgroundmenu.jpg");
        background.setTexture(background_menu_txt);

        menu[0].setFont(font);
        menu[0].setFillColor(sf::Color::White);
        menu[0].setString("Nowa gra");
        menu[0].setPosition(sf::Vector2f(SCREEN_WIDTH / 6, 0.85 * SCREEN_HEIGHT));
        menu[1].setFont(font);
        menu[1].setFillColor(sf::Color::White);
        menu[1].setString("Wczytaj gre");
        menu[1].setPosition(sf::Vector2f(SCREEN_WIDTH / 2.2, 0.85 * SCREEN_HEIGHT));
        menu[2].setFont(font);
        menu[2].setFillColor(sf::Color::White);
        menu[2].setString("Wyjdz");
        menu[2].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.75, 0.85 * SCREEN_HEIGHT));

        pause[0].setFont(font);
        pause[0].setFillColor(sf::Color::White);
        pause[0].setString("Kontynuuj");
        pause[0].setPosition(sf::Vector2f(SCREEN_WIDTH / 6, 0.85 * SCREEN_HEIGHT));
        pause[1].setFont(font);
        pause[1].setFillColor(sf::Color::White);
        pause[1].setString("Zapisz gre");
        pause[1].setPosition(sf::Vector2f(SCREEN_WIDTH / 2.15, 0.85 * SCREEN_HEIGHT));
        pause[2].setFont(font);
        pause[2].setFillColor(sf::Color::White);
        pause[2].setString("Wyjdz");
        pause[2].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.75, 0.85 * SCREEN_HEIGHT));

        ins[0].setFont(font);
        ins[0].setFillColor(sf::Color::White);
        ins[0].setString("PROJEKT - INFORMATYKA II");
        ins[0].setPosition(sf::Vector2f(0, 0));
        ins[1].setFont(font);
        ins[1].setFillColor(sf::Color::White);
        ins[1].setString("Marceli Fylcek");
        ins[1].setPosition(sf::Vector2f(0, SCREEN_HEIGHT / 13));
        ins[2].setFont(font);
        ins[2].setFillColor(sf::Color::White);
        ins[2].setString("EiA PG 2020");
        ins[2].setPosition(sf::Vector2f(0, 2 * SCREEN_HEIGHT / 13));

        difficultytext[0].setFont(font);
        difficultytext[0].setFillColor(sf::Color::White);
        difficultytext[0].setString("Poziom latwy");
        difficultytext[0].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.39, 0.1 * SCREEN_HEIGHT));
        difficultytext[0].setCharacterSize(50);
        difficultytext[1].setFont(font);
        difficultytext[1].setFillColor(sf::Color::White);
        difficultytext[1].setString("Poziom sredni");
        difficultytext[1].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.39, 0.1 * SCREEN_HEIGHT));
        difficultytext[1].setCharacterSize(50);
        difficultytext[2].setFont(font);
        difficultytext[2].setFillColor(sf::Color::White);
        difficultytext[2].setString("Poziom trudny");
        difficultytext[2].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.39, 0.1 * SCREEN_HEIGHT));
        difficultytext[2].setCharacterSize(50);

        stats[3].setFont(font);
        stats[3].setFillColor(sf::Color::White);
        stats[3].setString("Liczba strzal - 3");
        stats[3].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.41, 0.55 * SCREEN_HEIGHT));
        stats[2].setFont(font);
        stats[2].setFillColor(sf::Color::White);
        stats[2].setString("Szybkosc - 8");
        stats[2].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.41, 0.25 * SCREEN_HEIGHT));
        stats[1].setFont(font);                            
        stats[1].setFillColor(sf::Color::White);           
        stats[1].setString("Pancerz - 12");
        stats[1].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.41, 0.35 * SCREEN_HEIGHT));
        stats[0].setFont(font);                           
        stats[0].setFillColor(sf::Color::White);          
        stats[0].setString("Obrazenia - 10");
        stats[0].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.41, 0.45 * SCREEN_HEIGHT));
           

        setuptext[1].setFont(font);
        setuptext[1].setFillColor(sf::Color::White);
        setuptext[1].setString("Zmien trudnosc");
        setuptext[1].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.31, 0.8 * SCREEN_HEIGHT));
        setuptext[1].setCharacterSize(40);
        setuptext[2].setFont(font);
        setuptext[2].setFillColor(sf::Color::White);
        setuptext[2].setString("Rozpocznij");
        setuptext[2].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.55, 0.8 * SCREEN_HEIGHT));
        setuptext[2].setCharacterSize(40);
        setuptext[0].setFont(font);
        setuptext[0].setFillColor(sf::Color::White);
        setuptext[0].setString("Zmien postac");
        setuptext[0].setPosition(sf::Vector2f(SCREEN_WIDTH * 0.09, 0.8 * SCREEN_HEIGHT));
        setuptext[0].setCharacterSize(40);

        character = new AnimatedObject("images/maincharacter.png", 64, 64, 9, 100, 0);
        character->changeSheet(1, 10);
        character->scale(9);

        setupbackgroundtxt.loadFromFile("images/paperbackground.png");
        setupbackground.setTexture(setupbackgroundtxt);
        setupbackground.setPosition(0, -80);

        difficultytext[3] = difficultytext[0];



}
void Menu::draw(sf::RenderWindow& window) //draw starting menu
{
    window.clear();
    window.draw(background);
    for (int i = 0; i < 3; i++)
    {
    window.draw(ins[i]);
    window.draw(menu[i]);
    }
    window.draw(menu[selected]);
    window.draw(menu[selected]);
    
    window.display();
}
void Menu::drawpause(sf::RenderWindow& window) //draw pause menu
{
    window.clear();
    window.draw(background);
    for (int i = 0; i < 3; i++)
    {
        window.draw(ins[i]);
        window.draw(pause[i]);
    }
    window.draw(pause[selected]);
    window.draw(pause[selected]);

    window.display();
}
void Menu::drawsetup(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);
    window.draw(setupbackground);
    for  (int i = 0; i < 3; i++)
    {
        window.draw(setuptext[i]);
    }
    window.draw(setuptext[selected]);
    window.draw(setuptext[selected]);

    window.draw(stats[0]);
    window.draw(stats[1]);
    window.draw(stats[2]);
    window.draw(stats[3]);

    window.draw(difficultytext[3]);
    character->animate();
    character->display(window, sf::Vector2f(0, 0));
    window.display();

}
void Menu::run(int* phase, int* selectedcharacter, int* difficulty, sf::RenderWindow& window, sf::Clock* clock) 
{
    sf::Clock delay;
    while (window.isOpen() && (*phase == 0 || *phase == 2 || *phase == 5))
    {
        if (clock->getElapsedTime().asMilliseconds() > 20)
        {
            //Event handling
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    *phase = 4;
                    break;
                }

            }
            if (sf::Keyboard::isKeyPressed && window.hasFocus())
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && delay.getElapsedTime().asMilliseconds() > 200)
                {
                    if (selected > 0)
                    {
                        selected--;
                    }
                    delay.restart();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && delay.getElapsedTime().asMilliseconds() > 200)
                {
                    if (selected < options - 1)
                    {
                        selected++;
                    }
                    delay.restart();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && delay.getElapsedTime().asMilliseconds() > 200)
                {
                    switch (selected)
                    {
                    case 0:
                        if (*phase == 0) //starting menu
                        {
                            (*phase) = 5;  //character creation
                            selected = 0;
                        } 
                        else if (*phase == 2) // pause menu
                        {
                            *phase = 3;  //return to the game
                            selected = 0;
                        }
                        else if (*phase == 5) //character creation
                        {
                            //change character
                            if (*selectedcharacter == 0)
                            {
                                (*selectedcharacter)++;
                                delete character;
                                character = new AnimatedObject("images/maincharacter2.png", 64, 64, 9, 100, 0);
                                character->changeSheet(1, 10);
                                character->scale(9);
                                character->animate();
                                stats[0].setString("Obrazenia - 9");
                                stats[1].setString("Pancerz - 10");
                                stats[2].setString("Szybkosc - 10");
                                stats[3].setString("Liczba strzal - 5");
                            }
                            else if (*selectedcharacter == 1)
                            {
                                (*selectedcharacter)++;
                                delete character;
                                character = new AnimatedObject("images/maincharacter3.png", 64, 64, 9, 100, 0);
                                character->changeSheet(1, 10);
                                character->scale(9);
                                stats[0].setString("Obrazenia - 15");
                                stats[1].setString("Pancerz - 20");
                                stats[2].setString("Szybkosc - 6");
                                stats[3].setString("Liczba strzal - 2");
                            }
                            else if (*selectedcharacter == 2)
                            {
                                *selectedcharacter = 0;
                                delete character;
                                character = new AnimatedObject("images/maincharacter.png", 64, 64, 9, 100, 0);
                                character->changeSheet(1, 10);
                                character->scale(9);
                                stats[0].setString("Obrazenia - 10");
                                stats[1].setString("Pancerz - 12");
                                stats[2].setString("Szybkosc - 8");
                                stats[3].setString("Liczba strzal - 3");
                            }

                        }
                        clock->restart(); // same clock used for game class
                        break;
                        case 1: //save/load/change difficulty
                            if (*phase == 5)
                            {
                                if ((*difficulty) < 2)
                                    (*difficulty)++;
                                else
                                    (*difficulty) = 0;
                                difficultytext[3] = difficultytext[*difficulty];
                            }
           
                            if (*phase == 0) //starting menu
                            {
                                *phase = 7; //load a game
                            }
                            if (*phase == 2) //pause menu - save a game
                            {
                                std::cout << "here" << std::endl;
;                                *phase = 6; //save a game
                            }
                            break;


                        case 2: 
                            if (*phase == 0 || *phase == 2) //close
                            {
                                window.close();
                                *phase = 4;
                            }
                            if (*phase == 5)
                            {
                                *phase = 1;
                                selected = 0;
                            }
                            break;
                    }
                    delay.restart();
                }
            }
                switch (*phase)
                {
                case 0:                                                                //phase 0 - starting menu
                    draw(window);                                                      //phase 1 - game
                    break;                                                             //phase 2 - pause
                case 2:                                                                //phase 3 - return to game
                    drawpause(window);                                                 //phase 4 - quit
                    break;                                                             //phase 5 - character creation(after phase 0, before phase 1)
                case 5:                                                                
                    drawsetup(window);
                    break;

                  
                }                                                                      

            


            clock->restart();
        }
      
        
        
       
    }
   
}
