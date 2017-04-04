
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

#include "Enemy.h"
#include "Player.h"
#include "Gun.h"
using namespace std;

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "RRTT: Sprite Test");
    char direcX = 'z';
    float PI = 3.14159265f;
    float mouseAng = 0.0f;
    float mousePos[2]={0,0};
    float windowSize[2]={0,0};
    windowSize[0]=window.getSize().x/2;
    windowSize[1]=window.getSize().y/2;
    
    
    bool mov = true;
    Texture *text = new Texture("resources/sprites.png");
    Player *rath = new Player(Coordinate(320,240), text,Rect<float> (0, 0, 128, 128), 1.0f);
    //Gun *scytheArm = new Gun(new Coordinate(320, 240 ),new Rect<float>(0 ,512, 128 ,128), text, 1, 0.5f);
    Gun *gunArm = new Gun(Coordinate(320, 240), new Rect<float> (0, 640, 128, 128), text);
    //gunArm->setOrigin(64,30);
    Enemy *enemy = new Enemy(Coordinate(600, 240), text, Rect<float> (0, 0, 128, 128), 1.0f);
    rath->getAnimation()->addAnimation("idle", Coordinate(0, 0), 3, 0.5f);
    rath->getAnimation()->addAnimation("correrDerecha", Coordinate(0, 128), 3, 0.5f);
    rath->getAnimation()->addAnimation("correrArriba", Coordinate(0, 256), 3, 0.5f);
    rath->getAnimation()->addAnimation("correrIzquierda", Coordinate(0, 384), 3, 0.5f);
    rath->getAnimation()->addAnimation("ataqueDerecha", Coordinate(0, 768), 1, 0.5f);
    rath->getAnimation()->addAnimation("ataqueIzquierda", Coordinate(0, 896), 1, 0.5f);
    rath->getAnimation()->addAnimation("ataqueAbajo", Coordinate(0, 1024), 1, 0.5f);
    rath->getAnimation()->addAnimation("ataqueArriba", Coordinate(0, 1152), 1, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", true);
    
    gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 0.25f);
    gunArm->getAnimation()->initAnimator();    
    gunArm->getAnimation()->changeAnimation("armaIdle", true);
    
    enemy->getAnimation()->addAnimation("enemyIdle", Coordinate(0, 0), 1, 0.25f);
    enemy->getAnimation()->initAnimator();
    enemy->getAnimation()->changeAnimation("enemyIdle", true);
    //rath->addAnimation('die', new Coordinate(X, X), 3, 0.5f);
    //rath->addAnimation('respawn', new Coordinate(X, X), 3, 0.5f);
    rath->addGun(gunArm);
    window.setFramerateLimit(120);
    //rath->setWeapon(scytheArm);
    
    
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
        gunArm->getAnimation()->setRotation(mouseAng);    
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(mouseAng<315 && mouseAng>225){
                //derecha BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueDerecha", false);
            }
            if(mouseAng<225 && mouseAng>135){
                //arriba BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueArriba", false);
            }
            if(mouseAng<135 && mouseAng>45){
                //izquierda BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueIzquierda", false);
            }
            if(mouseAng<45 || mouseAng>315){
                //abajo BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueAbajo", false);
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rath->move(0, -1);
            rath->getAnimation()->changeAnimation("correrAbajo", true);
        }
        mov=true;
        
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            //correr abajo
            rath->move(0, 1);
            if(direcX=='r'){
                rath->getAnimation()->changeAnimation("correrDerecha", true);  
                mov=true;
            }
            else{
                if(direcX=='l'){
                    rath->getAnimation()->changeAnimation("correrIzquierda", true);
                    mov=true;
                }
                
                
                else{
                    if(direcX!='r'&& direcX!='l'){
                        rath->getAnimation()->changeAnimation("correrDerecha", true);
                        mov=true;
                        
                    }
                }
            }
        }    
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rath->move(1, 0);
            rath->getAnimation()->changeAnimation("correrDerecha", true);
            direcX='r';
            mov=true;
        }
        else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                rath->move(-1, 0);
                rath->getAnimation()->changeAnimation("correrIzquierda", true);
                direcX='l';
                mov=true;
            }
        }
        
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
                && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& mov==true){
            rath->getAnimation()->changeAnimation("correrAbajo", true);
            mov=false;
        }
        
        rath->getAnimation()->updateAnimator();
        gunArm->getAnimation()->updateAnimator();
        enemy->getAnimation()->updateAnimator();
        window.clear();
        window.draw(*gunArm->getAnimation()->getSprite());
        window.draw(*rath->getAnimation()->getSprite());
        window.draw(*enemy->getAnimation()->getSprite());
        window.display();   
    }
    return 0;
}
