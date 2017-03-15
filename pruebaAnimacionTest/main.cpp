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

#include "../Entity.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
     sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
     char direcY = 'z';
     char direcX = 'z';
     bool mov = true;
     Texture *text = new Texture("resources/sprites.png");
     Entity *rath = new Entity(320, 240, 128, 128, 1.0f);
     rath->loadAnimation(text, 0, 0, 4, 0.1f);
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
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rath->move(1, 0);
            if( direcX!='r'){
                rath->getAnimation()->changeSpriteRect(0, 128, 128, 128);
            }
            direcX='r';}
        else{if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            rath->move(-1, 0);
            if( direcX !='l'){
                rath->getAnimation()->changeSpriteRect(0, 384, 128, 128);
                }
                direcX='l';
                }
            }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rath->move(0, -1);
            if( direcY != 'u'){
                rath->getAnimation()->changeSpriteRect(0, 256, 128, 128);
            }
            direcY='u';
        }
        
        else{if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rath->move(0, 1);
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
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& direcY!='I'){
            direcY='I';
                    rath->getAnimation()->changeSpriteRect(0,0,128,128);
                    mov=false;
            }
                    
                
            
        
                
        window.clear();
        window.draw(rath->getAnimation()->getCurrentSprite());
        window.display();
        
    }
    return 0;
}
