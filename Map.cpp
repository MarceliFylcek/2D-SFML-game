#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

Map::Map(int selectedmap, int SCREEN_WIDTH, int SCREEN_HEIGHT) //Save parameters, set textures for sprite
{
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->selectedmap = selectedmap;
    

    //Initialize the background
    backgroundimg1.loadFromFile("images/background1.png");
    background.setTexture(backgroundimg1);

    //Initialize graphical objects
    //Stone 1
    stonetile.loadFromFile("images/stonetexture.png");
    defstonetile.setTexture(stonetile);
    //Stone 1 shadow
    stonetileshadow.loadFromFile("images/stoneshadow.png");
    defstoneshadow.setTexture(stonetileshadow);
    //Stone 2
    stonetile2.loadFromFile("images/stonetexture2.png");
    defstonetile2.setTexture(stonetile2);
    //Grass 1/2
    grass.loadFromFile("images/grasstexture.png");
    grasstile.setTexture(grass);
    //Full grass
    grass1.loadFromFile("images/grass.png");
    grass1s.setTexture(grass1);
    //Dirt
    dirt.loadFromFile("images/dirt.png");
    dirttile.setTexture(dirt);
    //Water
    water.loadFromFile("images/water.png");
    watertile.setTexture(water);
    //Campfire
    campfire = new AnimatedObject("images/campfire.png", 16, 16, 4, 56*50, 680);
    (*campfire).scale(4);
    //Flower
    flower = new Object("images/flowers2.png", 128, 128, 100, 500);
    flower->scale(0.5);
    //Trees
    trees = new Object("images/trees.png", 352, 256, 0, 0);
    (*trees).scale(2.5);
    //Tent
    tent = new  Object("images/Tent.png", 32, 26, 0, 0);
    tent->scale(3.5);
    //Well
    well = new  Object("images/well.png", 34, 34, 0, 0);
    well->scale(2);
    //Barrel
    barrels = new Object("images/barrels.png", 32, 32, 0, 0);
    //House1
    house1 = new Object("images/house1.png", 162, 228, 0, 0);
    house1->scale(1.5);
    //Goat
    goat = new AnimatedObject("images/goat.png", 128, 128, 4, 0, 7);
    goat->changeSheet(0, 5);
    //Woodenwall
    woodenwall = new Object("images/woodenwall.png", 133, 84, 0, 0);
    woodenwall->scale(2);
    //Woodenwall front and back
    woodenwallfront = new Object("images/fence_medieval.png", 32, 32, 0, 0);
    woodenwallfront->scale(3);
    //Fences
    fences = new Object("images/fence_medieval.png", 32, 32, 0, 0);
    fences->scale(2);
    //Decorations
    decorations = new Object("images/decorations-medieval.png", 32, 32, 0, 0);
    decorations->scale(1.25);
    //Fire
    fire = new AnimatedObject("images/fire.png", 64, 64, 3, 0, 0);
    //Dead body;
    deadbody = new Object("images/villager.png", 64, 64, 0, 0);
    deadbody->scale(1.5);
    deadbody->changeSheet(5, 20);
    //Villager
    villager = new Object("images/villager.png", 64, 64, 0, 0);
    villager->scale(1.5);
    villager->changeSheet(0, 14);
    //Mother&child
    mother = new Object("images/mother.png", 64, 64, 0, 0);
    child = new Object("images/child.png", 64, 64, 0, 0);
    mother->scale(1.5);
    child->scale(1.5);
    mother->changeSheet(0, 10);
    child->changeSheet(0, 10);
}
void Map::moveEntity(float x, float y, Player* object)
{
    if (selectedmap == 1) //forest location
    {
        Vector4b vec;
        vec = collision((*object).position, 64, 42, forrestobj); //update collsions
        float dx = 0;
        float dy = 0;
        if (x < 0 && vec.l == 0) //left
        {
            dx = x;
        }
        else if (x > 0 && vec.r == 0) //right
        {
            dx = x;
        }
        if (y < 0 && vec.t == 0) //up
        {
            dy = y;
        }
        else if (y > 0 && vec.d == 0) //down
        {
            dy = y;
        }
        (*object).move(dx, dy); //back to player/enemy
    }
    if (selectedmap == 2) //forest location
    {
        Vector4b vec;
        vec = collision((*object).position, 57, 40, castle1obj); //update collsions
        float dx = 0;
        float dy = 0;
        if (x < 0 && vec.l == 0) //left
        {
            dx = x;
        }
        else if (x > 0 && vec.r == 0) //right
        {
            dx = x;
        }
        if (y < 0 && vec.t == 0) //up
        {
            dy = y;
        }
        else if (y > 0 && vec.d == 0) //down
        {
            dy = y;
        }
        (*object).move(dx, dy); //back to player/enemy
    }
    if (selectedmap == 3) //final
    {
        Vector4b vec;
        vec = collision((*object).position, 57, 40, finalobj); //update collsions
        float dx = 0;
        float dy = 0;
        if (x < 0 && vec.l == 0) //left
        {
            dx = x;
        }
        else if (x > 0 && vec.r == 0) //right
        {
            dx = x;
        }
        if (y < 0 && vec.t == 0) //up
        {
            dy = y;
        }
        else if (y > 0 && vec.d == 0) //down
        {
            dy = y;
        }
        (*object).move(dx, dy); //back to player/enemy
    }
   
}
Vector4b Map::collision(sf::Vector2f position, float height, float width, char Map[18][128])
{
    Vector4b collision;
    int lx = (position.x - width/2) / 50;  //left side x                                                  //            (lx, ty)   x  o  x  (rx,ty)
    int rx = (position.x + width / 2) / 50;  //right side x                                               //                         -|-       
    int ty = (position.y) / 50;  //top(head) y  for right/left collisions                                 //            (lx, my)   x  |  x  (rx, my)   
    int by = (position.y + height) / 50; //bottom(feet) y, for right/left collisions                      //                         _ _        
    int my = (position.y + (height / 2)) / 50;  //medium(belt) y                                          //            (lx, by)   x     x  (rx, by)   
    int my1 = (position.y + (height / 2) - 5) / 50; // for top collisions
    int by1 = (position.y + height + 5) / 50; //for bottom collsions
    int lx1 = ((position.x - (width / 2) - 5)) / 50;
    int rx1 = ((position.x + width / 2) + 5) / 50;
  
   //!postion.x goes through the middle, position.y goes through head!


    //check for left collisions
    if (Map[my][lx1] != ' ' || Map[by][lx1] != ' ') //legs blocked, torso goes through
        collision.l = 1;
    else
        collision.l = 0;

    if (Map[my][rx1] != ' ' || Map[by][rx1] != ' ') //right
        collision.r = 1;
    else
        collision.r = 0;

    if (Map[my1][rx] != ' ' || Map[my1][lx] != ' ') //top
        collision.t = 1;
    else
        collision.t = 0;

    if (Map[by1][lx] != ' ' || Map[by1][rx] != ' ') //down
        collision.d = 1;
    else
        collision.d = 0;


    if ((position.x - width/2) < 0)
        collision.l = 1;
    if (position.y < 0)
        collision.t = 1;
    if (position.y + height > SCREEN_HEIGHT)
        collision.d = 1;


    return collision;
}
void Map::draw(sf::RenderWindow& window, sf::Vector2f cameraoffset)
{
    if (selectedmap == 1)
    {
        //Blocks
        window.clear(sf::Color(35, 117, 52));
        for (int i = 0; i < 18; i++) //y 0-8
        {
            for (int j = 0; j < 128; j++) //x 0-15
            {
                if (forresttxt[i][j] == '#')
                {
                    defstonetile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(defstonetile);
                }
                if (forresttxt[i][j] == '+')
                {
                    defstoneshadow.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(defstoneshadow);
                }
                if (forresttxt[i][j] == '-')
                {
                    grasstile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(grasstile);
                }
                if (forresttxt[i][j] == '*')
                {
                    defstonetile2.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(defstonetile2);
                }
                if (forresttxt[i][j] == '@')
                {
                    dirttile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(dirttile);
                }
                if (forresttxt[i][j] == 'o')
                {
                    watertile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(watertile);
                }
                if (forresttxt[i][j] == ' ')
                {
                    grass1s.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(grass1s);
                }
            }

        }


        //Objects

        //Campfires
        (*campfire).animate();
        (*campfire).display(window, cameraoffset);
        campfire->displayAt(window, cameraoffset, 88 * 50, 550);
        campfire->displayAt(window, cameraoffset, 119 * 50, 200);

        //Flowers


        //Trees
        (*trees).display(window, cameraoffset);
        (*trees).displayAt(window, cameraoffset, 1000, -200);
        (*trees).displayAt(window, cameraoffset, 2000, -400);
        (*trees).displayAt(window, cameraoffset, 3000, -300);
        (*trees).displayAt(window, cameraoffset, 4000, -450);
        (*trees).displayAt(window, cameraoffset, 5000, -300);

        //Tent
        (*tent).displayAt(window, cameraoffset, 122 * 50, 100);
        (*tent).displayAt(window, cameraoffset, 122 * 50, 200);
        (*tent).displayAt(window, cameraoffset, 122 * 50, 300);
        (*tent).displayAt(window, cameraoffset, 118 * 50, 350);

        //Well
        well->displayAt(window, cameraoffset, 115 * 50, 400);

        //Barrel
        barrels->displayAt(window, cameraoffset, 117 * 50, 450);


    }
    if (selectedmap == 2)
    {
        //Blocks
        window.clear(sf::Color(35, 117, 52));
        for (int i = 0; i < 18; i++) //y 0-8
        {
            for (int j = 0; j < 128; j++) //x 0-15
            {
                if (castle1[i][j] == '#')
                {
                    defstonetile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(defstonetile);
                }
                if (castle1[i][j] == '-')
                {
                    grasstile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(grasstile);
                }
                if (castle1[i][j] == '*')
                {
                    defstonetile2.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(defstonetile2);
                }
                if (castle1[i][j] == '@')
                {
                    dirttile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(dirttile);
                }
                if (castle1[i][j] == 'o')
                {
                    watertile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(watertile);
                }
                if (castle1[i][j] == ' ')
                {
                    grass1s.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(grass1s);
                }
            }

        }
        (*flower).displayAt(window, cameraoffset, 200, 200);
        (*flower).displayAt(window, cameraoffset, 600, 700);
        (*flower).displayAt(window, cameraoffset, 26 * 50 + 30, 8 * 50 + 5);
        flower->displayAtSheet(window, cameraoffset, 400, 700, 3, 0);
        flower->displayAtSheet(window, cameraoffset, 500, 200, 5, 2);
        flower->displayAtSheet(window, cameraoffset, 200, 100, 5, 2);
        flower->displayAtSheet(window, cameraoffset, 100, 600, 5, 3);
        flower->displayAtSheet(window, cameraoffset, 600, 200, 0, 5);
        flower->displayAtSheet(window, cameraoffset, 0, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 50, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 100, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 150, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 200, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 250, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 300, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 350, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 400, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 450, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 500, 0, 5, 6);
        flower->displayAtSheet(window, cameraoffset, 550, 0, 5, 6);
        (*trees).displayAt(window, cameraoffset, -100, 800);
        for (int i = 0; i < 10; i++)
        {
            woodenwall->displayAt(window, cameraoffset, 2234+(i*266), 0);
        }
        house1->displayAt(window, cameraoffset, 2500, 0);
        house1->displayAt(window, cameraoffset, 2800, 0);
        house1->displayAt(window, cameraoffset, 3100, 0);
        house1->displayAt(window, cameraoffset, 3400, 0);
        house1->displayAt(window, cameraoffset, 3700, 0);
        house1->displayAt(window, cameraoffset, 3700, 700);
        house1->displayAt(window, cameraoffset, 3400, 700);
        house1->displayAt(window, cameraoffset, 3100, 700);
        well->displayAt(window, cameraoffset, 2880, 700);
        goat->displayAt(window, cameraoffset, 2600, 700);
        goat->animate();
        barrels->displayAtSheet(window, cameraoffset, 2820, 350,  2, 0);
        flower->displayAtSheet(window, cameraoffset, 105*50, 700, 3, 0);
        flower->displayAtSheet(window, cameraoffset, 110*50, 200, 3, 0);


        //wooden fence
        fences->displayAtSheet(window, cameraoffset, 2150, 70 + 32,  11, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 70 + 64,  10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 70 + 96,  10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 70 + 128, 10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 70 + 160, 10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 70 + 192, 9, 7);


        fences->displayAtSheet(window, cameraoffset, 2150, 500 + 32, 11, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 500 + 64, 10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 500 + 96, 10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 500 + 128, 10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 500 + 160, 10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 500 + 192, 10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 500 + 224, 10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 500 + 256, 10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 500 + 288, 10, 7);
        fences->displayAtSheet(window, cameraoffset, 2150, 500 + 320, 9, 7);

        //stone fence(goat)
        fences->displayAtSheet(window, cameraoffset, 2400 - 64 +50, 650, 6, 6);
        fences->displayAtSheet(window, cameraoffset, 2400 - 32 +50, 650, 7, 6);
        fences->displayAtSheet(window, cameraoffset, 2400+50, 650, 7, 6);
        fences->displayAtSheet(window, cameraoffset, 2432+50, 650, 7, 6);
        fences->displayAtSheet(window, cameraoffset, 2464+50, 650, 7, 6);
        fences->displayAtSheet(window, cameraoffset, 2464+50 + 32, 650, 7, 6);
        fences->displayAtSheet(window, cameraoffset, 2464+50 + 64, 650, 7, 6);
        fences->displayAtSheet(window, cameraoffset, 2464+50 + 96, 650, 7, 6);
        fences->displayAtSheet(window, cameraoffset, 2464+50 + 128, 650, 7, 6);
        fences->displayAtSheet(window, cameraoffset, 2400+50 + 160, 650, 6, 6);
        fences->displayAtSheet(window, cameraoffset, 2400+50 + 192, 650, 6, 6);
        fences->displayAtSheet(window, cameraoffset, 2400+50 + 224, 650, 6, 6);
        fences->displayAtSheet(window, cameraoffset, 2464+50 + 224, 650, 8, 6);


        fences->displayAtSheet(window, cameraoffset, 2400+50 - 96, 650 + 32, 8, 7);
        fences->displayAtSheet(window, cameraoffset, 2400+50 - 96, 650 + 64, 7, 7);
        fences->displayAtSheet(window, cameraoffset, 2400+50 - 96, 650 + 92, 7, 7);
        fences->displayAtSheet(window, cameraoffset, 2400+50 - 96, 650 + 124, 7, 7);
        fences->displayAtSheet(window, cameraoffset, 2400+50 - 96, 650 + 156, 7, 7);
        fences->displayAtSheet(window, cameraoffset, 2400+50 - 96, 650 + 188, 7, 7);

        fences->displayAtSheet(window, cameraoffset, 2400+50 + 330, 650 + 32, 8, 7);
        fences->displayAtSheet(window, cameraoffset, 2400+50 + 330, 650 + 64, 7, 7);
        fences->displayAtSheet(window, cameraoffset, 2400+50 + 330, 650 + 92, 7, 7);
        fences->displayAtSheet(window, cameraoffset, 2400+50 + 330, 650 + 124, 7, 7);
        fences->displayAtSheet(window, cameraoffset, 2400+50 + 330, 650 + 156, 7, 7);
        fences->displayAtSheet(window, cameraoffset, 2400+50 + 330, 650 + 188, 7, 7);
 




        //wooden wall
        //front
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 0, 3, 12);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 0 + 64, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 0 + 128, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 0 + 192, 3, 14);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 0 + 256, 3, 15);


        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 430, 3, 12);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 430 + 64, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 430 + 128, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 430 + 192, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 430 + 256, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 430 + 320, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 430 + 384, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 2230, 430 + 448, 3, 13);

        //back
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 0, 3, 12);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 0 + 64, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 0 + 128, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 0 + 192, 3, 14);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 0 + 256, 3, 15);
                                                               
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 430, 3, 12);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 430 + 64, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 430 + 128, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 430 + 192, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 430 + 256, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 430 + 320, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 430 + 384, 3, 13);
        woodenwallfront->displayAtSheet(window, cameraoffset, 98*50, 430 + 448, 3, 13);


        //Hay
        decorations->displayAtSpecific(window, cameraoffset, 48 * 50, 6.2 * 50 - 32, 7*64-32, 8*64, 100, 64);

        decorations->displayAtSpecific(window, cameraoffset, 39 * 50, 3 * 50, 0, 650, 60, 80);
        decorations->displayAtSpecific(window, cameraoffset, 41 * 50, 4 * 50, 0, 650, 60, 80);

        //cart
        decorations->displayAtSpecific(window, cameraoffset, 60 * 50, 9 * 50-10, 3 * 64, 8 * 64, 80, 75);

        //pole
        decorations->displayAtSpecific(window, cameraoffset, 27 * 50, 7 * 50, 360, 190, 10, 90);
       

        //sign
        decorations->displayAtSpecific(window, cameraoffset, 27 * 50, 7 * 50, 200, 230, 25, 30);
        decorations->displayAtSpecific(window, cameraoffset, 40 * 50, 13 * 50, 320, 128, 32, 70);


        //stand
        decorations->displayAtSpecific(window, cameraoffset, 65 * 50, 10 * 50, 62, 1344, 97, 60);

        //
        decorations->displayAtSpecific(window, cameraoffset, 69 * 50, 10 * 50, 200, 1280, 110, 110);

        //fontain
        decorations->displayAtSpecific(window, cameraoffset, 88 * 50-10, 8 * 50, 0, 576, 70, 70);

        //monument
        decorations->displayAtSpecific(window, cameraoffset, 88 * 50+10, 13 * 50, 130, 290, 30, 60);
        decorations->displayAtSpecific(window, cameraoffset, 88 * 50 + 10, 7 * 50, 130, 290, 30, 60);

        //fire
        //hay1
        fire->displayAt(window, cameraoffset, 39 * 50, 3 * 50);
        fire->displayAt(window, cameraoffset, 39 * 50+15, 3 * 50-15);
        //hay2
        fire->displayAt(window, cameraoffset, 41 * 50, 4 * 50);
        fire->displayAt(window, cameraoffset, 41 * 50 + 15, 4 * 50 - 15);
        //hay3
        fire->displayAt(window, cameraoffset, 48 * 50 + 20, 6.2 * 50 - 37);

        //house1
        fire->displayAt(window, cameraoffset, 2520, 100);
        fire->displayAt(window, cameraoffset, 2600, 50);
        //house2
        fire->displayAt(window, cameraoffset, 2900, 100);
        fire->displayAt(window, cameraoffset, 2820, 50);
        //house3
        fire->displayAt(window, cameraoffset, 3120, 100);
        fire->displayAt(window, cameraoffset, 3200, 50);
        //house4
        fire->displayAt(window, cameraoffset, 3800, 100);
        fire->displayAt(window, cameraoffset, 3720, 50);
        //house5
        fire->displayAt(window, cameraoffset, 3420, 800);
        fire->displayAt(window, cameraoffset, 3500, 750);
        
        //
        fire->displayAt(window, cameraoffset, 69 * 50+10, 10 * 50+20);
        fire->displayAt(window, cameraoffset, 69 * 50 + 40, 10 * 50 + 40);

        fire->animate();

        //dead bodies
        deadbody->displayAt(window, cameraoffset, 32 * 50, 11 * 50);
        deadbody->displayAt(window, cameraoffset, 33 * 50, 8 * 50);
        deadbody->displayAt(window, cameraoffset, 35 * 50, 12 * 50);
        deadbody->displayAt(window, cameraoffset, 36 * 50, 13 * 50);
        deadbody->displayAt(window, cameraoffset, 39 * 50, 8 * 50);
        deadbody->displayAt(window, cameraoffset, 31 * 50, 4 * 50);
        deadbody->displayAt(window, cameraoffset, 28 * 50, 4 * 50);
        deadbody->displayAt(window, cameraoffset, 28 * 50, 15 * 50);
        deadbody->displayAt(window, cameraoffset, 53 * 50, 8 * 50);
        deadbody->displayAt(window, cameraoffset, 55 * 50, 9 * 50);
        deadbody->displayAt(window, cameraoffset, 67 * 50, 7 * 50);
        deadbody->displayAt(window, cameraoffset, 70 * 50, 14 * 50);
        deadbody->displayAt(window, cameraoffset, 72 * 50, 7 * 50);
        deadbody->displayAt(window, cameraoffset, 29 * 50, 6 * 50);
        deadbody->displayAt(window, cameraoffset, 81 * 50, 8 * 50);
        deadbody->displayAt(window, cameraoffset, 83 * 50, 9 * 50);
        deadbody->displayAt(window, cameraoffset, 95 * 50, 3 * 50);
        deadbody->displayAt(window, cameraoffset, 96 * 50, 13 * 50);
        deadbody->displayAt(window, cameraoffset, 47 * 50, 7 * 50);

        //villagers
        villager->displayAtSheet(window, cameraoffset, 126 * 50, 5 * 50, 0, 10);
        villager->displayAtSheet(window, cameraoffset, 124 * 50, 9 * 50, 0, 10);
        villager->displayAtSheet(window, cameraoffset, 123 * 50, 5 * 50, 0, 10);
        villager->displayAtSheet(window, cameraoffset, 122 * 50, 7 * 50, 0, 10);
        villager->displayAtSheet(window, cameraoffset, 122 * 50, 8 * 50, 0, 10);
        villager->displayAtSheet(window, cameraoffset, 123 * 50, 9 * 50, 0, 10);
        villager->displayAtSheet(window, cameraoffset, 124 * 50, 6 * 50, 0, 10);

        //mother & child
        mother->displayAt(window, cameraoffset, 123.5 * 50, 7.5 * 50); //124 125
        child->displayAt(window, cameraoffset, 124.5 * 50, 7.5 * 50);





    }

    if (selectedmap == 3)
    {
        //Blocks
        window.clear(sf::Color(35, 117, 52));
        for (int i = 0; i < 18; i++) //y 0-8
        {
            for (int j = 0; j < 128; j++) //x 0-15
            {
                if (final[i][j] == '#')
                {
                    defstonetile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(defstonetile);
                }
                if (final[i][j] == '-')
                {
                    grasstile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(grasstile);
                }
                if (final[i][j] == '*')
                {
                    defstonetile2.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(defstonetile2);
                }
                if (final[i][j] == '@')
                {
                    dirttile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(dirttile);
                }
                if (final[i][j] == 'o')
                {
                    watertile.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(watertile);
                }
                if (final[i][j] == ' ')
                {
                    grass1s.setPosition(((SCREEN_WIDTH / 32) * j) - cameraoffset.x, (SCREEN_HEIGHT / 18) * i);
                    window.draw(grass1s);
                }
            }

        }
    }
   
   
}
int Map::getmap()
{
    return selectedmap;
}
void Map::setmap(int map)
{
    selectedmap = map;
}