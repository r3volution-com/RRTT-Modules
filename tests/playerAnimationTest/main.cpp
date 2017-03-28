/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: pablo
 *
 * Created on 15 de marzo de 2017, 9:43
 */

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <cstdio>

#include "../Player.h"
#include "../Gun.h"
using namespace std;

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
    char direc = 'z';
    char direcX = 'z';
    float PI = 3.14159265f;
    float mouseAng = 0.0f;
    float mousePos[2]={0,0};
    float windowSize[2]={0,0};
    windowSize[0]=window.getSize().x/2;
    windowSize[1]=window.getSize().y/2;
    
    
    bool mov = true;
    Texture *text = new Texture("resources/sprites.png");
    Player *rath = new Player(new Rect<float> (320, 240, 128, 128), 1.0f);
    Gun *scytheArm = new Gun(new Coordinate(320, 240 ),new Rect<float>(0 ,512, 128 ,128), text, 1, 0.5f);
    Gun *gunArm = new Gun(new Coordinate(600, 240),new Rect<float> (0, 640, 128, 128), text, 0, 1.0f);
    gunArm->setOrigin(64,30);
    rath->loadAnimation(text, new Coordinate(0,0), 3, 0.5f);
    window.setFramerateLimit(120);
    rath->setWeapon(scytheArm);
    rath->addGun(gunArm);

    
    //Bucle del juego
    while (window.isOpen()) {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
                default: break;
            }
        }
        mousePos[0]=sf::Mouse::getPosition(window).x-windowSize[0];
        mousePos[1]=(sf::Mouse::getPosition(window).y-windowSize[1])*-1;
        //float hip = std::sqrt(mousePos[0]*mousePos[0]+mousePos[1]*mousePos[1]);
        //float mouseAng = acos((mousePos[0]*mousePos[0]+hip*hip-mousePos[1]*mousePos[0])/(2*mousePos[0]*hip))*180/PI;
        
        //if(mouseAng<=90 || mouseAng>=270){
        //gunArm->getAnimation()->changeSpriteRect(new Rect<float>(0, 640, 128, 128));

        if(mousePos[0]>=0 && mousePos[1]>=0){
        mouseAng=atan(mousePos[0]/mousePos[1])*180/PI+180;    
        //derecha arriba
        }
        else{if(mousePos[0]<=0 && mousePos[1]>=0){
            mousePos[0]=0-mousePos[0];
            mouseAng=atan(mousePos[1]/mousePos[0])*180/PI+90;
            //izquierda arriba
        }
        else{if(mousePos[0]<0 && mousePos[1]<0){
            mousePos[0]=0-mousePos[0];
            mousePos[1]=0-mousePos[1];
            mouseAng=atan(mousePos[0]/mousePos[1])*180/PI;
            //izquierda abajo
        }
        else{if(mousePos[0]>0 && mousePos[1]<0){
            mousePos[1]=0-mousePos[1];
            mouseAng=atan(mousePos[1]/mousePos[0])*180/PI+270;
            //derecha abajo
        }
        }
        }
        }
        gunArm->setRotation(mouseAng);    
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(mouseAng<315 && mouseAng>225){
                //derecha BIEN
                rath->weaponAttack(new Rect<float>(0, 768, 128, 128));
            }
            if(mouseAng<225 && mouseAng>135){
                //arriba BIEN
                rath->weaponAttack(new Rect<float>(0, 1152, 128, 128));
            }
            if(mouseAng<135 && mouseAng>45){
                //izquierda BIEN
                rath->weaponAttack(new Rect<float>(0, 896, 128, 128));
            }
            if(mouseAng<45 || mouseAng>315){
                //abajo BIEN
                rath->weaponAttack(new Rect<float>(0, 1024, 128, 128));
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rath->move(0, -1);
            if( direc != 'u'){
                rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 256, 128, 128));
                }
                mov=true;
                direc='u';
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                rath->move(0, 1);
                if(direcX=='r' && direc!='d'){
                    if(direc!='d'){
                        rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 128, 128, 128));  
                        direc=='d';
                        mov=true;
                    }
                }
                else{
                    if(direcX=='l'&& direc!='d'){
                        if(direc!='d'){
                            rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 384, 128, 128));
                            direc=='d';
                            mov=true;
                        }
                    }
                    else{
                        if(direcX=='r'&& direc!='d'){
                            if(direc!='d'){
                                rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 128, 128, 128));
                                direc=='d';
                                mov=true;
                                
                            }
                        }
                    }
                }
            }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rath->move(1, 0);
            if( direc !='r'){
                rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 128, 128, 128));
            }
            direc='r';
            direcX='r';
            mov=true;
        }
        else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                rath->move(-1, 0);
                if( direc !='l'){
                    rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 384, 128, 128));
                }
                direc='l';
                direcX='l';
                mov=true;
            }
        }
        
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
        && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& mov==true){
                    direc='I';
                    rath->getAnimation()->changeSpriteRect(new Rect<float>(0,0,128,128));
                    mov=false;
            }
                
        window.clear();
        window.draw(gunArm->getAnimation()->getCurrentSprite());
        window.draw(scytheArm->getAnimation()->getCurrentSprite());
        window.draw(rath->getAnimation()->getCurrentSprite());
        window.display();
        
    }
    return 0;
}
