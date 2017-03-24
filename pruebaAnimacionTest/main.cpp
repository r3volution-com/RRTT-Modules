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
    char direcY = 'z';
    char direcX = 'z';
    char animX = 'z';
    float PI = 3.14159265f;
    float mouseAng = 0.0f;
    float mousePos[2]={0,0};
    float windowSize[2]={0,0};
    windowSize[0]=window.getSize().x/2;
    windowSize[1]=window.getSize().y/2;
    
    
    bool mov = true;
    Texture *text = new Texture("resources/sprites.png");
    Player *rath = new Player(new Rect<float> (320, 240, 128, 128), 1.0f);
    Gun *scytheArm = new Gun(new Coordinate(320, 240 ),new Rect<float>(0 ,512, 128 ,128), text, 3, 1.0f);
    Gun *gunArm = new Gun(new Coordinate(320, 240),new Rect<float> (0, 640, 128, 128), text, 3, 1.0f);
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
        mousePos[0]=sf::Mouse::getPosition().x-windowSize[0];
        mousePos[1]=(sf::Mouse::getPosition().y-windowSize[1])*-1;
        float hip = std::sqrt(mousePos[0]*mousePos[0]+mousePos[1]*mousePos[1]);
        float mouseAng = acos((mousePos[0]*mousePos[0]+hip*hip-mousePos[1]*mousePos[0])/(2*mousePos[0]*hip))*180/PI;
        
        if(mouseAng<=90 || mouseAng>=270){
        gunArm->getAnimation()->changeSpriteRect(new Rect<float>(0, 768, 128, 128));
        //sf::Transform Rotacion(cos (mouseAng*PI/180), -sin (mouseAng*PI/180),0,
             //   sin (mouseAng*PI/180), -cos (mouseAng*PI/180),0,
             //   0,     0,      1);
        //   }   
        //   if(mouseAng<270 && mouseAng>90){
        gunArm->setRotation(mouseAng);
        }    
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if((mouseAng>0 && mouseAng<45) || mouseAng > 315 && mouseAng < 360){
                //derecha
                
            }
            if(mouseAng>45 && mouseAng<135){//arriba
                
            }
            if(mouseAng>135 && mouseAng<225){//izquierda
                
            }
            if(mouseAng>225 && mouseAng<315){//abajo
                
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rath->move(1, 0);
            if( animX !='r'){
                rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 128, 128, 128));
            }
            direcX='r';
            animX='r';
            mov=true;
        }
        else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                rath->move(-1, 0);
                if( animX !='l'){
                    rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 384, 128, 128));
                }
                direcX='l';
                animX='l';
                mov=true;
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rath->move(0, -1);
            if( direcY != 'u'){
                rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 256, 128, 128));
                }
                mov=true;
                direcY='u';
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                rath->move(0, 1);
                if(direcX=='r' && direcY!='d'){
                    if(mov==false){
                        rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 128, 128, 128));  
                        direcY=='d';
                        mov=true;
                    }
                }
                else{
                    if(direcX=='l'&& direcY!='d'){
                        if(mov==false){
                            rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 384, 128, 128));
                            direcY=='d';
                            mov=true;
                        }
                    }
                    else{
                        if(direcX=='r'&& direcY!='d'){
                            if(mov==false){
                                rath->getAnimation()->changeSpriteRect(new Rect<float>(0, 128, 128, 128));
                                direcY=='d';
                                mov=true;
                                
                            }
                        }
                    }
                }
            }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
        && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& mov==true){
                    direcY='I';
                    animX='I';
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
