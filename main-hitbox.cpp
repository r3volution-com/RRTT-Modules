/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main-hitbox.cpp
 * Author: pablo
 *
 * Created on 27 de abril de 2017, 12:05
 */

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <cstdio>

#include "Enemy.h"
#include "Player.h"
#include "Gun.h"
using namespace std;

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");

    Texture *text = new Texture("resources/sprites.png");
    Player *rath = new Player(Coordinate(320, 240), text,Rect<float> (0, 0, 128, 128), 1.0f);
    
    Gun *gunArm = new Gun(Coordinate(300, 220), Rect<float> (0, 640, 128, 128), text);
    gunArm->getAnimation()->setOrigin(Coordinate(90,50));
    
    Enemy *enemy = new Enemy(Coordinate(600, 240), text, Rect<float> (0, 0, 128, 128), 1.0f);

    rath->getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", false);

    gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
    gunArm->getAnimation()->initAnimator();    
    gunArm->getAnimation()->changeAnimation("armaIdle", false);
    
    enemy->getAnimation()->addAnimation("enemyIdle", Coordinate(0, 0), 2, 0.25f);
    enemy->getAnimation()->initAnimator();
    enemy->getAnimation()->changeAnimation("enemyIdle", false);
    
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
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rath->move(0, -1);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rath->move(0, 1);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rath->move(1, 0);
        }
        else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                rath->move(-1, 0);
            }
        }
    }
    return 0;
}