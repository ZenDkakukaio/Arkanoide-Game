#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;

bool en_collision (Sprite s1, Sprite s2)
{
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}


int main()
{

    srand(time(0));

    RenderWindow fen(VideoMode(1000, 600), "ARKANOIDE");
    fen.setFramerateLimit(60);

     Texture t1, t2, t3, t4;



    t1.loadFromFile("images/bloc.png");
    t2.loadFromFile("images/ballarka.png");
    t3.loadFromFile("images/bgarkanoide.png");
    t4.loadFromFile("images/player1.png");

    Sprite sballarka, sbgarkanoide, splayer1, sbloc;

    sballarka.setTexture(t2);
    sbgarkanoide.setTexture(t3);
    splayer1.setTexture(t4);


    splayer1.setPosition(500,500);
    sballarka.setPosition(500, 400);



     Sprite block[1000];


    int n=0;
    for (int i=1;i<=20;i++)
        {
            for (int j=1;j<=5;j++)
            {
                block[n].setTexture(t1);
                block[n].setPosition(i*45, j*45);
                block[n].setScale(3.f, 3.f);
                n++;



            }

        }

        float dx=8, dy=7;



    while (fen.isOpen())
    {
        Event event;

        Font f1;

        f1.loadFromFile("fonts/RAVIE.TTF");

        Text text1("ARCANOIDE CASH",f1, 40);
        text1.setFillColor(Color::Yellow);
        text1.setPosition(250.f, 3.f);






        while (fen.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                fen.close();
            }
            else if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    fen.close();
                }
            }
        }



        sballarka.move(dx, 0);
        for (int i=0;i<n;i++)
        {
            if (en_collision(sballarka, block[i])) {block[i].setPosition(-100, 0); dx=-dx;}
        }

        sballarka.move(0, dy);
        for (int i=0;i<n;i++)
        {
            if (en_collision(sballarka, block[i])) {block[i].setPosition(-100, 0); dy=-dy;}
        }

        Vector2f b = sballarka.getPosition();
        if (b.x<0 || b.x>1000)  dx=-dx;
        if (b.y<0 || b.y>600)  dy=-dy;

        int speed_touch = 10;

        if (Keyboard::isKeyPressed(Keyboard::Right)) {splayer1.move(speed_touch, 0);}
        if (Keyboard::isKeyPressed(Keyboard::Left)) {splayer1.move(-speed_touch, 0);}
        if (Keyboard::isKeyPressed(Keyboard::Up)) {splayer1.move(0, -speed_touch);}
        if (Keyboard::isKeyPressed(Keyboard::Down)) {splayer1.move(0, speed_touch);}

        if (en_collision(splayer1, sballarka)) {dy=-(rand()%5+2);}



        fen.clear();
        fen.draw(sbgarkanoide);
        fen.draw(sballarka);
        fen.draw(splayer1);
        fen.draw(text1);

       // fen.draw(sbloc);

       for (int i=0;i<=n;i++)
       {
           fen.draw(block[i]);
       }








        fen.display();
    }

    return EXIT_SUCCESS;







}
