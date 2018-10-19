#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <iostream>

using namespace sf;

Event ev;
Player hero({20});

void game(){
    hero.setPos({50.0f, 500.0f});
    float gravity=1.0f, jumpSpeed=25.0f;
    int vSpeed=0;
    bool isJumping=false, moving=true;
    RenderWindow win(VideoMode(1000, 600), "Hello World");
    win.setFramerateLimit(60);

    RectangleShape groundR({1000, 10});
    groundR.setPosition(0, 540);
    groundR.setFillColor(Color::Green);

    while(win.isOpen()){

        if(Keyboard::isKeyPressed(Keyboard::Up)){
            hero.move({0, -jumpSpeed});
            isJumping=true;
        }
        if(Keyboard::isKeyPressed(Keyboard::Right)){
            if(vSpeed<80) vSpeed+=2;
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            if(vSpeed>-80) vSpeed-=2;
        }

        if(isJumping) jumpSpeed-=gravity;

        if(hero.getY()<500.0f && !isJumping) {
            jumpSpeed-=gravity;
            hero.move({0, -jumpSpeed});
        }

        if(hero.getY()>=500.0f && isJumping) jumpSpeed=25.0f;
        if(hero.getY()>=500.0f && !isJumping) jumpSpeed=0.0f, hero.setPos({hero.getX(), 500.0f});

        if(!moving){
            if(vSpeed>=0) vSpeed-=2;
            if(vSpeed<=0) vSpeed+=2;
            if(vSpeed==0) moving=false;
        }

        if(vSpeed!=0) hero.move({(float)vSpeed/10.0f, 0});

        while(win.pollEvent(ev)){
            switch(ev.type){
            case Event::Closed:
                win.close();
            case Event::KeyReleased:
                if(ev.key.code==Keyboard::Up) isJumping=false;
                if(ev.key.code==Keyboard::Left || ev.key.code==Keyboard::Right) moving=false;
            default:
                break;
            }
        }

        win.clear();
        win.draw(groundR);
        hero.drawTo(win);
        win.display();

    }
}

#endif //GAME_HPP_INCLUDED
