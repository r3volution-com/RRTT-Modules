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
#include <math.h>

#include "../Entity.h" //ToDo: cambiarlo por player
using namespace std;

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
    char direcY = 'z';
    char direcX = 'z';
    char animX = 'z';
    float PI = 3.14159265f;
    float mouseAng = 0.0f;
    float mousePos[2]={0,0};
    
    bool mov = true;
    Texture *text = new Texture("resources/sprites.png");
    Entity *rath = new Entity(320, 240, 128, 128, 1.0f);
    Entity *scytheArm = new Entity(320, 240, 128, 128, 1.0f);
    Entity *gunArm = new Entity(320, 240, 128, 128, 1.0f);
    rath->loadAnimation(text, 0, 0, 3, 0.5f);
    scytheArm->loadAnimation(text, 0, 512, 3, 0.5f);
    gunArm ->loadAnimation(text, 0, 640, 3, 0.5f);
    window.setFramerateLimit(120);
    
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
        
        sf::vector2 mousePos=sf::Mouse::getPosition(Window&);
        float hip = sqrt(mousePos[0]*mousePos[0]+mousePos[1]*mousePos[1]);
        float mouseAng = acos((mousePos[0]*mousePos[0]+hip*hip-mousePos[1]*mousePos[0])/(2*mousePos[0]*hip))*180/PI;
        
        if(mouseAng<=90 || mouseAng>=270){
            gunArm->setRotation(float mouseAng);
        }   
        if(mouseAng<270 && mouseAng>90){
            
        }    
        
        if(sf::Mouse::isButtonPressed(Button Left)){
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
            scytheArm->move(1, 0);
            if( animX !='r'){
                rath->getAnimation()->changeSpriteRect(0, 128, 128, 128);
            }
            direcX='r';
            animX='r';
            mov=true;
        }
        else{if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            rath->move(-1, 0);
            scytheArm->move(-1, 0);
            if( animX !='l'){
                rath->getAnimation()->changeSpriteRect(0, 384, 128, 128);
            }
            direcX='l';
            animX='l';
            mov=true;
        }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rath->move(0, -1);
            scytheArm->move(0, -1);
            if( direcY != 'u'){
                rath->getAnimation()->changeSpriteRect(0, 256, 128, 128);
            }
            mov=true;
            direcY='u';
        }
        
        else{if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rath->move(0, 1);
            scytheArm->move(0, 1);
            if(direcY=='u' && direcY!='d'){
                if(mov==false){
                    rath->getAnimation()->changeSpriteRect(0, 128, 128, 128);  
                    direcY=='d';
                    mov=true;
                }
            }
            else{
                if(direcX=='l'&& direcY!='d'){
                    if(mov==false){
                        rath->getAnimation()->changeSpriteRect(0, 384, 128, 128);
                        direcY=='d';
                        mov=true;
                    }
                }
                else{
                    if(direcX=='r'&& direcY!='d'){
                        if(mov==false){
                            rath->getAnimation()->changeSpriteRect(0, 128, 128, 128);
                            direcY=='d';
                             mov=true;
                            }
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
                    rath->getAnimation()->changeSpriteRect(0,0,128,128);
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
