#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "AnimatedObject.h"
#include "Object.h"


//Contains code connected to the game enginne
Game::Game(int SCREEN_WIDTH, int SCREEN_HEIGHT, int* selectedcharacter, int* difficulty)
{
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;

    //Version inscription
    try
    {
        if (!font.loadFromFile("fonts/Piazzolla-VariableFont_opsz,wght.ttf"))
            throw "Couldn't load the font";
    }
    catch (const char* exp)
    {
        std::wcout << "Error: " << exp << std::endl;
    }
    try
    {
        if (!font2.loadFromFile("fonts/PirataOne-Regular.ttf"))
            throw "Couldn't load the font2";
    }
    catch (const char* exp)
    {
        std::wcout << "Error: " << exp << std::endl;
    }
    text.setString("Version 7.2");
    text.setFont(font);
    text.setCharacterSize(SCREEN_HEIGHT / 40);
    text.setPosition(0, 29 * SCREEN_HEIGHT / 30);
    endtext.setString("Koniec gry");
    endtext.setFont(font2);
    endtext.setCharacterSize(SCREEN_HEIGHT / 8);
    endtext.setPosition(SCREEN_WIDTH / 2.85, SCREEN_HEIGHT / 3.3);
    endscore[0].setString("Twoj wynik:");
    endscore[0].setFont(font2);
    endscore[0].setCharacterSize(SCREEN_HEIGHT / 9);
    endscore[0].setPosition(SCREEN_WIDTH / 3.7, SCREEN_HEIGHT / 2);
    endscore[1].setFont(font);
    endscore[1].setCharacterSize(SCREEN_HEIGHT / 9);
    endscore[1].setPosition(SCREEN_WIDTH / 1.65, SCREEN_HEIGHT / 2);

    missiongoal.setFont(font2);
    missiongoal.setCharacterSize(SCREEN_HEIGHT / 45);
    missiongoal.setPosition(50, 150);

    score = 0;

    scoretxt[0].setString("Punkty: ");
    scoretxt[0].setFont(font2);
    scoretxt[0].setCharacterSize(SCREEN_HEIGHT / 29);
    scoretxt[0].setPosition(1325, SCREEN_HEIGHT/21);

    scoretxt[1].setString("0");
    scoretxt[1].setFont(font);
    scoretxt[1].setCharacterSize(SCREEN_HEIGHT / 20);
    scoretxt[1].setPosition(1450, SCREEN_HEIGHT / 30);



    //Music
    try
    {
        if (!music.openFromFile("sounds/theme1.ogg"))
            throw "Couldn't load the music file";
        if (!bandittheme.openFromFile("sounds/Bandit-Fight.ogg"))
            throw "Couldn't load the music file";
        if (!map2.openFromFile("sounds/Let_s-Kill-Some-Crows.ogg"))
            throw "Couldn't load the music file";
        if (ending.openFromFile("sounds/endsong.ogg"))
            throw "Couldn't load the music file";
    }
    catch (const char* exp)
    {
        std::wcout << "Error: " << exp << std::endl;
    }
    music.play();

    //sounds
    malescream.openFromFile("sounds/malescream.ogg");


    
    
    /*playermap = new Object("images/head.png", 24, 24, 200, 200);*/

    //Arrow
    for (size_t i = 0; i < 10; i++)
    {
        arrow[i].arrowtxt.loadFromFile("images/arrow.png");
        arrow[i].sprite.setTexture(arrow[i].arrowtxt);
        arrow[i].sprite.scale(2, 2);
    }
    


    //Enemy
    enemy1txt.loadFromFile("images/enemy1.png");
    enemy2txt.loadFromFile("images/enemy2.png");
    enemy3txt.loadFromFile("images/enemy3.png");
    enemy4txt.loadFromFile("images/enemy4.png");


    for (int i = 0; i < 30; i++)
    {
        enemy[i].setPosition(0, 0);
        enemy[i].setHealth(100);
        enemy[i].character.setScale(1.5, 1.5);
        if (i % 3 == 0)
            enemy[i].character.setTexture(enemy1txt);
        else if (i % 3 == 1)
            enemy[i].character.setTexture(enemy2txt);
        else
            enemy[i].character.setTexture(enemy4txt);
        enemy[i].character.setTextureRect(sf::IntRect(0 * 64, 2 * 64, 64, 64));
    }
   
    //Camera
    cameraoffset.x = 0;
    map1 = new Map(1, 1600, 900);
    /*mainworld.set();*/

    //main player damage display
    damagestats[30].dm_display.setFont(font2);
    damagestats[30].dm_display.setCharacterSize(SCREEN_HEIGHT / 35);
    damagestats[30].dm_display.Bold;
    damagestats[30].dm_display.setOutlineColor(sf::Color::Black);
    damagestats[30].dm_display.setFillColor(sf::Color(112, 19, 19));

    //enemy damage display
    for (size_t i = 0; i < 30; i++)
    {
        damagestats[i].dm_display.setFont(font2);
        damagestats[i].dm_display.setCharacterSize(SCREEN_HEIGHT / 35);
        damagestats[i].dm_display.Bold;
        damagestats[i].dm_display.setOutlineColor(sf::Color::Black);
        damagestats[i].dm_display.setFillColor(sf::Color::White);
        enemy[i].received_damage = -1; // -1 flag for displaying damage, values bigger than -1 will get displayed including 0 damage
    }
   
    tselectedcharacter = selectedcharacter; //save to local variables
    tdifficulty = difficulty;

    gamefinished = 0;
    gamerestart = 0;
    player = new Player(0, 100, 200, 750);
    arrowsused = 0;
}

void Game::run(sf::RenderWindow& window, int *phase)
{

    if (*phase != 3) //set chosen character and difficulty if new game
    {
        setup();
        setmap(1);
    }


    //Main loop of the game
    while (window.isOpen() && window.hasFocus() && (*phase == 1 || *phase == 3))
    {
        //Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                *phase = 4; //Close the program
                break;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            *phase = 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && helpdelay.getElapsedTime().asMilliseconds() > 200)
        {
            if (helpon == 0)
            {
                helpon = 1;
                helpdelay.restart();
            }
            else if (helpon == 1 && helpdelay.getElapsedTime().asMilliseconds() > 200)
            {
                helpon = 0;
                helpdelay.restart();
            }
            
            
        }
        if (helpon == 1)
            help(window);
        else
            runloc(window);

        if (gamerestart == 1)
        {
            *phase = 8;
            player->isdead = 0;
            gamefinished = 0;
            gamerestart = 0;
            delete player;
            player = new Player(0, 100, 200, 750);
            bandittheme.stop();
            map2.stop();
            ending.stop();
            music.play();
            score = 0;
        }
            
        
    } 

    if (!window.hasFocus() && window.isOpen()) //Pause menu if window is not closed
    {
        *phase = 2;
    }
    
}

void Game::setmap(int num)
{
    for (size_t i = 0; i < numfarrows; i++) //default arrow settings and position
    {
        arrow[i].sprite.setPosition(50 + 70 * (numfarrows - 1 - i) , 80); //first arrow goes far to the right as it will be the first one to be used
        arrow[i].isvisible = 1;
        arrow[i].isactive = 0;
    }
    arrowsused = 0;
    switch (num)
    {
    case 0: //Doesn't exist
        std::cout << "Map not available" << std::endl;
        break;
    case 1: //las
        map1->setmap(1);
        player->setPosition(200, 750);
        numofenemies = 9;
        enemy[0].setPosition(1000, 700);
        enemy[1].setPosition(56 * 50, 640);
        enemy[2].setPosition(57 * 50, 680);
        enemy[3].setPosition(77 * 50, 500);
        enemy[4].setPosition(88 * 50, 650);
        enemy[5].setPosition(89 * 50, 600);
        enemy[6].setPosition(90 * 50, 650);
        enemy[7].setPosition(111 * 50, 700);
        enemy[8].setPosition(112 * 50, 720);

        for (int i = 0; i < 9; i++)
        {
            enemy[i].setHealth(100);
            enemy[i].isdead = 0;
            enemy[i].armor = 10;
            enemy[i].damage = 60;
            enemy[i].spear = 1;
            enemy[i].setstate(3);
            switch (*tdifficulty)
            {
            case 0 :
                enemy[i].armor = 10;
                enemy[i].damage = 40;
                break;
            case 1:
                enemy[i].armor = 20;
                enemy[i].damage = 50;
                break;
            case 2:
                enemy[i].armor = 30;
                enemy[i].damage = 60;
                break;
            }
        }
        currentmap = 1;

        break;
    case 2:
        map1->setmap(2);
        player->setPosition(100, 450);
        numofenemies = 15;
        for (size_t i = 0; i < numofenemies; i++)
        {
            enemy[i].setHealth(100);
            enemy[i].setstate(2);
            enemy[i].spear = 1;
            enemy[i].isdead = 0;
            enemy[i].armor = 15;
            enemy[i].damage = 60;
            switch (*tdifficulty)
            {
            case 0:
                enemy[i].armor = 15;
                enemy[i].damage = 50;
                break;
            case 1:
                enemy[i].armor = 25;
                enemy[i].damage = 60;
                break;
            case 2:
                enemy[i].armor = 35;
                enemy[i].damage = 70;
                break;
            }
            if (i == 5)
            {
                enemy[i].armor = 50;
                enemy[i].spear = 0;
                enemy[i].character.setTexture(enemy3txt);
            }
        }
        enemy[0].setPosition(31 * 50, 17 * 50);
        enemy[1].setPosition(31 * 50, 14 * 50);
        enemy[2].setPosition(32 * 50, 10 * 50);
        enemy[3].setPosition(42 * 50, 12 * 50);
        enemy[4].setPosition(52 * 50, 11 * 50);
        enemy[5].setPosition(53 * 50, 9 * 50);
        enemy[6].setPosition(56 * 50, 10 * 50);
        enemy[7].setPosition(63 * 50, 9 * 50);
        enemy[8].setPosition(64 * 50, 12 * 50);
        enemy[9].setPosition(70 * 50, 10 * 50);
        enemy[10].setPosition(71 * 50, 6 * 50);
        enemy[11].setPosition(82 * 50, 5 * 50);
        enemy[12].setPosition(83 * 50, 7 * 50);
        enemy[13].setPosition(110 * 50, 9 * 50);
        enemy[14].setPosition(109 * 50, 14 * 50);
       
        currentmap = 2;
        break;
    case 3:
        map1->setmap(3);
        player->setPosition(100, 100);
        currentmap = 3;
        break;
    case 4:
        break;
    }
}

void Game::setup()
{
    std::cout << "selectedcharacter: " << *tselectedcharacter << std::endl;
    std::cout << "difficulty: " << *tdifficulty << std::endl;
    switch (*tselectedcharacter)
    {
    case 0:
        numfarrows = 3; //max amount of arrows is 10
        break;
    case 1:
        numfarrows = 5;
        player->setTexture(1);
        player->spear = 1;
        player->defspeed *= 1.2;
        player->defspeedv *= 1.2;
        player->damage *= 0.9;
        player->armor *= 0.8;
        break;
    case 2:
        numfarrows = 2;
        player->setTexture(2);
        player->defspeed *= 0.8;
        player->defspeedv *= 0.8;
        player->armor *= 2;
        player->damage *= 1.5;
        break;
    default:
        std::cout << "Error" << std::endl;
    }
}

void Game::runloc(sf::RenderWindow& window) //runs selected map
{


    if (clock.getElapsedTime().asMilliseconds() > 20) //50 times per second
    {
        script();
        //DRAW
        window.clear();
        //health
        sf::RectangleShape health(sf::Vector2f(player->getHealth() * 2, SCREEN_HEIGHT / 36)); //Sets health
        health.setFillColor(sf::Color(145, 0, 10));
        health.setPosition((SCREEN_WIDTH / 30), SCREEN_HEIGHT / 20);
        //map
        map1->draw(window, cameraoffset); //Draws selected map



        //enemy

        for (int i = 0; i < numofenemies; i++)  //draw dead enemies first
        {
            if (enemy[i].isdead == 1)
            {
                enemy[i].character.setPosition(enemy[i].position.x - cameraoffset.x - 45, enemy[i].position.y - 30);
                window.draw(enemy[i].character);

            }
        }

        //arrows
        arrows_logic();

        for (size_t i = 0; i < numfarrows; i++) //drawing arrows
        {
            if(arrow[i].isvisible == 1)
                window.draw(arrow[i].sprite);
        }

        window.draw(player->character); //draw player

        for (int i = 0; i < numofenemies; i++)  //draw alive enemies on top
        {
            if (enemy[i].isdead == 0)
            {
                enemy[i].character.setPosition(enemy[i].position.x - cameraoffset.x - 45, enemy[i].position.y - 30);
                window.draw(enemy[i].character);
            }
        }

        cameraupdate(player->position); //Calculate camera offset

        window.draw(health);
        window.draw(text);

        for (size_t i = 0; i < numofenemies; i++)
        {
            if (enemy[i].received_damage != -1)
            {
                score += enemy[i].received_damage;
            }
        }
        scoretxt[1].setString(std::to_string(score));
        window.draw(scoretxt[0]);
        window.draw(scoretxt[1]);
        window.draw(missiongoal);


        if (player->isdead || gamefinished == 1)
        {
            endscore[1].setString(std::to_string(score));
            window.draw(endtext);
            window.draw(endscore[0]);
            window.draw(endscore[1]);
        }
        

        display_damage(window);
        window.display();


        //Enemy AI
        for (int i = 0; i < numofenemies; i++)
        {
            if (enemy[i].getHealth() > 0)
            {
                if (player->isdead != 1)
                     enemy[i].attack(player, map1);
            }
            else
            {
                enemy[i].animate(8);
            }

        }



        ////Handle input
        if (!player->isdead)
        {
            playerinput();
        }
        else
        {
            gameover(window);
        }




        clock.restart();
    }


}

void Game::script() //performs actions specific to a map
{
    switch (currentmap)
    {
    case 1:
        missiongoal.setString("Ostrzez wioske przed\natakiem bandytow");
        if (music.getStatus() == 2)
        {
            music.stop();
        }
        if (bandittheme.getStatus() != 2)
        {
            bandittheme.play();
        }

        if (player->position.x > 126 * 50)
        {
            setmap(2);
        }
        break;
    case 2:
        missiongoal.setString("Ratuj swoja rodzine");
        if (bandittheme.getStatus() == 2)
        {
            bandittheme.stop();
        }
        if (music.getStatus() == 2)
        {
            music.stop();
        }
        if (map2.getStatus() != 2 && player->position.x < 123*50)
        {
            map2.play();
        }
        if (player->position.x > 120 * 50)
        {
            if (map2.getStatus() == 2)
            {
                map2.stop();
            }
            if (ending.getStatus() != 2)
            {
                ending.play();
            }
            gamefinished = 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                gamerestart = 1;
        }
        break;
    case 3:
        break;
    }
}

void Game::playerinput() //handles control of a character
{
    bool ismoving = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (shiftpressed == 1)
        {
             shiftpressed = 0;
             arrow[arrowsused].isactive = 1;
             arrowsused++;
        }
        //attack
        slowed_down = 1;
        if (player->currentanimation == 0 || player->currentanimation == 4) //fight right
        {
            player->animate(4);
        }
        if (player->currentanimation == 1 || player->currentanimation == 5) //fight left
        {
            player->animate(5);
        }
        if (player->currentanimation == 2 || player->currentanimation == 6) //fight up
        {
            player->animate(6);
        }
        if (player->currentanimation == 3 || player->currentanimation == 7) //fight down
        {
            player->animate(7);
        }
        for (int i = 0; i < numofenemies; i++)
        {
            if (enemy[i].isdead == 0)
            {
                if (player->currentanimation == 4 && player->getfightstate(Player::right) == 5 && attackdelay.getElapsedTime().asMilliseconds() > 150) //right
                {
                    if ((enemy[i].position.x >= player->position.x) && (enemy[i].position.x - player->position.x < 75) && abs(player->position.y - enemy[i].position.y) < 50)
                    {
                        enemy[i].defend(player->damage);
                        std::cout << "HIT right" << std::endl;
                        malescream.play();
                        attackdelay.restart();
                    }
                }
                else if (player->currentanimation == 5 && player->getfightstate(Player::left) == 5 && attackdelay.getElapsedTime().asMilliseconds() > 150) //left
                {
                    if ((enemy[i].position.x <= player->position.x) && (player->position.x - enemy[i].position.x < 75) && abs(player->position.y - enemy[i].position.y) < 50)
                    {
                        enemy[i].defend(player->damage);
                        std::cout << "HIT left" << std::endl;
                        attackdelay.restart();
                    }
                }
                else if (player->currentanimation == 6 && player->getfightstate(Player::up) == 5 && attackdelay.getElapsedTime().asMilliseconds() > 150) //up
                {
                    if ((enemy[i].position.y <= player->position.y) && (player->position.y - enemy[i].position.y < 75) && abs(player->position.x - enemy[i].position.x) < 50)
                    {
                        enemy[i].defend(player->damage);
                        std::cout << "HIT up" << std::endl;
                        attackdelay.restart();
                    }
                }
                else if (player->currentanimation == 7 && player->getfightstate(Player::down) == 5 && attackdelay.getElapsedTime().asMilliseconds() > 150) //down
                {
                    if ((enemy[i].position.y >= player->position.y) && (enemy[i].position.y - player->position.y < 75) && abs(player->position.x - enemy[i].position.x) < 50)
                    {
                        enemy[i].defend(player->damage);
                        std::cout << "HIT down" << std::endl;
                        attackdelay.restart();
                    }
                }
            }
        }

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && arrowsused < numfarrows)
    {
        shiftpressed = 1;
  
        slowed_down = 1;
        if (player->currentanimation == 4 || player->currentanimation == 0) //right bow
        {
            player->setstate(5);
            arrow[arrowsused].setVelocity(30, 0);
            arrow[arrowsused].sprite.setPosition(player->position.x - cameraoffset.x, player->position.y - 12);
            arrow[arrowsused].sprite.setRotation(0);
            arrow[arrowsused].direction = 0;
        }
        else if (player->currentanimation == 5 || player->currentanimation == 1) //left bow
        {
            player->setstate(6);
            arrow[arrowsused].setVelocity(-30, 0);
            arrow[arrowsused].sprite.setPosition(player->position.x - cameraoffset.x + 10, player->position.y + 46);
            arrow[arrowsused].sprite.setRotation(180);
            arrow[arrowsused].direction = 1;
        }
        else if (player->currentanimation == 6 || player->currentanimation == 2) //up bow
        {
            player->setstate(7);
            arrow[arrowsused].setVelocity(0, -30);
            arrow[arrowsused].sprite.setPosition(player->position.x - cameraoffset.x - 25, player->position.y + 60);
            arrow[arrowsused].sprite.setRotation(-90);
            arrow[arrowsused].direction = 2;
        }
        else if (player->currentanimation == 7 || player->currentanimation == 3) //down bow
        {
            player->setstate(8);
            arrow[arrowsused].setVelocity(0, 30);
            arrow[arrowsused].sprite.setPosition(player->position.x - cameraoffset.x + 25, player->position.y - 10);
            arrow[arrowsused].sprite.setRotation(+90);
            arrow[arrowsused].direction = 3;
        }
    }
    else
    {
        slowed_down = 0; //no fighting or holding an arrow
        if (shiftpressed == 1)
        {
            shiftpressed = 0;
            arrow[arrowsused].isactive = 1;
            arrowsused++;
        }
       
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        //go left
        if (slowed_down == 0)
        {
            map1->moveEntity(-player->defspeed, 0, player);
            player->animate(1);
        }
        if (slowed_down == 1)
        {
            map1->moveEntity(-player->defspeed / 4, 0, player);
        }
        ismoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (slowed_down == 0)
        {
            map1->moveEntity(player->defspeed, 0, player);
            player->animate(0);
        }
        if (slowed_down == 1)
        {
            map1->moveEntity(player->defspeed / 4, 0, player);
        }
        ismoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        //goup
        if (slowed_down == 0)
        {
            map1->moveEntity(0, -player->defspeedv, player);
            player->animate(2);
        }
        if (slowed_down == 1)
        {
            map1->moveEntity(0, -player->defspeedv / 4, player);
        }
        ismoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        //go down
        if (slowed_down == 0)
        {
            map1->moveEntity(0, player->defspeedv, player);
            player->animate(3);
        }
        if (slowed_down == 1)
        {
            map1->moveEntity(0, player->defspeedv / 4, player);
        }
        ismoving = true;
    }
    if (slowed_down == 0 && ismoving == false)
    {
        if (player->currentanimation == 0 || player->currentanimation == 4)
        {
            player->setstate(0);
        }
        else if (player->currentanimation == 1 || player->currentanimation == 5)
        {
            player->setstate(1);
        }
        else if (player->currentanimation == 2 || player->currentanimation == 6)
        {
            player->setstate(2);
        }
        else if (player->currentanimation == 3 || player->currentanimation == 6)
        {
            player->setstate(3);
        }
    }

}

void Game::display_damage(sf::RenderWindow& window) //displays damage above characters' heads
{

    if (player->isdead != 1)
    {
        if (player->received_damage != -1) //new damage
        {
            damagestats[30].dmclock.restart();                                    //restart clock
            damagestats[30].received_damage = player->received_damage;            //save damage to display it
            player->received_damage = -1;                             //set -1 flag, it remains as -1 until new damage gets assigned and then the clock will get restarted
        }

        if (damagestats[30].dmclock.getElapsedTime().asMilliseconds() < 1500)     //display new damage for 1.5s
        {
            damagestats[30].dm_display.setString(std::to_string(damagestats[30].received_damage));
            damagestats[30].dm_display.setPosition(player->position.x - 7 - cameraoffset.x, player->position.y - 40);
            window.draw(damagestats[30].dm_display);
        }
    }


    for (int i = 0; i < numofenemies; i++)
    {
        if (enemy[i].received_damage != -1)
        {
            damagestats[i].dmclock.restart();
            damagestats[i].received_damage = enemy[i].received_damage;
            enemy[i].received_damage = -1;
        }

        if (damagestats[i].dmclock.getElapsedTime().asMilliseconds() < 1500)
        {
            damagestats[i].dm_display.setString(std::to_string(damagestats[i].received_damage));
            damagestats[i].dm_display.setPosition(enemy[i].position.x - 6 - cameraoffset.x, enemy[i].position.y - 40);
            window.draw(damagestats[i].dm_display);
        }
    }

}

void Game::help(sf::RenderWindow& window) //F1 help menu
{
    window.clear(sf::Color::Black);
    Object helpmenu("images/help.png", 1600, 1000, 15, -45);
    Object wsad("images/wsad.png", 1040, 685, 545, 120);
    Object spacebar("images/spacebar.png", 1323, 506, 540, 280);
    Object shift("images/shift.png", 2000, 692, 540, 440);
    helpmenu.scale(.95);
    wsad.scale(0.14);
    spacebar.scale(0.12);
    shift.scale(0.08);
    helpmenu.display(window, sf::Vector2f(0, 0));
    wsad.display(window, sf::Vector2f(0, 0));
    spacebar.display(window, sf::Vector2f(0, 0));
    shift.display(window, sf::Vector2f(0, 0));
    window.display();
}

void Game::cameraupdate(sf::Vector2f playerposition) //offset for objects
{
    if (playerposition.x < (SCREEN_WIDTH / 2))
    {
        cameraoffset.x = 0;
    }
    else if ((playerposition.x >= SCREEN_WIDTH / 2) && (playerposition.x < 127 * 50 - SCREEN_WIDTH / 2))
    {
        cameraoffset.x = playerposition.x - SCREEN_WIDTH / 2;
    }
    else
        cameraoffset.x = 127 * 50 - SCREEN_WIDTH;
    if (playerposition.y < (SCREEN_HEIGHT / 2))
    {
        cameraoffset.y = 0;
    }
    else if ((playerposition.y >= SCREEN_HEIGHT / 2) && (playerposition.y < 127 * 50 - SCREEN_HEIGHT / 2))
    {
        cameraoffset.y = playerposition.y - SCREEN_HEIGHT / 2;
    }
    else
        cameraoffset.y = 127 * 50 - SCREEN_HEIGHT;
}

void Game::save()
{
    temp = *player;
    FILE* file;
    file = fopen("saves/player.dat", "wb");     //player
    if (file == NULL)
    {
        std::cout << "Couldn't open player.dat" << std::endl;
    }
    fwrite(&temp, sizeof(Player), 1, file);
    fclose(file);


    file = fopen("saves/enemy.dat", "wb");      //enemy
    if (file == NULL)
    {
        std::cout << "Couldn't open enemy.dat" << std::endl;
    }
    int i = fwrite(&enemy, sizeof(Enemy), 30, file);
    std::cout << "Saved elements:" << i << std::endl;
    fclose(file);


    file = fopen("saves/data.dat", "wb");       //game data
    if (file == NULL)
    {
        std::cout << "Couldn't open data.dat" << std::endl;
    }
    fwrite(tselectedcharacter, sizeof(int), 1, file);
    fwrite(tdifficulty, sizeof(int), 1, file);
    fwrite(&currentmap, sizeof(int), 1, file);
    fwrite(&score, sizeof(int), 1, file);
    fwrite(&arrowsused, sizeof(int), 1, file);
    fclose(file);


    std::cout << "Saving completed" << std::endl;
}

void Game::load()
{
    FILE* file;
    int temparrows;
    file = fopen("saves/data.dat", "rb"); //DATA
    if (file == NULL)
    {
        std::cout << "Couldn't open enemy.dat" << std::endl;
    }
    fread(tselectedcharacter, sizeof(int), 1, file);
    fread(tdifficulty, sizeof(int), 1, file);
    fread(&currentmap, sizeof(int), 1, file);
    fread(&score, sizeof(int), 1, file);
    fread(&temparrows, sizeof(int), 1, file); //loading arrowsused to temp value
    fclose(file);


    std::cout << "selectedcharacter: " << *tselectedcharacter << std::endl;
    std::cout << "difficulty: " << *tdifficulty << std::endl;
    std::cout << "selectedmap: " << currentmap << std::endl;
    std::cout << "used arrows:" << temparrows << std::endl;
  
    file = fopen("saves/player.dat", "rb");  //PLAYER
    if (file == NULL)
    {
        std::cout << "Couldn't open player.dat" << std::endl;
    }
    fread(&temp, sizeof(Player), 1, file);
    fclose(file);
   
    setup(); //character, set max amount of arrows

    setmap(currentmap); //takes currentmap, sets default settings for arrows

    for (size_t i = 0; i < temparrows; i++) //restore setting for arrows
    {
        arrow[i].isactive = 0;
        arrow[i].isvisible = 0;
    }

    arrowsused = temparrows; //sets amount of arrows already used

    player->setHealth(temp.getHealth());                            //position and health
    player->setPosition(temp.position.x, temp.position.y);
    player->character.setPosition(temp.character.getPosition());

    Enemy tempe[30];

    file = fopen("saves/enemy.dat", "rb");
    if (file == NULL)
    {
        std::cout << "Couldn't open enemy.dat" << std::endl;
    }
    int i = fread(tempe, sizeof(Enemy), 30, file);
    std::cout << "read elements:" << i << std::endl;
    fclose(file);

    for (size_t i = 0; i < 30; i++)
    {
         enemy[i].setHealth(tempe[i].getHealth());
         enemy[i].position.x = tempe[i].position.x;
         enemy[i].position.y = tempe[i].position.y;
         enemy[i].character.setPosition(tempe[i].character.getPosition());
         enemy[i].isdead = tempe[i].isdead;
         enemy[i].spear = tempe[i].spear;
    }



    std::cout << "Loading completed" << std::endl;


}

void Game::runmain(sf::RenderWindow& window) //not used anymore
{
    mainworld.display(window);
    if (clock.getElapsedTime().asMilliseconds() > 20) //50 times per second
    {
        //Handle input
        float x = 0, y = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            y -= player->defspeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            x -= player->defspeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            x += player->defspeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            y += player->defspeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            mainworld.zoom();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            mainworld.unzoom();
        }
        playermap->sprite.move(x, y);
        mainworld.setCamPos(playermap->sprite.getPosition().x, playermap->sprite.getPosition().y);
        clock.restart();
    }
    window.draw(playermap->sprite);
    window.display();
}


void Game::gameover(sf::RenderWindow& window)
{
    player->animate(8);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        gamerestart = 1;
}

void Game::arrows_logic()
{
    for (size_t j = 0; j < numfarrows; j++)
    {
        if (arrow[j].isactive == 1)
        {
            arrow[j].move();
            for (size_t i = 0; i < numofenemies; i++) //arrow hit
            {
                if (enemy[i].isdead == 0)
                {
                    if (arrow[j].direction == 0 && arrow[j].isactive == 1) //right
                    {
                        if ((enemy[i].position.x >= (arrow[j].sprite.getPosition().x + cameraoffset.x)) && (enemy[i].position.x - (arrow[j].sprite.getPosition().x + cameraoffset.x) < 75) && abs(arrow[j].sprite.getPosition().y - enemy[i].position.y) < 35)
                        {
                            enemy[i].defend(2*player->damage);
                            std::cout << "HIT right by an arrow" << std::endl;
                            malescream.play();
                            arrow[j].isactive = 0;
                            arrow[j].isvisible = 0;
                        }
                    }
                    else if (arrow[j].direction == 1 && arrow[j].isactive == 1) //left
                    {
                        if ((enemy[i].position.x <= (arrow[j].sprite.getPosition().x + cameraoffset.x)) && ((arrow[j].sprite.getPosition().x + cameraoffset.x) - enemy[i].position.x < 75) && abs(arrow[j].sprite.getPosition().y - 50 - enemy[i].position.y) < 35)
                        {
                            enemy[i].defend(2 * player->damage);
                            std::cout << "HIT left by an arrow" << std::endl;
                            arrow[j].isactive = 0;
                            arrow[j].isvisible = 0;
                        }
                    }
                    else if (arrow[j].direction == 2 && arrow[j].isactive == 1) //up
                    {
                        if ((enemy[i].position.y <= arrow[j].sprite.getPosition().y) && (arrow[j].sprite.getPosition().y - enemy[i].position.y < 75) && abs((arrow[j].sprite.getPosition().x) - enemy[i].position.x) < 50)
                        {
                            enemy[i].defend(2 * player->damage);
                            std::cout << "HIT up by an arrow" << std::endl;
                            arrow[j].isactive = 0;
                            arrow[j].isvisible = 0;
                        }
                    }
                    else if (arrow[0].direction == 3 && arrow[0].isactive == 1) //down
                    {
                        if ((enemy[i].position.y >= arrow[j].sprite.getPosition().y) && (enemy[i].position.y - arrow[j].sprite.getPosition().y < 75) && abs(arrow[j].sprite.getPosition().x - enemy[i].position.x) < 50)
                        {
                            enemy[i].defend(2 * player->damage);
                            std::cout << "HIT down by an arrow" << std::endl;
                            arrow[j].isactive = 0;
                            arrow[j].isvisible = 0;
                        }
                    }
                }
            }

        }
    }
   
   

}